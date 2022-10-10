#include <bits/stdc++.h>

template <typename T> // NB: T must be an integer type (signed/unsigned, pos/neg - doesn't matter).
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

using ValType = int; // Evil thing to ease testing of different data types

namespace MergeSort {
std::vector<ValType> merge(const std::vector<ValType>& lhs, const std::vector<ValType>& rhs) {
    std::vector<ValType> result{};
    int i{}, j{};
    // Compare and add while there's room for that
    while (i < lhs.size() && j < rhs.size()) {
            if(lhs[i] < rhs[j])
                result.push_back(lhs[i++]);
            else
                result.push_back(rhs[j++]);
    }

    // Push everything left from one of the vectors 
    while (i < lhs.size()) result.push_back(lhs[i++]);
    while (j < rhs.size()) result.push_back(rhs[j++]);

    return result;
}

std::vector<ValType> merge_sort(const std::vector<ValType>& array) {
    if (array.size() <= 1) return array;

    int middle = array.size() / 2;

    // Split the array in two parts
    std::vector<ValType> left{}, right{};
    for (int i{}; i < middle; ++i) left.push_back(array[i]);
    for (int j{middle}; j < array.size(); ++j) right.push_back(array[j]);

    // Sort & merge
    auto left_sorted = merge_sort(left);
    auto right_sorted = merge_sort(right);
    return merge(left_sorted, right_sorted);
}
} // MergeSort namespace

struct Timer
{
    std::chrono::high_resolution_clock::time_point start { std::chrono::high_resolution_clock::now() };

    ~Timer() {
        auto end { std::chrono::high_resolution_clock::now() };
        auto duration { end - start };

        std::cout << "\nExecution time: " << 
            std::chrono::duration_cast<std::chrono::microseconds>(duration).count() << 
            " µs\n";
    }
};

int main()
{
    std::freopen("input.txt", "r", stdin);

    {
        Timer t{};

        std::vector<ValType> v{};
        for (ValType tmp{}; std::cin >> tmp; v.push_back(tmp)) {}
        printv(MergeSort::merge_sort(v));
    }
}