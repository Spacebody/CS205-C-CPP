#include <iostream>
#include "UTF8string.hpp"

int main()
{
    // test 1
    UTF8string test_str("わたしの愛 それは小舟");
    std::cout << "length of the utf-8 string: " << test_str.length() << std::endl;
    std::cout << "size of the utf-8 string: " << test_str.bytes() << std::endl;
    std::cout << "position of the utf-8 sub-string: " << test_str.find("愛") << std::endl;
    UTF8string to_remove("小舟");
    UTF8string replacement("巨轮");
    std::cout << "before replacement: " << test_str.content() << std::endl;
    test_str.replace(to_remove, replacement);
    std::cout << "after replacement: " << test_str.content() << std::endl << std::endl;
    // test 2
    UTF8string test_str2("两只老虎，两只老虎，跑得快，跑得快，一直没有眼睛，一直没有耳朵");
    std::cout << "length of the utf-8 string: " << test_str2.length() << std::endl;
    std::cout << "size of the utf-8 string: " << test_str2.bytes() << std::endl;
    std::cout << "position of the utf-8 sub-string: " << test_str2.find("眼镜") << std::endl;
    UTF8string to_remove2("老虎");
    UTF8string replacement2("老鼠");
    std::cout << "Replacement in pure C style:" << std::endl;
    std::cout << "before replacement: " << test_str2.content() << std::endl;
    test_str2.replace(to_remove2, replacement2);
    std::cout << "after replacement: " << test_str2.content() << std::endl;
    UTF8string to_remove3("跑得快");
    UTF8string replacement3("飞得太慢");
    std::cout << "Replacement in C++ style:" << std::endl;
    std::cout << "before replacement: " << test_str2.content() << std::endl;
    test_str2.replace2(to_remove3, replacement3);
    std::cout << "after replacement: " << test_str2.content() << std::endl;
    return 0;
}