# Vector #

This project is the extension of std::vector<T> from STL but based on .NET Framework List<T>.  
It means, that all of features and methods provided by [List<T>](https://docs.microsoft.com/pl-pl/dotnet/api/system.collections.generic.list-1?view=netframework-4.8#methods)
should also be available in the implmemented std::vector<T> extension: Cx::Vector<T>.  
  
  
---
  
## The goal ##

The goal of this project was to create the extension of std::vector<T> which will be easy to use for basic operations like:  
searching, sorting, getting indexes, performing actions for each of the element, checking existence of specific element,  
and many other, which are currently not included in just the *vector* header, but require more includes and more LOC.  
  
The other goal of this project was to practice and improve the skills in:

* C++11/14/17 programming
* Unit testing with Google Tests
* Best practices when creating software and libraries
  
  
---
  
## Technology ##

As already mentioned this project was developed using the following tools:

|      Name     | Version |
|:-------------:|:-------:|
|       C++     |    17   |
|    GNU GCC    |  7.3.0  |
| Visual Studio |  16.5.4 |
|     CMake     |  3.17.1 |
|  Google Test  |  1.10.0 |
  
  
---
  
## Development ##

The whole development process was based on a single *master* branch.

More branches would only be used in this project for refactoring, risky bugfixing, etc.

This approach had a chance of being successful only because of one developer working on the project.

With proper commit messages and consequent commiting after each step it was possible to still keep the trackability and an order in development.


---


## Results ##

The presentation of some of the Cx::Vector abilities is done in the *App/Main.cpp* source code file.  
The `main()` method shows the usage of this container and prints it's results to the console.  
Below the `main()` source can be found:  

```cpp
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
```

which gives the following output:

```
Printing Cx::Vector with 2 elements inside:
Hello World!

Printing Cx::Vector with 0 elements inside:


Printing Cx::Vector with 10 elements inside:
Elephant Cat Mouse Wolf Dinosaur Tiger Dog Eagle Cow Snake

Printing Cx::Vector with 2 elements inside:
Cat Cow

Printing Cx::Vector with 4 elements inside:
Cat Wolf Dog Cow

Printing Cx::Vector with 4 elements inside:
Animal:Cat Animal:Wolf Animal:Dog Animal:Cow

Index of 'Animal:Dog' is: 2

Printing Cx::Vector with 3 elements inside:
Animal:Cat Animal:Wolf Animal:Dog
```

