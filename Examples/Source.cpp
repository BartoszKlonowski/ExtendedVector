#include <iostream>

#include "Examples/CitiesFilteringApplication.cpp"


int main()
{
    std::cout << "SharpVector - Examples application!" << std::endl;

    Examples::ExampleApplication1 example1;

    return static_cast<int>(example1.Run());
}
