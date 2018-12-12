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
    os << box.getLength() << " " << box.getBreadth() << " " << box.getHeight();
    return os;
}

bool operator<(const Box &A, const Box &B)
{
    if(A.getLength() < B.getLength())  // A.l < B.l
        return true;
    else if(A.getBreadth() < B.getBreadth() && A.getLength() == B.getLength())  // A.b < B.b and A.l == B.l
        return true;
    else if (A.getHeight() < B.getHeight() && A.getBreadth() == B.getBreadth() && \
            A.getLength() == B.getLength())  // A.h < B.h and A.b == B.b and A.l == B.l
        return true;
    else
        return false;  // otherwise, return as false
}
