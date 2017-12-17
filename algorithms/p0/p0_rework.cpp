#include <string>
#include <ctime>
#include <algorithm>
#include <utility>
#include <iostream>


/// Calculate average of given numbers
/// @param[in] arr Numbers to calculate from
/// @returns Average of given numbers. When ampty array 
/// was given 0 will be returned
unsigned arithmetic_mean(const unsigned *arr, unsigned size)
{
    if (!size)
        return 0;
    // overflow of 'res' will never happen because c++11 standard guarantees
    // that sizeof(unsigned) will never be longer than 4 bytes and than 
    // sizeof(unsigned long long) will always be at least 8 bytes so in worst
    // case scenario (when 'arr' is full of 'UINT_MAX') sum of its values 
    // will never be greater than sizeof(unsigned long long)
    ///  (2 ^ 32 * 2 ^ 32 == 2 ^ 64)
    unsigned long long res = 0;
    for (unsigned i = 0; i < size; ++i)
        res += arr[i];
    return static_cast<unsigned>(res / size);
}

void print_table(const unsigned *data, unsigned data_size, const std::string &name, unsigned line_size)
{
    if (!data_size) {
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
    std::cout << "\n";
}

void selection_sort(unsigned *vec, unsigned vec_size)
{
    unsigned min_elem = 0;
    for (int i = 0; i < vec_size; i++) {
        min_elem = i;
        for (int j = i + 1; j < vec_size; j++)
            if (vec[j] < vec[min_elem])
                min_elem = j;
        std::swap(vec[min_elem], vec[i]);
    }
}

void init_random_number()
{
    std::srand(std::time(nullptr));
}

unsigned get_random_number(unsigned min, unsigned max)
{
    return min + (rand() % static_cast<int>(max - min + 1));
}

int main()
{
    constexpr std::size_t n = 100;
    constexpr unsigned d = 100;
    constexpr unsigned g = 100000;
    constexpr unsigned k = 8;
    init_random_number();
    unsigned A[n];

    for (unsigned i = 0; i < n; ++i)
        A[i] = get_random_number(d, g);
    unsigned average = arithmetic_mean(A, n);
    print_table(A, n, "A", k);

    // 1.
    unsigned *B(new unsigned[n]);
    unsigned B_size = 0;
    unsigned *C(new unsigned[n]);
    unsigned C_size = 0;
    for (unsigned i = 0; i < n; ++i) {
        unsigned curr_value = A[i];
        if (curr_value > average) {
            B[B_size] = curr_value;
            B_size++;
        } else {
            C[C_size] = curr_value;
            C_size++;
        }
    }

    // 2.
    print_table(B, B_size, "B", k);
    print_table(C, C_size, "C", k);

    // 3.
    selection_sort(A, n);
    selection_sort(B, B_size);
    selection_sort(C, C_size);

    //4.
    print_table(A, n, "B", k);
    print_table(B, B_size, "B", k);
    print_table(C, C_size, "C", k);
}
