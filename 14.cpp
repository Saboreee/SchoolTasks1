#include <iostream>
#include <stdlib.h>

using namespace std;

class Big_Data {

public:
    void* buffer;
    size_t size;

    Big_Data(size_t size) {
        this->size = size;
        buffer = malloc(size);
        if (!buffer) {
            throw bad_alloc();
        }
    }

    ~Big_Data() {
        free(buffer);
    }

    Big_Data(const Big_Data& other) {
        this->size = other.size;
        buffer = malloc(size);
        if (!buffer) {
            throw bad_alloc();
        }
        memcpy(buffer, other.buffer, size);
    }

    Big_Data& operator=(const Big_Data& other) {
        if (this != &other) {
            free(buffer);
            size = other.size;
            buffer = malloc(size);
            if (!buffer) {
                throw bad_alloc();
            }
            memcpy(buffer, other.buffer, size);
        }
        return *this;
    }
};

int main() {
    try {
        Big_Data a(1024);
        Big_Data b(1024);

        // Testit kopiokonstruktorille ja sijoitusoperaattorille:

        a = a; // Kopioi a itseensä
        cout << "a = a kopion jalkeen: " << a.buffer << endl;
        a = b; // Kopioi b:n a:han
        cout << "a = b jalkeen: " << endl;
        cout << "a = " << a.buffer << endl;
        cout << "b = " << b.buffer << endl;
        Big_Data c(a); // Kopioi a:n c:hen
        cout << "lopuksi a kopioi c:hen jalkeiset arvot:" << endl;
        cout << "a = " << a.buffer << endl;
        cout << "b = " << b.buffer << endl;
        cout << "c = " << c.buffer << endl;


    }
    catch (const bad_alloc& e) {
        cerr << "Muistin varaaminen epäonnistui: " << e.what() << endl;
    }

    return 0;
}