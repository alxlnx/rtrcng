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

    int& get(const int& idx) {
        // bruh no validity check
        return data[idx];
    }
    const int& get(const int& idx) const {
        return data[idx];
    }
};

template <typename T> // T must be an integer type (signed/unsigned, pos/neg - doesn't matter).
void dec2bin(const T& n) 
// Print binary representation of n (output is sent to stdout) using bit masks.
{
    for (int i{ sizeof(T) * 8 - 1 }; i >= 0; --i) {
        // -1 seems to work but check out pos and neg nums
        // also pass ull to see weird stuff
        std::cout << ( ( (n & (1 << i) ) > 0 ) ? 1 : 0);
    }   
}

int main() {
    VectorInt v{};

    union A {
        float value;
        unsigned int bits;
    };

    // 1. float -> binary
    // { // That works! dec2bin(137.375f) won't.
    //
    //     // 01000011000010010110000000000000
    //     A a { 137.375f };
    //     dec2bin(a.bits);
    // }

    // 2. Mantissa overflow. Idk what I see when this runs.
    // {
    //     std::cout << std::fixed; 
    //     std::cout.precision(2);
    //
    //     for (unsigned int i { 10 }; (unsigned long)i * 10 < std::numeric_limits<unsigned int>::max(); i *= 10) {
    //         std::cout << i << "    " << std::bitset<sizeof(unsigned long) * 8>(i) << "    "; 
    //         dec2bin( A{ (float)i }.bits ); 
    //         std::cout << '\n';
    //     }
    // }
    
    

    std::cout << "\n\n";
    return 0;
}