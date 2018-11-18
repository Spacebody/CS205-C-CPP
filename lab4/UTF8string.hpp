#ifndef __UTF8STRING_HPP
#define __UTF8STRING_HPP

#include <iostream>
#include <cstring>
#include <string.h>

// definition of class
class UTF8string
{
    private:
      std::string str; // store string

    public:                           
      explicit UTF8string(std::string str);       // constructor
      explicit UTF8string();                      // another constructor, without initialization
      UTF8string(const UTF8string &s);            // copy constructor
      virtual ~UTF8string();                      // destructor
      UTF8string &operator=(const UTF8string &s); // assignment

      /* Utilities */
      int length();                                                // return the length in characters
      int bytes();                                                 // return the length in bytes
      int find(std::string substr);                                // find the position of the substr
      int replace(UTF8string &to_remove, UTF8string &replacement); // replace to_remove with replacement
      std::string content();                                       // get the content of the string;
};

#endif