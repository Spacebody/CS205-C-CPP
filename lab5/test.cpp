#include <iostream>
#include "UTF8string.hpp"

int main()
{
    //test
    UTF8string test_str3("商女不知亡国恨");
    std::cout << "Test <<:" << std::endl;
    std::cout << test_str3 << std::endl; // <<
    UTF8string test_str4("隔江犹唱后庭花");
    UTF8string cat_str = test_str3 + UTF8string("，") + test_str4 + UTF8string("。");  // +
    std::cout << "Test +:" << std::endl;
    std::cout << cat_str << std::endl;
    test_str3 += UTF8string("，"); // +=
    test_str3 += test_str4;
    test_str3 += UTF8string("。");
    std::cout << "Test +=:" << std::endl;
    std::cout << test_str3 << std::endl;
    UTF8string repeated_str = test_str3 * 2;  // *
     UTF8string repeated_str2 = 2 * test_str3;  // *
    std::cout << "Test *:" << std::endl;
    std::cout << repeated_str << std::endl;
    std::cout << repeated_str2 << std::endl;
    std::cout << "Test !:" << std::endl;
    UTF8string reversed_str = !test_str3;  // !
    std::cout << reversed_str << std::endl;
    UTF8string test_str6("étudiant");
    UTF8string reversed_str2 = !test_str6;
    std::cout << reversed_str2 << std::endl;
    return 0;
}
