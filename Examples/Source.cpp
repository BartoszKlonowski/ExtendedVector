#include <iostream>

#include "Examples/CitiesFilteringApplication.cpp"
#include "Examples/Coordinates.cpp"
#include "Examples/BusinessObject.cpp"


int main()
{
    std::cout << "ExtendedVector - Examples application!" << std::endl;

    Examples::ExampleApplication1 example1;
    Examples::ExampleApplication2 example2;
    Examples::BusinessObjectExample example3;

    auto result = static_cast<int>(example1.Run()) + static_cast<int>(example2.Run()) + static_cast<int>(example3.Run());

    return result;
}
