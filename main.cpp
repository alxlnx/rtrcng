#include <bits/stdc++.h>

struct VectorInt {    
    int* data;
    int size;

    void initialize(int new_sz) {
        size = new_sz;
        data = new int[size];
    }

    void erase() {
        delete[] data;
    }

    int get(const int& idx) {
        // bruh no validity check
        return data[idx];
    }
};

int main() {
    VectorInt v{};


    std::cout << "\n\n";
    return 0;
}