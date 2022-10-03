#include <bits/stdc++.h>

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

template <typename T>
void printv(const std::vector<T>& v) {
    for (auto x : v)
        std::cout << x << ' ';
}

int main()
{
    std::freopen("input.txt", "r", stdin);

    
}