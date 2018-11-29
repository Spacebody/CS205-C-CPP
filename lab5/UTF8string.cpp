#include "utf8.h"
#include "UTF8string.hpp"
#include "string"

UTF8string &UTF8string::operator=(const UTF8string &s)
{
    this->str = s.str;
    return *this;
}

int UTF8string::length() const
{
    return utf8_charlen((unsigned char *)this->str.c_str()); // get length in character
}

int UTF8string::bytes() const
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

int UTF8string::find(const std::string substr) const
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

int UTF8string::replace(const UTF8string &to_remove, const UTF8string &replacement)
{
    int is_replaced = 0;
    if (to_remove.bytes() == replacement.bytes()) // length of to_remove == the length of replacement
    {
        unsigned char *pos_ptr = NULL;
        while ((pos_ptr = utf8_search((unsigned char *)this->str.c_str(), \
                (unsigned char *)to_remove.str.c_str())))
        {
            is_replaced = 1;
            int lenptr = 0;
            unsigned char *pt = (unsigned char *)this->str.c_str();
            // move the pointer to the position
            while (pt != pos_ptr)
            {
                utf8_to_codepoint(pt, &lenptr);
                pt += lenptr;
            }
            // copy the replacement to to_remove
            strncpy((char *)pt, (char *)replacement.str.c_str(), (size_t)to_remove.bytes()); 
        }
    }
    else if (to_remove.bytes() > replacement.bytes()) // length of to_remove > the length of replacement
    {
        unsigned char *pos_ptr = NULL;
        int movement = to_remove.bytes() - replacement.bytes();
        int total_movement = 0;
        while ((pos_ptr = utf8_search((unsigned char *)this->str.c_str(),
                                      (unsigned char *)to_remove.str.c_str())))
        {
            is_replaced = 1;
            total_movement += movement;
            int lenptr = 0;
            unsigned char *pt = (unsigned char *)this->str.c_str();
            // move the pointer to the position
            while (pt != pos_ptr)
            {
                utf8_to_codepoint(pt, &lenptr);
                pt += lenptr;
            }
            // copy the replacement to to_remove
            strncpy((char *)pt, (char *)replacement.str.c_str(), (size_t)replacement.bytes()); 
            unsigned char *tmp_ptr = pt;
            pt += replacement.bytes();
            tmp_ptr += to_remove.bytes();
            strcpy((char *)pt, (char *)tmp_ptr);
        }
        if(is_replaced)
        {
            char *tmp =
                (char *)malloc(sizeof(char) * ((unsigned long)(this->bytes() - total_movement + 1)));
            if (tmp == NULL) return -1;  // not enough space
            strncpy(tmp, this->str.c_str(), (size_t)(strlen(this->str.c_str()) + 1)); // copy original string
            this->str = tmp;
        }
    }
    else // length of to_remove < the length of replacement
    {
        unsigned char *pos_ptr = NULL;
        int difference = replacement.bytes() - to_remove.bytes();
        while ((pos_ptr = utf8_search((unsigned char *)this->str.c_str(), (unsigned char *)to_remove.str.c_str())))
        {
            is_replaced = 1;
            // allocate a new memory
            char *tmp =
                (char *)malloc(sizeof(char) * ((unsigned long)(this->bytes() + difference)));
            if (tmp == NULL) return -1; // not enough space
            int lenptr = 0;
            unsigned char *pt = (unsigned char *)this->str.c_str();
            while (pt != pos_ptr)
            {
                utf8_to_codepoint(pt, &lenptr);
                pt += lenptr;
            }
            char *tmp_ptr = tmp;
            strncpy(tmp_ptr, this->str.c_str(), (size_t)((char *)pt - this->str.c_str()));                                                 // substring before to_remove
            tmp_ptr += (char *)pt - this->str.c_str();  // move the position
            // replace to_remove
            strncpy((char *)tmp_ptr, (char *)replacement.str.c_str(), (size_t)(replacement.bytes())); 
            tmp_ptr += replacement.bytes();
            strcpy((char *)tmp_ptr, (char *)(pt + to_remove.bytes()));
            this->str = tmp; // call constructor to re-assign the string
        }
    }
    return is_replaced == 1 ? 0 : -1;  // -1 means not found
}

int UTF8string::replace2(const UTF8string &to_remove, const UTF8string &replacement)
{
    if(to_remove.length() == 0 || replacement.length() == 0) return -1;
    else
    {
        int pos = 0;
        for(; (pos = (int)this->str.find(to_remove.content())) != std::string::npos; pos = 0)
        {
            this->str.replace((unsigned long)pos, (unsigned long)to_remove.bytes(), replacement.content());
        }
    }
    return 1;
}

std::string UTF8string::content() const
{
    return this->str;  // return the content
}

std::ostream &operator<<(std::ostream &os, UTF8string &str)
{
    os << str.content();  // print the content
    return os;
}

UTF8string operator+(const UTF8string &add_1, const UTF8string &add_2)
{
    return UTF8string(add_1.content() + add_2.content());  // combine the string, add_1 + add_2
}

UTF8string &UTF8string::operator+=(const UTF8string &add_1)
{
    this->str = this->str + add_1.content(); // concatenate this->str and add_1
    return *this;
}

UTF8string operator*(const UTF8string &prod, const int repeation)
{
    std::string tmp;
    for(int i = 0; i < repeation; ++i)
    {
        tmp += prod.content(); // repeat the content
    }
    return UTF8string(tmp);
}

UTF8string operator*(const int repeation, const UTF8string &prod)
{
    std::string tmp;
    for(int i = 0; i < repeation; ++i)
    {
        tmp += prod.content();
    }
    return UTF8string(tmp);
}

UTF8string UTF8string::operator!()
{
    std::string reversed;
    int lenptr = 0;
    int pos = 0;
    unsigned char *pt = (unsigned char *)this->str.c_str();
    while(reversed.length() < this->str.length())
    {
        utf8_to_codepoint(pt, &lenptr);
        // reverse string by concatenate the character reversely
        reversed = this->str.substr((unsigned long)pos, (unsigned long)lenptr) + reversed; 
        pt += lenptr;
        pos += lenptr;
    }
    return UTF8string(reversed);
}
