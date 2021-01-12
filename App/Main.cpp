#include <iostream>
#include "Vector.hpp"
#include <string>



template <class T>
void Print( std::vector<T> vector )
{
    std::cout << "\nPrinting Cx::Vector with " << vector.size() << " elements inside:" << std::endl;
    for( auto element : vector )
        std::cout << element << " ";
    std::cout << std::endl;
}



int main( int argc, char** argv )
{
    Cx::Vector<std::string> vector;
    vector.push_back( "Hello" );
    vector.push_back( "World!" );
    Print( vector );

    vector.clear();
    Print( vector );

    vector = { "Elephant", "Cat", "Mouse", "Wolf", "Dinosaur", "Tiger", "Dog", "Eagle", "Cow", "Snake" };
    Print( vector );

    auto animalsByCLetter = vector.FindAll( []( const std::string& animal )->bool
        {
            return animal[0] == 'C';
        } );
    Print( animalsByCLetter );

    vector.RemoveAll( []( const std::string& element )->bool
        {
            return element.length() > 4;
        } );
    Print( vector );

    vector.ForEach( []( std::string& element )
        {
            element = std::string("Animal:") + element;
        } );
    Print( vector );

    if( vector.Contains("Animal:Dog") )
        std::cout << "\nIndex of 'Animal:Dog' is: " << vector.IndexOf( "Animal:Dog" ) << std::endl;

    auto indexOfCow = vector.IndexOf( "Animal:Cow" );
    vector.RemoveAt( indexOfCow );
    Print( vector );

    std::cin.get();
}
