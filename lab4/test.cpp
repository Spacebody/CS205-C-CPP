#include <iostream>
#include "UTF8string.hpp"

int main()
{
    UTF8string test_str("わたしの愛 それは小舟");
    std::cout << "length of the utf-8 string: " << test_str.length() << std::endl;
    std::cout << "size of the utf-8 string: " << test_str.bytes() << std::endl;
    std::cout << "position of the utf-8 sub-string: " << test_str.find("愛") << std::endl;
    UTF8string to_remove("小舟");
    UTF8string replacement("巨轮");
    std::cout << "before replacement: " << test_str.str << std::endl;
    test_str.replace(to_remove, replacement);
    std::cout << "after replacement: " << test_str.str << std::endl;
    return 0;
}