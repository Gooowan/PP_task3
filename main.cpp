#include <iostream>
#include <dlfcn.h>
#include <cstring>
using namespace std;

int main() {
    void* lib = dlopen("./caesar_cipher.dylib1", RTLD_LAZY);

    if (!lib) {
        cerr << "Error loading the library: " << dlerror() << endl;
        return 1;
    }

    char* (*encrypt)(const char*, int);
    char* (*decrypt)(const char*, int);

    encrypt = reinterpret_cast<char* (*)(const char*, int)>(dlsym(lib, "encrypt"));
    decrypt = reinterpret_cast<char* (*)(const char*, int)>(dlsym(lib, "decrypt"));

    if (!encrypt || !decrypt) {
        cerr << "Error loading functions: " << dlerror() << endl;
        dlclose(lib);
        return 1;
    }

    char input[100];
    int key;

    while (true) {
        cout << "Enter a line of text, if you need help, type -h: ";

        cin.getline(input, sizeof(input));

        if (strcmp(input, "stop") == 0) {
            break;
        }

        if (strcmp(input, "-h") != 0) {
            cout << "Enter an encryption key: ";
            cin >> key;


            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            char *encrypted = encrypt(input, key);
            cout << "Encrypted: " << encrypted << endl;

            char *decrypted = decrypt(encrypted, key);
            cout << "Decrypted: " << decrypted << endl;


            delete[] encrypted;
            delete[] decrypted;
        } else {
            cout << "\nYou should type a message that you would like to transfer and key to create a message transcribed with caesar cipher\n \n";
        }
    }
    dlclose(lib);

    return 0;
}
