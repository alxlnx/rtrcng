#include <bits/stdc++.h>

std::ofstream ofs {"output.txt"};

namespace Utils {
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
void printv(const std::vector<T>& v) 
// Print a vector to stdout
{
    for (auto x : v)
        std::cout << x << ' ';
    std::cout << '\n';
}

template <typename T>
T get_rand_num(const T& min, const T& max) 
// Return a random number ranging from min to max.
{
    std::random_device rnd_dev{};
    std::default_random_engine engine(rnd_dev());
    std::uniform_int_distribution<T> distribution(min, max);

    return distribution(engine);
}

template <typename T>
void random_fillv(std::vector<T>& v, const T& min, const T& max) 
// Fill a vector with random numbers ranging from min to max.
{
    for (long long i{}; i < v.size(); ++i)
        v[i] = get_rand_num<T>(min, max);
}

struct Timer
{
    std::chrono::high_resolution_clock::time_point start { std::chrono::high_resolution_clock::now() };

    ~Timer() {
        auto end { std::chrono::high_resolution_clock::now() };
        auto duration { end - start };

        ofs << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() << 
            "\n"; // "Execution time: " << µs 
    }
};
} // Utils namespace

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

int main()
{
    std::freopen("input.txt", "r", stdin);

    constexpr int points_amount { 50 };
    constexpr int tests_amount  { 100 };
    // Get N data points for a given level of optimization:
    ofs << "O3\n";
    ofs << points_amount << '\n'; // << "Amount of points: "
    ofs << tests_amount << '\n'; // << "Amount of tests per point: " 

    for (int point_num{}; point_num < points_amount; ++point_num) {
        // ofs << '\n';
        
        const int v_size { Utils::get_rand_num<int>(2, 1000 ) };
        
        ofs << v_size << '\n'; //  "Dataset length: " <<
        // Run 100 tests for fixed dataset length:
        for (int test_num{}; test_num < tests_amount; ++test_num) 
        {   
            Utils::Timer t{};

            std::vector<ValType> v(v_size, 0);

            Utils::random_fillv(v, 10, 100);

            v = MergeSort::merge_sort(v);
            // Utils::printv(v);
            // Utils::printv(MergeSort::merge_sort(v));
        }
        // for (ValType tmp{}; std::cin >> tmp; v.push_back(tmp)) {}
    }
}