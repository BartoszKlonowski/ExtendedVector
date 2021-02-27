#include <iostream>

#include "Examples/CitiesFilteringApplication.cpp"
#include "Examples/Coordinates.cpp"


int main()
{
    std::cout << "SharpVector - Examples application!" << std::endl;

    Examples::ExampleApplication1 example1;
    Examples::ExampleApplication2 example2;

    auto result = static_cast<int>(example1.Run()) + static_cast<int>(example2.Run());

    return result;
}
