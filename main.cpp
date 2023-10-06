#include <iostream>
#include <dlfcn.h>
using namespace std;


int main() {
    void* lib = dlopen("./caesar_cipher.dylib", RTLD_LAZY);

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

    cout << "Enter a line of text: ";
    cin.getline(input, sizeof(input));

    cout << "You entered: " << input << endl;

    cout << "Enter an encryption key: ";
    cin >> key;

    char* encrypted = encrypt(input, key);
    cout << "Encrypted: " << encrypted << endl;

    char* decrypted = decrypt(encrypted, key);
    cout << "Decrypted: " << decrypted << endl;

    delete[] encrypted;
    delete[] decrypted;

    dlclose(lib);

    return 0;
}