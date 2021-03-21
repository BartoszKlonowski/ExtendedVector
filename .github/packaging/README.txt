# ExtendedVector #

Thank you for using this utility!
The full support and more information can be found in the official project's repository:
  https://github.com/BartoszKlonowski/ExtendedVector

---

This project is the extension of `std::vector<T>` from STL but based on .NET Framework `List<T>`.
It means, that all of features and methods provided by `List<T>` should also be available in the implemented `std::vector<T>` extension: `Cx::Vector<T>`.

The goal of this project was to create the tool which will make the usage of standard `std::vector<T>` even easier when it comes to complex yet typical operations done on collections which are currently not a part of the *vector* header, but require more includes and more LOC.

Please check the official documentation of `std::vector<T>`:
  https://en.cppreference.com/w/cpp/container/vector
and `System.Collections.Generic.List<T>`:
  https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=netframework-4.8
to see the two bases of this product and how it connects both of them.
  
---
  
## Installation & Usage ##

To use this tool:
* Download the archived release package,
* Unpack the release package and place the main implementation's header (which is *Vector.hpp*) in any directory within your project (for example "*Dependencies*" or "*3rdParties*"),
* Include the *Vector.hpp* header in your implementation and call the `Cx::Vector<T>` to instantiate the container.

**NOTE:**
ExtendedVector already uses several other includes from standard library, such as the following:
*vector*, *iostream*, *algorithm*, *functional*

---


## Documentation ##

This project fills the gap between the `std::vector<T>` and `System.Collections.Generic.List<T>` which means that it brings all the features already available in the `List<T>` to the `std::vector<T>`, making a `Cx::Vector<T>` in result.
Each method implemented within the `Cx::Vector<T>` corresponds to the same method in the `List<T>` from .NET.
So to check the method's documentation in details please check the .NET's official documentation of `List<T>` methods:
  https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=netframework-4.8#methods
section.
The methods already available in the original `std::vector<T>` are still available unchanged when using `Cx::Vector<T>`.

**NOTE:** Each method implemented in the *Vector.hpp* header are also covered with the *doxygen* comments (`///`), so each code editor supporting displaying them will show the method documented each time it is called within your code.

The presentation of some of the Cx::Vector abilities is done in the *Examples* project's source code files.
So to fully check the abilities of the ExtendedVector utility, please go to the Examples:
  https://github.com/BartoszKlonowski/ExtendedVector/tree/main/Examples
directory.

Below you can find just a short demo of what the *ExtendedVector* project is all about and what are the example benefits of using it:
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

---

## Contributing ##

If you would like to contribute to the *ExtendedVector* project, you are more than welcome!
Any contribution is to make the project better and to improve the developer's experience.
So if you'd like to contribute, you can do this in one of the following ways:

* Create an Issue:
    https://github.com/BartoszKlonowski/ExtendedVector/issues/new
  and let the author handle it
  Each issue created in the Issues:
    https://github.com/BartoszKlonowski/ExtendedVector/issues
  section gives a chance of improving the project and make it even more useful.

* Create the Pull Request:
    https://github.com/BartoszKlonowski/ExtendedVector/compare with the desired changes
  After a detailed review it will be merged.
  Please remember to give the detailed description of why such change is needed, what is the test plan and what are the details of your implementation. This will make the review easier and quicker.
  Please also remember to check the unit tests and implement additional tests in case of providing the project with some new features/new code.

---

## Thank you! ##

If you like this project, or you consider it helpfull, please share your opinion with the author or just give it a star!
