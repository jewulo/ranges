// ranges.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// https://en.cppreference.com/w/cpp/ranges


#include <vector>
#include <iostream>
#include <ranges>
#include <concepts>
#include <algorithm> 

namespace rv = std::ranges::views;
void test_ranges_1(void)
{
    const std::vector<int> nums{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto is_even = [](int i) { return 0 == i % 2; };
    auto square = [](int i) { return i * i; };

    for (int i : nums | std::views::filter(is_even) | std::views::transform(square)) {
        std::cout << i << ' ';
    }

    std::ranges::reverse_view rv{
        std::ranges::filter_view{
            std::ranges::drop_view { nums, 0 }, is_even
        }
    };

    for (auto& i : rv)
        std::cout << i << ' ';
}

struct Product {
    std::string name;
    double value{ 0.0 };
};

void print(std::string_view intro, const std::vector<Product>& container) {
    std::cout << intro << '\n';
    for (const auto& elem : container)
        std::cout << elem.name << ", " << elem.value << '\n';
}

// using range projections on data structures
void test_ranges_2(void)
{
    const std::vector<Product> prods{
        { "box", 10.0 }, {"tv", 100.0}, {"ball", 30.0},
        { "car", 1000.0 }, {"toy", 40.0}, {"cake", 15.0},
        { "book", 45.0}, {"pc game", 35.0}, {"wine", 25}
    };

    print("input", prods);

    // the standard version:
    std::vector<Product> copy = prods;
    std::sort(begin(copy), end(copy),
        [](const Product& a, const Product& b)
        { return a.name < b.name; }
    );

    print("after sorting by name", copy);

    // the ranges version:
    copy = prods;
    std::ranges::sort(copy, {}, &Product::name);
    print("after sorting by name", copy);
    std::ranges::sort(copy, {}, &Product::value);
    print("after sorting by value", copy);
    auto sorted = std::ranges::is_sorted(copy, {}, &Product::value);
    std::cout << "is sorted by value: " << sorted << '\n';
}

void test_projection(void)
{
    Product p1{ "apples",2.0 };
    Product p2{ "pears",4.0 };

    std::cout << std::invoke(&Product::name, p1) << '\n';
    std::cout << std::invoke(&Product::value, p1) << '\n';
    std::cout << std::invoke(&Product::name, p2) << '\n';
    std::cout << std::invoke(&Product::value, p2) << '\n';
}

int main()
{
    test_ranges_1();

    test_ranges_2();

    test_projection();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
