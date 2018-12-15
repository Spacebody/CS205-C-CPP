#include <iostream>
#include "Box.hpp"

int main(int argc, char *argv[])
{
    //test
    Box box_0(-1, -3, 1000000);
    Box box(5, 5, 5);               // constructor
    std::cout << box << std::endl;  // test <<
    // test memberfunctions
    std::cout << "Length: " << box.getLength() << std::endl;
    std::cout << "Height: " << box.getHeight() << std::endl;
    std::cout << "Breadth: " << box.getBreadth() << std::endl;
    std::cout << "The volume: " << box.CalculateVolume() << std::endl;
    Box box2(5, 6, 6);
    if(box < box2) // test <
        std::cout << "box is smaller." << std::endl;
    else
        std::cout << "No, box is not smaller." << std::endl;
}