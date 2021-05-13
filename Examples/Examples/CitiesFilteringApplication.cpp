// Copyright (c) Cx Code - Bartosz Klonowski.
// Licensed under the MIT License.

#include "../ErrorCodes.hpp"
#include "../../Source/Vector.hpp"
#include <string>
#include <iostream>


namespace Examples
{
    class City
    {
    public:
        City() = default;

        City( const std::string& name, const unsigned int populationCount ) : name{name}, populationCount{populationCount}
        {
        }

        bool operator==( const City& left ) const
        {
            return left.name == this->name && left.populationCount == this->populationCount;
        }

        bool operator<( const City& left ) const
        {
            return left.populationCount < this->populationCount;
        }

        const unsigned int PopulationCount() const noexcept
        {
            return populationCount;
        }

        const std::string Name() const noexcept
        {
            return name;
        }

    private:
        std::string name;
        unsigned int populationCount;
    };


    class CitiesFilter
    {
    public:
        CitiesFilter( std::initializer_list<City> data )
        {
            cities.AddRange( data );
        }

        void AddNewCity( const City& newCity )
        {
            cities.push_back( newCity );
        }

        void RemoveCity( City cityToRemove )
        {
            cities.Remove( cityToRemove );
        }

        std::string GetNameOfMostPopulated() noexcept
        {
            auto sortedCities = cities;
            sortedCities.Sort();
            return sortedCities[0].Name();
        }

        City FindByName( std::string name )
        {
            return cities.Find( [=]( City c )->bool
                {
                    return c.Name() == name;
                } );
        }

    private:
        Cx::Vector<City> cities;
    };


    class ExampleApplication1
    {
    public:
        ErrorCodes Run()
        {
            auto citiesFilter = CitiesFilter(
                {
                    City( "Warsaw", 10000 ),
                    City( "New York", 2344000 ),
                    City( "Miami", 2306043 ),
                    City( "Philadelfia", 3434322 ),
                    City( "Wroclaw", 899000 ),
                    City( "Bydgoszcz", 355000 ),
                    City( "Moscow", 1770100 ),
                    City( "Paris", 1055799 ),
                    City( "Madrid", 4999000 ),
                    City( "Tokyo", 6799899 )
                } );

            if( citiesFilter.GetNameOfMostPopulated() != "Tokyo" )
            {
                std::cout << "ExampleApplication1 - GetNameOfMostPopulated() failed!" << std::endl;
                return ErrorCodes::Error;
            }

            const auto cityToRemove = City( "Bydgoszcz", 355000 );
            citiesFilter.RemoveCity( cityToRemove );
            if( citiesFilter.FindByName( "Bydgoszcz" ).Name() != "" )
            {
                std::cout << "ExampleApplication1 - RemoveCity( \"Bydgosz\", 355000) failed!" << std::endl;
                return ErrorCodes::Error;
            }

            citiesFilter.AddNewCity( City( "Krakow", 456098 ) );
            if( citiesFilter.FindByName( "Krakow" ).PopulationCount() != 456098 )
            {
                std::cout << "ExampleApplication1 - AddNewCity( \"Krakow\", 456098) failed!" << std::endl;
                return ErrorCodes::Error;
            }

            citiesFilter.RemoveCity( City( "Tokyo", 6799899 ) );
            if( citiesFilter.FindByName( "Tokyo" ).Name() == "" )
            {
                if( citiesFilter.GetNameOfMostPopulated() != "Madrid" )
                {
                    std::cout << "ExampleApplication1 - GetNameOfMostPopulated() failed!" << std::endl;
                    return ErrorCodes::Error;
                }
            }
            else
            {
                std::cout << "ExampleApplication1 - FindByName(\"Tokyo\") failed!" << std::endl;
                return ErrorCodes::Error;
            }

            return ErrorCodes::Success;
        }
    };
}
