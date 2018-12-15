#ifndef BOX_HPP
#define BOX_HPP

#include <iostream>

class Box
{
  private:
    int l;  // length 
    int b;  // breathe
    int h;  // height

  public:
    Box() : l(0), b(0), h(0) {}  // default constructor
    Box(int length, int breadth, int height) : l(length), b(breadth), h(height) 
    {
        // 
        try
        {
            if (l < 0 || b < 0 || h < 0 || l > 100000 || b > 100000 || h > 100000)
            {
                throw std::string("ERROR: length or breadth or height cannot be larger than 0 and less than 100000.");
            }
        }
        catch (std::string s) 
        {
            std::cout << s << std::endl;
        }
    }  // parameterized constructor
    Box(const Box &box); // copy constructor
    ~Box() {}  // destrcutor

    int getLength() const;  // get length
    int getBreadth() const;  // get breath
    int getHeight() const;  // get height
    long long CalculateVolume() const; // calculate the volume

    friend std::ostream &operator<<(std::ostream &os, const Box &box);  // overload <<
    friend bool operator<(const Box &A, const Box &B);  // overload <

};

#endif
