#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

// Function to generate RSA key pair
void generate_rsa_key_pair(std::string &public_key, std::string &private_key) {
    RSA *rsa = RSA_new();
    BIGNUM *bne = BN_new();
    BN_set_word(bne, RSA_F4);

    RSA_generate_key_ex(rsa, 2048, bne, NULL);

    BIO *bp_public = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bp_public, rsa);
    BIO *bp_private = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bp_private, rsa, NULL, NULL, 0, NULL, NULL);

    size_t public_len = BIO_pending(bp_public);
    size_t private_len = BIO_pending(bp_private);

    public_key.resize(public_len);
    private_key.resize(private_len);

    BIO_read(bp_public, &public_key[0], public_len);
    BIO_read(bp_private, &private_key[0], private_len);

    BIO_free_all(bp_public);
    BIO_free_all(bp_private);
    RSA_free(rsa);
    BN_free(bne);
}

// Function to encrypt data with AES
std::vector<unsigned char> aes_encrypt(const std::vector<unsigned char> &data, const std::vector<unsigned char> &key, const std::vector<unsigned char> &iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key.data(), iv.data());

    std::vector<unsigned char> ciphertext(data.size() + AES_BLOCK_SIZE);
    int len;
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, data.data(), data.size());
    int ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;
    ciphertext.resize(ciphertext_len);

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext;
}

// Function to decrypt data with AES
std::vector<unsigned char> aes_decrypt(const std::vector<unsigned char> &ciphertext, const std::vector<unsigned char> &key, const std::vector<unsigned char> &iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key.data(), iv.data());

    std::vector<unsigned char> plaintext(ciphertext.size());
    int len;
    EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size());
    int plaintext_len = len;
    EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len);
    plaintext_len += len;
    plaintext.resize(plaintext_len);

    EVP_CIPHER_CTX_free(ctx);
    return plaintext;
}

// Function to encrypt symmetric key with RSA public key
std::vector<unsigned char> rsa_encrypt(const std::vector<unsigned char> &data, const std::string &public_key) {
    BIO *bio = BIO_new_mem_buf(public_key.data(), public_key.size());
    RSA *rsa = PEM_read_bio_RSAPublicKey(bio, NULL, NULL, NULL);
    BIO_free(bio);

    std::vector<unsigned char> encrypted(RSA_size(rsa));
    int len = RSA_public_encrypt(data.size(), data.data(), encrypted.data(), rsa, RSA_PKCS1_OAEP_PADDING);
    if (len == -1) {
        RSA_free(rsa);
        throw std::runtime_error("RSA encryption failed");
    }

    RSA_free(rsa);
    encrypted.resize(len);
    return encrypted;
}

// Function to decrypt symmetric key with RSA private key
std::vector<unsigned char> rsa_decrypt(const std::vector<unsigned char> &encrypted, const std::string &private_key) {
    BIO *bio = BIO_new_mem_buf(private_key.data(), private_key.size());
    RSA *rsa = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
    BIO_free(bio);

    std::vector<unsigned char> decrypted(RSA_size(rsa));
    int len = RSA_private_decrypt(encrypted.size(), encrypted.data(), decrypted.data(), rsa, RSA_PKCS1_OAEP_PADDING);
    if (len == -1) {
        RSA_free(rsa);
        throw std::runtime_error("RSA decryption failed");
    }

    RSA_free(rsa);
    decrypted.resize(len);
    return decrypted;
}

// Function to read file content into a vector
std::vector<unsigned char> read_file(const std::string &file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file for reading");
    }
    std::vector<unsigned char> content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

// Function to write vector content to a file
void write_file(const std::string &file_path, const std::vector<unsigned char> &content) {
    std::ofstream file(file_path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file for writing");
    }
    file.write(reinterpret_cast<const char*>(content.data()), content.size());
}

// Main function
int main() {
    try {
        // Generate RSA key pair
        std::string public_key, private_key;
        generate_rsa_key_pair(public_key, private_key);
        std::cout << "pub key: " << public_key.c_str() << "\npriv key: " << private_key.c_str() << std::endl;
        // Generate AES key and IV
        std::vector<unsigned char> aes_key(32);
        std::vector<unsigned char> aes_iv(AES_BLOCK_SIZE);
        RAND_bytes(aes_key.data(), aes_key.size());
        RAND_bytes(aes_iv.data(), aes_iv.size());

        // Encrypt AES key with RSA public key
        std::vector<unsigned char> encrypted_aes_key = rsa_encrypt(aes_key, public_key);
        std::cout << "encrypted_aes_key : {";
        for(char c1 : encrypted_aes_key) {
          std::cout << c1;
        }
        std::cout << "}" << std::endl;
        // Read and encrypt the file
        std::string input_file_path = "input.txt";
        std::vector<unsigned char> file_content = read_file(input_file_path);
        std::vector<unsigned char> encrypted_file_content = aes_encrypt(file_content, aes_key, aes_iv);
        // Write the encrypted file content to an output file
        std::string outEncr_file_path = "output_encrypt.enc";
        write_file(outEncr_file_path, encrypted_file_content);

        // Decrypt the file content
        std::vector<unsigned char> decrypted_aes_key = rsa_decrypt(encrypted_aes_key, private_key);
        std::vector<unsigned char> decrypted_file_content = aes_decrypt(encrypted_file_content, decrypted_aes_key, aes_iv);
        std::cout << "decrypted_aes_key : {";
        for(char c2 : decrypted_aes_key) {
          std::cout << c2;
        }
        std::cout << "}" << std::endl;

        // Write the decrypted file content to an output file
        std::string decrypt_file_path = "output_decrypt.txt";
        write_file(decrypt_file_path, decrypted_file_content);

        // Modify the decrypted file content
        std::string modified_content = "Modified content: \n    ";
        for(char c : decrypted_file_content) {
          modified_content += c;
          //std::cout << c << std::endl;
        }
        decrypted_file_content.assign(modified_content.begin(), modified_content.end());
        // Write the modified file content to an output file
        std::string modif_file_path = "modified.txt";
        write_file(modif_file_path, decrypted_file_content);

        // Re-encrypt the modified file content
        std::vector<unsigned char> re_encrypted_file_content = aes_encrypt(decrypted_file_content, aes_key, aes_iv);

        // Write the encrypted file content to an output file
        std::string output_file_path = "output.enc";
        write_file(output_file_path, re_encrypted_file_content);

        std::cout << "File has been successfully encrypted, modified, and written to " << output_file_path << std::endl;
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

