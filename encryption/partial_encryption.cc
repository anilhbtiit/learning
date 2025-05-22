#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/aes.h>

// Function to encrypt data using RSA public key
std::string rsaEncrypt(const std::string &data, const std::string &pubKeyPath) {
    // Load the public key
    FILE *pubKeyFile = fopen(pubKeyPath.c_str(), "rb");
    if (!pubKeyFile) {
        throw std::runtime_error("Unable to open public key file");
    }
    RSA *rsa = PEM_read_RSA_PUBKEY(pubKeyFile, nullptr, nullptr, nullptr);
    fclose(pubKeyFile);
    if (!rsa) {
        throw std::runtime_error("Error reading public key");
    }

    std::string encryptedData(RSA_size(rsa), '\0');
    int result = RSA_public_encrypt(data.size(),
                                    reinterpret_cast<const unsigned char *>(data.c_str()),
                                    reinterpret_cast<unsigned char *>(&encryptedData[0]),
                                    rsa, RSA_PKCS1_OAEP_PADDING);
    RSA_free(rsa);
    if (result == -1) {
        throw std::runtime_error("Error encrypting data");
    }

    return encryptedData;
}

// Function to decrypt data using RSA private key
std::string rsaDecrypt(const std::string &encryptedData, const std::string &privKeyPath) {
    // Load the private key
    //FILE *privKeyFile = fopen(privKeyPath.c_str(), "rb");
    FILE *privKeyFile = fopen(privKeyPath.c_str(), "r");
    if (!privKeyFile) {
        throw std::runtime_error("Unable to open private key file");
    }
    RSA *rsa = PEM_read_RSAPrivateKey(privKeyFile, nullptr, nullptr, nullptr);
    fclose(privKeyFile);
    if (!rsa) {
        throw std::runtime_error("Error reading private key");
    }

    std::string decryptedData(RSA_size(rsa), '\0');
    int result = RSA_private_decrypt(encryptedData.size(),
                                     reinterpret_cast<const unsigned char *>(encryptedData.c_str()),
                                     reinterpret_cast<unsigned char *>(&decryptedData[0]),
                                     rsa, RSA_PKCS1_OAEP_PADDING);
    RSA_free(rsa);
    if (result == -1) {
        throw std::runtime_error("Error decrypting data");
    }

    return decryptedData;
}

// Function to read the file and process the sections marked with pragma
void processFile(const std::string &inputFilePath, const std::string &outputFilePath,
                 const std::string &privKeyPath, const std::string &pubKeyPath) {
    std::ifstream inputFile(inputFilePath);
    std::ofstream outputFile(outputFilePath);

    if (!inputFile || !outputFile) {
        throw std::runtime_error("Unable to open input or output file");
    }

    std::string line;
    bool inPragmaSection = false;
    std::stringstream pragmaContent;

    while (std::getline(inputFile, line)) {
        if (line.find("#pragma start") != std::string::npos) {
            inPragmaSection = true;
            outputFile << line << '\n';
            continue;
        } else if (line.find("#pragma end") != std::string::npos) {
            inPragmaSection = false;

            // Decrypt the pragma content
            std::string encryptedContent = pragmaContent.str();
            std::string decryptedContent = rsaDecrypt(encryptedContent, privKeyPath);

            // Modify the decrypted content (for example, replace a string)
            std::string modifiedContent = decryptedContent; // Perform your modifications here

            // Encrypt the modified content
            std::string reencryptedContent = rsaEncrypt(modifiedContent, pubKeyPath);

            // Write the encrypted content to the output file
            outputFile << reencryptedContent << '\n';
            outputFile << line << '\n';

            // Clear the stringstream for the next pragma section
            pragmaContent.str(std::string());
            continue;
        }

        if (inPragmaSection) {
            pragmaContent << line << '\n';
        } else {
            outputFile << line << '\n';
        }
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    try {
        std::string inputFilePath = "pragma_input.txt";
        std::string outputFilePath = "pragma_output.txt";
        //std::string privKeyPath = "private_key.pem";
        //std::string pubKeyPath = "public_key.pem";
        std::string privKeyPath = "privKey.pem";
        std::string pubKeyPath = "pubKey.pem";

        processFile(inputFilePath, outputFilePath, privKeyPath, pubKeyPath);

        std::cout << "File processed successfully." << std::endl;
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

