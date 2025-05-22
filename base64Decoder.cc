#include <iostream>
#include <string>
#include <vector>

// Function to decode a single Base64 character
unsigned char decode_base64_char(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return 0;
}

// Function to decode a Base64 encoded string
std::vector<unsigned char> base64_decode(const std::string &encoded) {
    std::vector<unsigned char> decoded;
    int val = 0, valb = -8;
    for (char c : encoded) {
        if (c == '=') break;
        val = (val << 6) + decode_base64_char(c);
        valb += 6;
        if (valb >= 0) {
            decoded.push_back((val >> valb) & 0xFF);
            valb -= 8;
        }
    }
    return decoded;
}

int main() {
    std::string encoded = "SGVsbG8gd29ybGQ="; // "Hello world" in Base64
    std::vector<unsigned char> decoded = base64_decode(encoded);

    // Convert to char* buffer
    char* buffer = new char[decoded.size() + 1];
    std::copy(decoded.begin(), decoded.end(), buffer);
    buffer[decoded.size()] = '\0'; // Null-terminate the string

    std::cout << "Decoded string: " << buffer << std::endl;

    delete[] buffer; // Don't forget to free the allocated memory
    return 0;
}

