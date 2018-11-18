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
                (char *)malloc(sizeof(char) * (this->bytes() - total_movement + 1));
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
                (char *)malloc(sizeof(char) * (this->bytes() + difference));
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

std::string UTF8string::content()
{
    return this->str;
}