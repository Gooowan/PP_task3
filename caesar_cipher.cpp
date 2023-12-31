#include <iostream>
#include <cstring>

extern "C" char* encrypt(const char* rawText, int key) {
    size_t length = strlen(rawText);
    char* encryptedText = new char[length + 1];

    for (size_t i = 0; i < length; i++) {
        char originalChar = rawText[i];
        char encryptedChar;

        if (int(originalChar) + key > 127) {
            while (int(originalChar) + key > 127){
                key -= 127;
            }
            encryptedChar = static_cast<char>(originalChar + key);
        } else {
            encryptedChar = static_cast<char>(originalChar + key);
        }

        if (originalChar >= 'a' && originalChar <= 'z') {
            if (encryptedChar > 'z') {
                encryptedChar = 'a' + (encryptedChar - 'z' - 1);
            }
        } else if (originalChar >= 'A' && originalChar <= 'Z') {
            if (encryptedChar > 'Z') {
                encryptedChar = 'A' + (encryptedChar - 'Z' - 1);
            }
        }

        encryptedText[i] = encryptedChar;
    }
    encryptedText[length] = '\0';

    return encryptedText;
}

extern "C" char* decrypt(const char* rawText, int key) {
    size_t length = strlen(rawText);
    char* decryptedText = new char[length + 1];

    for (size_t i = 0; i < length; i++) {
        char originalChar = rawText[i];
        char decryptedChar;

        if (int(originalChar) - key < 0) {
            while (int(originalChar) - key < 0){
                key -= 127;
            }
            decryptedChar = static_cast<char>(originalChar - key);
        } else {
            decryptedChar = static_cast<char>(originalChar - key);
        }

        if (originalChar >= 'a' && originalChar <= 'z') {
            if (decryptedChar < 'a') {
                decryptedChar = 'z' - ('a' - decryptedChar - 1);
            }
        } else if (originalChar >= 'A' && originalChar <= 'Z') {
            if (decryptedChar < 'A') {
                decryptedChar = 'Z' - ('A' - decryptedChar - 1);
            }
        }

        decryptedText[i] = decryptedChar;
    }
    decryptedText[length] = '\0';

    return decryptedText;
}