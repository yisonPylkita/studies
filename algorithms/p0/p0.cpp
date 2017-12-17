#include <cassert>
#include <string>
#include <array>
#include <vector>
#include <random>
#include <algorithm>
#include <utility>
#include <iostream>


/// Calculate average of given numbers
/// @param[in] arr Numbers to calculate from
/// @returns Average of given numbers. When ampty array 
/// was given 0 will be returned
template <typename T>
unsigned arithmetic_mean(const T &arr)
{
    if (arr.empty())
        return 0;
    // overflow of 'res' will never happen because c++11 standard guarantees
    // that sizeof(unsigned) will never be longer than 4 bytes and than 
    // sizeof(unsigned long long) will always be at least 8 bytes so in worst
    // case scenario (when 'arr' is full of 'UINT_MAX') sum of its values 
    // will never be greater than sizeof(unsigned long long)
    ///  (2 ^ 32 * 2 ^ 32 == 2 ^ 64)
    unsigned long long res = 0;
    for (auto x : arr)
        res += x;
    return static_cast<unsigned>(res / arr.size());
}

template <typename T>
void print_table(const T &data, const std::string &name, unsigned line_size)
{
    const unsigned data_size = data.size();
    if (data_size == 0) {
        std::cout << "Table " << name << " is empty\n";
        return;
    }
    std::cout << "Table " << name << ", size " << data_size << "\n";

    unsigned curr_line_size = 0;
    for (unsigned i = 0; i < data_size; i++) {
        std::cout << data[i] << ", ";
        curr_line_size++;
        if (curr_line_size > line_size) {
            curr_line_size = 0;
            std::cout << "\n";
        }
    }
}

template <typename T>
void selection_sort(T &vec)
{
    const auto vec_size = vec.size();
    unsigned min_elem = 0;
    for (int i = 0; i < vec_size; i++) {
        min_elem = i;
        for (int j = i + 1; j < vec_size; j++)
            if (vec[j] < vec[min_elem])
                min_elem = j;
        std::swap(vec[min_elem], vec[i]);
    }
}

int main()
{
    constexpr std::size_t n = 1000000;
    constexpr unsigned d = 100;
    constexpr unsigned g = 100000;
    constexpr unsigned k = 8;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(d, g);
    std::array<unsigned, n> A;

    for (auto &x : A)
        x = dis(gen);
    unsigned average = arithmetic_mean(A);
    print_table(A, "A", k);

    // 1.
    std::vector<unsigned> B;
    std::vector<unsigned> C;
    for (auto x : A) {
        if (x > average)
            B.push_back(x);
        else
            C.push_back(x);
    }

    // 2.
    print_table(B, "B", k);
    print_table(C, "C", k);

    // 3.
    selection_sort(A);
    selection_sort(B);
    selection_sort(C);

    //4.
    print_table(A, "B", k);
    print_table(B, "B", k);
    print_table(C, "C", k);
}
