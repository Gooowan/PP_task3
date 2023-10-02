#include <iostream>
#include <cstdlib>
using namespace std;

char* encrypt(const char* rawText, int key) {
    size_t length = strlen(rawText);
    char* encryptedText = new char[length + 1];

    for (size_t i = 0; i < length; i++) {
        char originalChar = rawText[i];
        char encryptedChar = static_cast<char>(originalChar + key);

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

char* decrypt(const char* rawText, int key) {
    size_t length = strlen(rawText);
    char* decryptedText = new char[length + 1];

    for (size_t i = 0; i < length; i++) {
        char originalChar = rawText[i];
        char decryptedChar = static_cast<char>(originalChar - key);

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

int main() {
    char* input = nullptr;
    int key;

    printf("Enter a line of text: ");

    size_t buffer_size = 100;
    input = (char*)malloc(buffer_size);

    if (input != nullptr) {
        if (fgets(input, buffer_size, stdin) != NULL) {
            size_t len = strlen(input);
            if (len > 0 && input[len - 1] == '\n') {
                input[len - 1] = '\0';
            }

            printf("You entered: %s\n", input);

            printf("Enter an encryption key: ");
            cin >> key;

            char* encrypted = encrypt(input, key);
            cout << "Encrypted: " << encrypted << endl;

            char* decrypted = decrypt(encrypted, key);
            cout << "Decrypted: " << decrypted << endl;

            free(input);
            delete[] encrypted;
            delete[] decrypted;
        } else {
            printf("Error reading input.\n");
            free(input);
        }
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
