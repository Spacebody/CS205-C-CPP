#ifndef UTF8STRING_HPP
#define UTF8STRING_HPP

#include <iostream>
#include <cstring>
#include <string.h>

// definition of class
class UTF8string
{
    private:
      std::string str; // store string

    public:                           
      explicit UTF8string(const std::string s): str(s) {}  // constructor
      explicit UTF8string() {}                             // another constructor, without initialization
      UTF8string(const UTF8string &s): str(s.content()) {} // copy constructor
      ~UTF8string() {}                                     // destructor
      UTF8string &operator=(const UTF8string &s);          // assignment

      /* Utilities */
      int length() const;                                                 // return the length in characters
      int bytes() const;                                                  // return the length in bytes
      int find(const std::string substr) const;                                 // find the position of the substr
      int replace(const UTF8string &to_remove, const UTF8string &replacement);  // replace to_remove with replacement in pure C style
      int replace2(const UTF8string &to_remove, const UTF8string &replacement); // replace to_remove with replacement in C++ style
      std::string content() const;                                        // get the content of the string;
      
      /* Operators */
      friend std::ostream &operator<<(std::ostream &os, UTF8string &str);  // output the content
      friend UTF8string operator+(const UTF8string &add_1, const UTF8string &add_2);  // concatenate strings
      UTF8string &operator+=(const UTF8string &add);  // increment
      friend UTF8string operator*(const UTF8string &prod, const int repeation);  // repeat content
      friend UTF8string operator*(const int repeation, const UTF8string &prod);
      UTF8string operator!();  // reverse the string
};

#endif
