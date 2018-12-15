#include "Box.hpp"

// the function get the data should be 'const'
int Box::getLength() const
{
    return this->l;
}

int Box::getHeight() const
{
    return this->h;
}

int Box::getBreadth() const
{
    return this->b;
}

long long Box::CalculateVolume() const
{
    return (long long)(this->l * this->h * this->b);
}


// friend cannot use 'this' pointer
std::ostream &operator<<(std::ostream &os, const Box &box)
{
    // os << box.l << " " << box.b << " " << box.h;
    os << box.l << " " << box.b << " " << box.h;
    return os;
}

bool operator<(const Box &A, const Box &B)
{
    if(A.l < B.l)  // A.l < B.l
        return true;
    else if(A.b < B.b && A.l == B.l)  // A.b < B.b and A.l == B.l
        return true;
    else if (A.h < B.h && A.b == B.b && \
            A.l == B.l)  // A.h < B.h and A.b == B.b and A.l == B.l
        return true;
    else
        return false;  // otherwise, return as false
}
