#include "utf8.h"
#include "UTF8string.hpp"

UTF8string::UTF8string(std::string str)
{
    this->str = str;
}

UTF8string::UTF8string() {}

UTF8string::~UTF8string() {}

UTF8string &UTF8string::operator=(const UTF8string &s)
{
    this->str = s.str;
    return *this;
}

int UTF8string::length()
{
    return utf8_charlen((unsigned char *)this->str.c_str()); // get length in character
}

int UTF8string::bytes()
{
    int lenptr = 0; // record the length of the character in bytes
    int bytes = 0;    // count position
    unsigned char *pt = (unsigned char *)this->str.c_str();
    // move ptr to the position
    while (*pt != '\0')
    {
        utf8_to_codepoint(pt, &lenptr);
        pt += lenptr;
        bytes += lenptr;
    }
    return bytes; // get length in bytes
}

int UTF8string::find(std::string substr)
{
    // get position first
    unsigned char *pos_ptr =
            utf8_search((unsigned char *)this->str.c_str(), (unsigned char *)substr.c_str());
    if (pos_ptr == NULL)
        return -1;  // if not found
    int lenptr = 0; // record the length of the character in bytes
    int pos = 0;    // count position
    unsigned char *pt = (unsigned char *)this->str.c_str();
    // move ptr to the position
    while (pt != pos_ptr)
    {
        utf8_to_codepoint(pt, &lenptr);
        pt += lenptr;
        ++pos;
    }
    ++pos; // need an addition increment
    return pos;
}

int UTF8string::replace(UTF8string &to_remove, UTF8string &replacement)
{
    if (to_remove.bytes() >= replacement.bytes()) // if the length of to_remove > the length of replacement
    {
        unsigned char *pos_ptr =
                utf8_search((unsigned char *)this->str.c_str(), (unsigned char *)to_remove.str.c_str());
        if (pos_ptr == NULL)
            return -1;
        int lenptr = 0;
        unsigned char *pt = (unsigned char *)this->str.c_str();
        // move the pointer to the position
        while (pt != pos_ptr)
        {
            utf8_to_codepoint(pt, &lenptr);
            pt += lenptr;
        }
        strcpy((char *)pt, (char *)replacement.str.c_str()); // copy the replacement to to_remove
    }
    else // if the length of to_remove < the length of replacement
    {
        // allocate a new memory
        char *tmp =
                (char *)malloc(sizeof(char) * (this->bytes() + replacement.bytes() - to_remove.bytes()));
        if (tmp == NULL)
            return -1;  // not enough space
        strcpy(tmp, this->str.c_str()); // copy original string
        unsigned char *pos_ptr =
            utf8_search((unsigned char *)tmp, (unsigned char *)to_remove.str.c_str());
        if (pos_ptr == NULL)
            return -1;
        int lenptr = 0;
        unsigned char *pt = (unsigned char *)tmp;
        while (pt != pos_ptr)
        {
            utf8_to_codepoint(pt, &lenptr);
            pt += lenptr;
        }
        strcpy((char *)pt, (char *)replacement.str.c_str());
        this->str = tmp;  // call constructor to re-assign the string
    }
    return 0;
}