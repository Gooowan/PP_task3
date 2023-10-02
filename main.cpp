#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
using namespace std;

//char* encrypt(const char* rawText, int key) {
//    size_t length = strlen(rawText);
//    char* encryptedText = new char[length + 1];
//
//    for (size_t i = 0; i < length; i++) {
//        char originalChar = rawText[i];
//        char encryptedChar = static_cast<char>(originalChar + key);
//
//        if (originalChar >= 'a' && originalChar <= 'z') {
//            if (encryptedChar > 'z') {
//                encryptedChar = 'a' + (encryptedChar - 'z' - 1);
//            }
//        } else if (originalChar >= 'A' && originalChar <= 'Z') {
//            if (encryptedChar > 'Z') {
//                encryptedChar = 'A' + (encryptedChar - 'Z' - 1);
//            }
//        }
//
//        encryptedText[i] = encryptedChar;
//    }
//    encryptedText[length] = '\0';
//
//    return encryptedText;
//}
//
//char* decrypt(const char* rawText, int key) {
//    size_t length = strlen(rawText);
//    char* decryptedText = new char[length + 1];
//
//    for (size_t i = 0; i < length; i++) {
//        char originalChar = rawText[i];
//        char decryptedChar = static_cast<char>(originalChar - key);
//
//        if (originalChar >= 'a' && originalChar <= 'z') {
//            if (decryptedChar < 'a') {
//                decryptedChar = 'z' - ('a' - decryptedChar - 1);
//            }
//        } else if (originalChar >= 'A' && originalChar <= 'Z') {
//            if (decryptedChar < 'A') {
//                decryptedChar = 'Z' - ('A' - decryptedChar - 1);
//            }
//        }
//
//        decryptedText[i] = decryptedChar;
//    }
//    decryptedText[length] = '\0';
//
//    return decryptedText;
//}

int main() {
    void* lib = dlopen("./caesar_cipher.dylib", RTLD_LAZY);

    if (!lib) {
        std::cerr << "Error loading the library: " << dlerror() << std::endl;
        return 1;
    }

    char* (*encrypt)(const char*, int);
    char* (*decrypt)(const char*, int);

    encrypt = reinterpret_cast<char* (*)(const char*, int)>(dlsym(lib, "encrypt"));
    decrypt = reinterpret_cast<char* (*)(const char*, int)>(dlsym(lib, "decrypt"));

    if (!encrypt || !decrypt) {
        std::cerr << "Error loading functions: " << dlerror() << std::endl;
        dlclose(lib);
        return 1;
    }

    char input[100];
    int key;

    std::cout << "Enter a line of text: ";
    std::cin.getline(input, sizeof(input));

    std::cout << "You entered: " << input << std::endl;

    std::cout << "Enter an encryption key: ";
    std::cin >> key;

    char* encrypted = encrypt(input, key);
    std::cout << "Encrypted: " << encrypted << std::endl;

    char* decrypted = decrypt(encrypted, key);
    std::cout << "Decrypted: " << decrypted << std::endl;

    delete[] encrypted;
    delete[] decrypted;

    dlclose(lib);

    return 0;
}