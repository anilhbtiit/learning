#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/buffer.h>

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int main(void) {
    // Example key and IV (should be securely generated in real applications)
    unsigned char key[EVP_MAX_KEY_LENGTH] = "0123456789abcdef";
    unsigned char iv[EVP_MAX_IV_LENGTH+1] = "abcdef9876543210";

    // Example ciphertext (encrypted data)
    unsigned char ciphertext[] = { /* ... */ };
    int ciphertext_len = sizeof(ciphertext);

    // Buffer for the decrypted text
    //unsigned char decryptedtext;
    unsigned char* decryptedtext;
    int decryptedtext_len, len;

    // Create and initialize the context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    // Initialize the decryption operation
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    // Provide the message to be decrypted, and obtain the plaintext output
    if (1 != EVP_DecryptUpdate(ctx, decryptedtext, &len, ciphertext, ciphertext_len))
        handleErrors();
    decryptedtext_len = len;

    // Finalize the decryption
    if (1 != EVP_DecryptFinal_ex(ctx, decryptedtext + len, &len))
        handleErrors();
    decryptedtext_len += len;

    // Add a NULL terminator to the decrypted text
    decryptedtext[decryptedtext_len] = '\0';

    // Print the decrypted text
    printf("Decrypted text is: %s\n", decryptedtext);

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    return 0;
}

