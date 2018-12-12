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
    Box(int length, int breadth, int height) : l(length), b(breadth), h(height) {}  // parameterized constructor
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
