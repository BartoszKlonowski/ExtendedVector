#include "../ErrorCodes.hpp"
#include "../../Source/Vector.hpp"

namespace Examples
{
    using Point = std::pair<int, int>;

    class ExampleApplication2
    {
    public:
        ErrorCodes Run()
        {
            Cx::Vector<Point> coordinates
            {
                Point( {1,4} ),
                Point( {2,5} ),
                Point( {-1,4} ),
                Point( {-3,-6} ),
                Point( {4,-6} ),
                Point( {2,6} ),
                Point( {1,1} ),
                Point( {4,0} ),
                Point( {12,19} ),
                Point( {4,-4} )
            };

            auto negatives = coordinates.FindAll( []( Point p )->bool
                {
                    return p.first < 0 || p.second < 0;
                } );
            if( negatives.size() != 4 )
            {
                std::cout << "ExampleApplication2 - FindAll() failed!" << std::endl;
                return ErrorCodes::Error;
            }

            if( coordinates.Exists( []( Point p )->bool
                {
                    return p.first == 0 && p.second == 0;
                } ) )
            {
                std::cout << "ExampleApplication2 - Exists( Point(0,0) ) failed!" << std::endl;
                return ErrorCodes::Error;
            }

            if( !coordinates.Exists( []( Point p )->bool
                {
                    return p.first == 0 || p.second == 0;
                } ) )
            {
                std::cout << "ExampleApplication2 - Exists( Point(0 || 0) ) failed!" << std::endl;
                return ErrorCodes::Error;
            }

            coordinates.ForEach([](Point& p)
                {
                    p.first *= -1;
                    p.second *= -1;
                });
            negatives = coordinates.FindAll( []( Point p )->bool
                {
                    return p.first < 0 || p.second < 0;
                } );
            if( negatives.size() != 9 )
            {
                std::cout << "ExampleApplication2 - FindAll() failed!" << std::endl;
                return ErrorCodes::Error;
            }


            return ErrorCodes::Success;
        }
    };
}
