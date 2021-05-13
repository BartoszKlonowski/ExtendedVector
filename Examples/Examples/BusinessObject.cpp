// Copyright (c) Cx Code - Bartosz Klonowski.
// Licensed under the MIT License.

#include "../ErrorCodes.hpp"
#include "../../Source/Vector.hpp"
#include <string>


namespace Examples
{
    class Part
    {
    public:
        std::string partName;

        int partID;

        Part( std::string partName, int partID ) : partName{ partName }, partID{ partID }
        {
        }

        std::string ToString()
        {
            return std::string( "ID: " ).append( std::to_string( partID ) ).append( "   Name: " ).append( partName );
        }

        bool operator==( const Part& other ) const
        {
            return partID == other.partID;
        }
    };

    class BusinessObjectExample
    {
    public:
        ErrorCodes Run()
        {
            // Create a list of parts.
            Cx::Vector<Part> parts;

            // Add parts to the list.
            parts.push_back( Part( "crank arm", 1234 ) );
            parts.push_back( Part( "chain ring", 1334 ) );
            parts.push_back( Part( "regular seat", 1434 ) );
            parts.push_back( Part( "banana seat", 1444 ) );
            parts.push_back( Part( "cassette", 1534 ) );
            parts.push_back( Part( "shift lever", 1634 ) );

            // Write out the parts in the list. This will call the overridden ToString method in the Part class.
            parts.ForEach( []( Part p )
                {
                    std::cout << p.ToString() << std::endl;
                } );

            // Check the list for part #1734. This calls the IEquatable.Equals method of the Part class, which checks the PartId for equality.
            std::cout << "\nContains(\"1734\"): {" << parts.Contains( Part( "", 1734 ) ) << "}" << std::endl;

            // Insert a new item at position 2.
            std::cout << "\nInsert(2, \"1834\")" << std::endl;
            parts.insert( parts.cbegin() + 2, Part( "brake lever", 1834 ) );

            parts.ForEach( []( Part p )
                {
                    std::cout << p.ToString() << std::endl;
                } );

            std::cout << "\nParts[3]: {" << parts[3].ToString() << "{" << std::endl;

            std::cout << "\nRemove(\"1534\")" << std::endl;

            // This will remove part 1534 even though the PartName is different, because the Equals method only checks PartId for equality.
            parts.Remove( Part( "cogs", 1534 ) );

            parts.ForEach( []( Part p )
                {
                    std::cout << p.ToString() << std::endl;
                } );
            std::cout << "\nRemoveAt(3)" << std::endl;
            // This will remove the part at index 3.
            parts.RemoveAt( 3 );

            parts.ForEach( []( Part p )
                {
                    std::cout << p.ToString() << std::endl;
                } );

            /*

             ID: 1234   Name: crank arm
             ID: 1334   Name: chain ring
             ID: 1434   Name: regular seat
             ID: 1444   Name: banana seat
             ID: 1534   Name: cassette
             ID: 1634   Name: shift lever

             Contains("1734"): False

             Insert(2, "1834")
             ID: 1234   Name: crank arm
             ID: 1334   Name: chain ring
             ID: 1834   Name: brake lever
             ID: 1434   Name: regular seat
             ID: 1444   Name: banana seat
             ID: 1534   Name: cassette
             ID: 1634   Name: shift lever

             Parts[3]: ID: 1434   Name: regular seat

             Remove("1534")

             ID: 1234   Name: crank arm
             ID: 1334   Name: chain ring
             ID: 1834   Name: brake lever
             ID: 1434   Name: regular seat
             ID: 1444   Name: banana seat
             ID: 1634   Name: shift lever

             RemoveAt(3)

             ID: 1234   Name: crank arm
             ID: 1334   Name: chain ring
             ID: 1834   Name: brake lever
             ID: 1444   Name: banana seat
             ID: 1634   Name: shift lever
            */
            return ErrorCodes::Success;
        }
    };
}
