#include "CppUnitTest.h"
#include "Vector.hpp"
#include <array>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Cx
{
	TEST_CLASS(ExtendedVectorBasicTests)
	{
    private:
        Vector<int> vector;

        class Entity
        {
        public:
            Entity( int i, float j ) : i{ i }, j{ j } {}
            Entity( int i ) : i{ i } { j = 0; }
            Entity() = default;

            bool operator==( const Entity& element ) const
            {
                return this->i == element.i && this->j == element.j;
            }

            bool operator<( const Entity& e )
            {
                return i < e.i;
            }

            int i;
            float j;
        };

    public:
		
		TEST_METHOD( AddRangeByInitializerListTest )
        {
            vector.AddRange( { 1,4,12,8 } );
            Assert::IsTrue( vector[0] == 1 );
            Assert::IsTrue( vector[1] == 4 );
            Assert::IsTrue( vector[2] == 12 );
            Assert::IsTrue( vector[3] == 8 );
        }


        TEST_METHOD( AddRangeByStandardArrayTest )
        {
            int range[] = { 4,6,33,124 };
            vector.AddRange( range, 4 );
            Assert::IsTrue( vector[0] == 4 );
            Assert::IsTrue( vector[1] == 6 );
            Assert::IsTrue( vector[2] == 33 );
            Assert::IsTrue( vector[3] == 124 );
        }


        TEST_METHOD( AddRangeByAnotherCxVectorGivenByReference )
        {
            Vector<int> newVector;
            newVector.AddRange( { 1,15,23,56 } );
            vector.AddRange( newVector );
            Assert::IsTrue( vector[0] == 1 );
            Assert::IsTrue( vector[1] == 15 );
            Assert::IsTrue( vector[2] == 23 );
            Assert::IsTrue( vector[3] == 56 );
        }


        TEST_METHOD( AddRangeByAnotherCxVectorGivenByRValue )
        {
            Vector<int> newVector;
            newVector.AddRange( { 1,15,23,56 } );
            vector.AddRange( std::move( newVector ) );
            Assert::IsTrue( vector[0] == 1 );
            Assert::IsTrue( vector[1] == 15 );
            Assert::IsTrue( vector[2] == 23 );
            Assert::IsTrue( vector[3] == 56 );
        }


        TEST_METHOD( ContainerWithBasicTypesContainsAnElement )
        {
            vector.AddRange( { 2,56,2,34,8,10 } );
            Assert::IsFalse( vector.Contains( 11 ) );
            Assert::IsTrue( vector.Contains( 56 ) );
            Assert::IsFalse( vector.Contains( 9 ) );
            Assert::IsTrue( vector.Contains( 10 ) );

            vector.AddRange( { 3,5,7,12 } );
            Assert::IsFalse( vector.Contains( 13 ) );
            Assert::IsTrue( vector.Contains( 7 ) );
            Assert::IsFalse( vector.Contains( 6 ) );
            Assert::IsTrue( vector.Contains( 12 ) );
        }


        TEST_METHOD( ContainerWithCustomTypesContainsAnElement )
        {
            Vector<Entity> newVector;
            newVector.AddRange( {
                Entity( 2,8 ),
                Entity( 3,10 ),
                Entity( 4,12 ),
                Entity( 0,-2 ),
                Entity( -5,0.4f )
                } );

            Assert::IsFalse( newVector.Contains( Entity( 3, 12 ) ) );
            Assert::IsTrue( newVector.Contains( Entity( 3, 10 ) ) );
            Assert::IsFalse( newVector.Contains( Entity( 1, -1 ) ) );
            Assert::IsTrue( newVector.Contains( Entity( -5, 0.4f ) ) );
        }


        TEST_METHOD( SortingBasicTypesAtWholeScopeWithDefaultComparer )
        {
            vector.AddRange( { 4,13,2,56,3 } );
            vector.Sort();
            Assert::IsTrue( vector[0] == 2 );
            Assert::IsTrue( vector[1] == 3 );
            Assert::IsTrue( vector[2] == 4 );
            Assert::IsTrue( vector[3] == 13 );
            Assert::IsTrue( vector[4] == 56 );
        }


        TEST_METHOD( SortingCustomTypesAtWholeScopeWithDefaultComparer )
        {
            Vector<Entity> newVector;
            newVector.AddRange( { Entity( 4 ),Entity( 13 ),Entity( 2 ),Entity( 56 ),Entity( 3 ) } );
            newVector.Sort();
            Assert::IsTrue( newVector[0].i == 2 );
            Assert::IsTrue( newVector[1].i == 3 );
            Assert::IsTrue( newVector[2].i == 4 );
            Assert::IsTrue( newVector[3].i == 13 );
            Assert::IsTrue( newVector[4].i == 56 );
        }


        TEST_METHOD( SortingBasicTypesAtSpecifiedScopeWithDefaultComparer )
        {
            vector.AddRange( { 4,13,2,56,3 } );
            vector.Sort( 1, 3 );
            Assert::IsTrue( vector[0] == 4 );
            Assert::IsTrue( vector[1] == 2 );
            Assert::IsTrue( vector[2] == 13 );
            Assert::IsTrue( vector[3] == 56 );
            Assert::IsTrue( vector[4] == 3 );
        }


        TEST_METHOD( SortingCustomTypesAtSpecificScopeWithDefaultComparer )
        {
            Vector<Entity> newVector;
            newVector.AddRange( { Entity( 4 ),Entity( 13 ),Entity( 56 ),Entity( 2 ),Entity( 3 ) } );
            newVector.Sort( 1, 3 );
            Assert::IsTrue( newVector[0].i == 4 );
            Assert::IsTrue( newVector[1].i == 2 );
            Assert::IsTrue( newVector[2].i == 13 );
            Assert::IsTrue( newVector[3].i == 56 );
            Assert::IsTrue( newVector[4].i == 3 );
        }


        TEST_METHOD( SortingBasicTypesAtWholeScopeWithCustomComparer )
        {
            vector.AddRange( { 4,13,2,56,3 } );
            vector.Sort( []( int a, int b )->bool
                {
                    return a > b;
                } );
            Assert::IsTrue( vector[0] == 56 );
            Assert::IsTrue( vector[1] == 13 );
            Assert::IsTrue( vector[2] == 4 );
            Assert::IsTrue( vector[3] == 3 );
            Assert::IsTrue( vector[4] == 2 );
        }

        TEST_METHOD( SortingCustomTypesAtSpecificScopeWithCustomComparer )
        {
            Vector<Entity> newVector;
            newVector.AddRange( { Entity( 4 ),Entity( 13 ),Entity( 2 ),Entity( 56 ),Entity( 3 ) } );
            newVector.Sort( 1, 3, []( Entity a, Entity b )->bool
                {
                    return a.i > b.i;
                } );
            Assert::IsTrue( newVector[0].i == 4 );
            Assert::IsTrue( newVector[1].i == 56 );
            Assert::IsTrue( newVector[2].i == 13 );
            Assert::IsTrue( newVector[3].i == 2 );
            Assert::IsTrue( newVector[4].i == 3 );
        }


        TEST_METHOD( BasicTypeElementExistsInTheContainer )
        {
            vector.AddRange( { 3,4,12,5,98,11 } );
            auto falsePredicate = []( const int& element )->bool {
                return element == 6;
            };
            auto truePredicate = []( const int& element )->bool {
                return element == 98;
            };
            Assert::IsFalse( vector.Exists( falsePredicate ) );
            Assert::IsTrue( vector.Exists( truePredicate ) );
        }


        TEST_METHOD( CustomTypeElementExistsInTheContainer )
        {
            Vector<Entity> newVector;
            newVector.AddRange( { Entity( 3 ),Entity( 4 ),Entity( 12 ),Entity( 5 ),Entity( 98 ),Entity( 11 ) } );
            auto falsePredicate = []( const Entity& element )->bool {
                return element.i == 6;
            };
            auto truePredicate = []( const Entity& element )->bool {
                return element.i == 98;
            };
            Assert::IsFalse( newVector.Exists( falsePredicate ) );
            Assert::IsTrue( newVector.Exists( truePredicate ) );
        }


        TEST_METHOD( CopyToArrayPointerWithCustomStartingIndexesOfBothArrays )
        {
            vector.AddRange( { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 } );
            int destinationArray[10] = { 0,1,2,3,4,5 };
            vector.CopyTo( 11, destinationArray, 7, 3 );
            Assert::IsTrue( destinationArray[7] == 11 );
            Assert::IsTrue( destinationArray[8] == 12 );
            Assert::IsTrue( destinationArray[9] == 13 );
        }

        TEST_METHOD( CopyToArrayPointerAllElements )
        {
            vector.AddRange( { 10,11,12,13,14,15,16,17,18,19 } );
            int destinationArray[10] = { 0,1,2,3,4,5 };
            vector.CopyTo( destinationArray, 10 );
            Assert::IsTrue( destinationArray[0] == 10 );
            Assert::IsTrue( destinationArray[6] == 16 );
            Assert::IsTrue( destinationArray[7] == 17 );
            Assert::IsTrue( destinationArray[8] == 18 );
        }

        TEST_METHOD( CopyToArrayPointerAllElementsWithCustomStartingIndex )
        {
            vector.AddRange( { 6,7,8,9 } );
            int destinationArray[10] = { 0,1,2,3,4,5 };
            vector.CopyTo( destinationArray, 10, 6 );
            Assert::IsTrue( destinationArray[0] == 0 );
            Assert::IsTrue( destinationArray[6] == 6 );
            Assert::IsTrue( destinationArray[7] == 7 );
            Assert::IsTrue( destinationArray[8] == 8 );
        }

        TEST_METHOD( CopyToVectorWithCustomStartingIndexesOfBothArrays )
        {
            vector.AddRange( { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 } );
            std::vector<int> destinationArray = { 0,1,2,3,4,5 };
            vector.CopyTo( 11, destinationArray, 3, 3 );
            Assert::IsTrue( destinationArray[3] == 11 );
            Assert::IsTrue( destinationArray[4] == 12 );
            Assert::IsTrue( destinationArray[5] == 13 );
            Assert::IsTrue( destinationArray[6] == 3 );
            Assert::IsTrue( destinationArray[7] == 4 );
            Assert::IsTrue( destinationArray[8] == 5 );
        }

        TEST_METHOD( CopyToVectorAllElements )
        {
            vector.AddRange( { 10,11,12,13,14,15,16,17,18,19 } );
            std::vector<int> destinationArray = { 0,1,2,3,4,5 };
            vector.CopyTo( destinationArray );
            Assert::IsTrue( destinationArray[0] == 10 );
            Assert::IsTrue( destinationArray[6] == 16 );
            Assert::IsTrue( destinationArray[7] == 17 );
            Assert::IsTrue( destinationArray[8] == 18 );
            Assert::IsTrue( destinationArray[10] == 0 );
            Assert::IsTrue( destinationArray[11] == 1 );
        }

        TEST_METHOD( CopyToVectorAllElementsWithCustomStartingIndex )
        {
            vector.AddRange( { 6,7,8,9 } );
            std::vector<int> destinationArray = { 0,1,2,3,4,5 };
            vector.CopyTo( destinationArray, 4 );
            Assert::IsTrue( destinationArray[0] == 0 );
            Assert::IsTrue( destinationArray[3] == 3 );
            Assert::IsTrue( destinationArray[4] == 6 );
            Assert::IsTrue( destinationArray[6] == 8 );
            Assert::IsTrue( destinationArray[7] == 9 );
            Assert::IsTrue( destinationArray[8] == 4 );
        }

        TEST_METHOD( CopyToArrayWithCustomStartingIndexesOfBothArrays )
        {
            vector.AddRange( { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 } );
            std::array<int, 10> destinationArray = { 0,1,2,3,4,5 };
            vector.CopyTo( 11, destinationArray, 7, 3 );
            Assert::IsTrue( destinationArray[7] == 11 );
            Assert::IsTrue( destinationArray[8] == 12 );
            Assert::IsTrue( destinationArray[9] == 13 );
        }

        TEST_METHOD( CopyToArrayAllElements )
        {
            vector.AddRange( { 10,11,12,13,14,15,16,17,18,19 } );
            std::array<int, 10> destinationArray = { 0,1,2,3,4,5 };
            vector.CopyTo( destinationArray, 10 );
            Assert::IsTrue( destinationArray[0] == 10 );
            Assert::IsTrue( destinationArray[6] == 16 );
            Assert::IsTrue( destinationArray[7] == 17 );
            Assert::IsTrue( destinationArray[8] == 18 );
        }

        TEST_METHOD( CopyToArrayAllElementsWithCustomStartingIndex )
        {
            vector.AddRange( { 6,7,8,9 } );
            std::array<int, 10> destinationArray = { 0,1,2,3,4,5 };
            vector.CopyTo( destinationArray, 10, 6 );
            Assert::IsTrue( destinationArray[0] == 0 );
            Assert::IsTrue( destinationArray[6] == 6 );
            Assert::IsTrue( destinationArray[7] == 7 );
            Assert::IsTrue( destinationArray[8] == 8 );
        }


        TEST_METHOD( FindBasicTypeElement )
        {
            vector.AddRange( { 1,4,56,23,37 } );
            int result = 0;
            result = vector.Find( []( int element )->bool
                {
                    return element == 23;
                } );
            Assert::IsTrue( result == 23 );
        }

        TEST_METHOD( FindCustomTypeElement )
        {
            Vector<Entity> newVector;
            newVector.AddRange( { Entity( 1 ),Entity( 4 ),Entity( 56 ),Entity( 23 ),Entity( 37 ) } );
            auto result = Entity( 0 );
            result = newVector.Find( []( Entity element )->bool
                {
                    return element.i == 23;
                } );
            Assert::IsTrue( result.i == 23 );
        }


        TEST_METHOD( EraseSpecificElementsOfBasicType )
        {
            vector.AddRange( { 3,23,12,43,12,32,12 } );
            vector.RemoveAll( []( int element )->bool
                {
                    return element == 12;
                } );
            Assert::IsTrue( vector.size() == 4 );
            Assert::IsTrue( vector[0] == 3 );
            Assert::IsTrue( vector[1] == 23 );
            Assert::IsTrue( vector[2] == 43 );
            Assert::IsTrue( vector[3] == 32 );
        }


        TEST_METHOD( TrueForAllWithBasicType )
        {
            vector.AddRange( { 1,1,1,1,1,1,1,1 } );
            Assert::IsTrue( vector.TrueForAll( []( int element )->bool
                {
                    return element == 1;
                } ) );
            Assert::IsFalse( vector.TrueForAll( []( int element )->bool
                {
                    return element == 2;
                } ) );
        }

        TEST_METHOD( TrueForAllWithCustomType )
        {
            Vector<Entity> newVector;
            newVector.AddRange( { Entity( 1 ),Entity( 1 ), Entity( 1 ), Entity( 1 ), Entity( 1 ) } );
            Assert::IsTrue( newVector.TrueForAll( []( Entity element )->bool
                {
                    return element.i == 1;
                } ) );
            Assert::IsFalse( newVector.TrueForAll( []( Entity element )->bool
                {
                    return element.i == 2;
                } ) );
        }


        TEST_METHOD( BinarySearchSuccessForBasicType )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            Assert::IsTrue( vector.BinarySearch( 4 ) == 3 );
            Assert::IsTrue( vector.BinarySearch( 1 ) == 0 );
            Assert::IsTrue( vector.BinarySearch( 7 ) == 6 );
        }

        TEST_METHOD( BinarySearchFailureForBasicType )
        {
            vector.AddRange( { 1,2,4,5,6,7,8,9 } );
            Assert::IsTrue( vector.BinarySearch( 11 ) == -1 );
            Assert::IsTrue( vector.BinarySearch( 3 ) == -1 );
        }


        TEST_METHOD( RemoveItemOfBasicType )
        {
            vector.AddRange( { 1,4,2,4,67,4,23,5,34,4 } );
            vector.Remove( 4 );
            Assert::IsTrue( vector[0] == 1 );
            Assert::IsTrue( vector[1] == 2 );
            Assert::IsTrue( vector[2] == 4 );
            Assert::IsTrue( vector[3] == 67 );
            vector.Remove( 4 );
            Assert::IsTrue( vector[0] == 1 );
            Assert::IsTrue( vector[1] == 2 );
            Assert::IsTrue( vector[2] == 67 );
            Assert::IsTrue( vector[3] == 4 );
        }


        TEST_METHOD( FindLastSuccessForBasicElement )
        {
            vector.AddRange( { 15,2,4,1,2,4,2,67,23,2,64,3 } );
            int result = 0;
            constexpr int expected = 64;
            result = vector.FindLast( []( int element )->bool {return element % 2 == 0; } );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( FindLastFailForBasicElementWhenNoSuchElement )
        {
            vector.AddRange( { 15,2,4,1,2,4,2,67,23,2,64,3 } );
            int result = -1;
            constexpr int expected = 0;
            result = vector.FindLast( []( int element )->bool { return element % 13 == 0; } );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( FindLastSuccessForCustomElement )
        {
            Vector<Entity> entities;
            entities.AddRange( { Entity( 2 ), Entity( 15 ), Entity( 17 ), Entity( 10 ), Entity( 16 ), Entity( 5 ), Entity( 21 ) } );
            auto result = Entity( 0 );
            result = entities.FindLast( []( const Entity& e )->bool {return e.i % 5 == 0; } );
            Assert::IsTrue( result == Entity( 5 ) );
        }

        TEST_METHOD( FindLastFailForCustomElementWhenNoSuchElement )
        {
            Vector<Entity> entities;
            entities.AddRange( { Entity( 2 ), Entity( 15 ), Entity( 17 ), Entity( 10 ), Entity( 16 ), Entity( 5 ), Entity( 21 ) } );
            auto result = Entity( 24 );
            result = entities.FindLast( []( const Entity& e )->bool {return e.i % 20 == 0; } );
            Assert::IsTrue( result == Entity() );
        }


        TEST_METHOD( RemoveRangeSuccessForBasicType )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            vector.RemoveRange( 3, 3 );
            Assert::IsTrue( vector[0] == 1 );
            Assert::IsTrue( vector[1] == 2 );
            Assert::IsTrue( vector[2] == 3 );
            Assert::IsTrue( vector[3] == 7 );
            Assert::IsTrue( vector[4] == 8 );
        }

        TEST_METHOD( RemoveRangeFails )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            Assert::ExpectException<std::invalid_argument>( [&]()->void{ vector.RemoveRange( 5, 6 ); } );
        }

        TEST_METHOD( RemoveRangeSuccessForCustomType )
        {
            Vector<Entity> entities;
            entities.AddRange( { Entity( 1 ),Entity( 2 ), Entity( 3 ), Entity( 4 ), Entity( 5 ), Entity( 6 ) } );
            entities.RemoveRange( 3, 2 );
            Assert::IsTrue( entities[0] == Entity( 1 ) );
            Assert::IsTrue( entities[1] == Entity( 2 ) );
            Assert::IsTrue( entities[2] == Entity( 3 ) );
            Assert::IsTrue( entities[3] == Entity( 6 ) );
        }


        TEST_METHOD( RemoveItemOfCustomType )
        {
            Vector<Entity> entities;
            entities.AddRange( { Entity( 2 ), Entity( 4 ), Entity( 8 ), Entity( 1 ), Entity( 8 ), Entity( 7 ) } );
            entities.Remove( Entity( 8 ) );
            Assert::IsTrue( entities[0] == Entity( 2 ) );
            Assert::IsTrue( entities[1] == Entity( 4 ) );
            Assert::IsTrue( entities[2] == Entity( 1 ) );
            Assert::IsTrue( entities[3] == Entity( 8 ) );
            entities.Remove( Entity( 8 ) );
            Assert::IsTrue( entities[0] == Entity( 2 ) );
            Assert::IsTrue( entities[1] == Entity( 4 ) );
            Assert::IsTrue( entities[2] == Entity( 1 ) );
            Assert::IsTrue( entities[3] == Entity( 7 ) );
        }


        TEST_METHOD( IndexOfSuccessForBasicTypeElement )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            constexpr int expected = 6;
            int result = -1;
            result = vector.IndexOf( 7 );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( IndexOfSuccessForCustomTypeElement )
        {
            Vector<Entity> entities;
            entities.AddRange( { Entity( 2 ), Entity( 4 ), Entity( 8 ), Entity( 1 ), Entity( 8 ), Entity( 7 ) } );
            constexpr int expected = 3;
            int result = -1;
            result = entities.IndexOf( Entity( 1 ) );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( IndexOfFailsWhenNoSuchElement )
        {
            vector.AddRange( { 1,2,3,4,6,7,8,9 } );
            constexpr int expected = -1;
            int result = 10;
            result = vector.IndexOf( 5 );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( IndexOfWithSpecificStartSuccessForBasicTypeElement )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            constexpr int expected = 6;
            int result = -1;
            result = vector.IndexOf( 7, 4 );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( IndexOfWithSpecificStartSuccessForCustomTypeElement )
        {
            Vector<Entity> entities;
            entities.AddRange( { Entity( 2 ), Entity( 4 ), Entity( 8 ), Entity( 1 ), Entity( 8 ), Entity( 7 ) } );
            constexpr int expected = 3;
            int result = -1;
            result = entities.IndexOf( Entity( 1 ), 1 );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( IndexOfWithSpecificStartAndCountSuccessForBasicTypeElement )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            constexpr int expected = 6;
            int result = -1;
            result = vector.IndexOf( 7, 4, 4 );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( IndexOfWithSpecificStartAndCountSuccessForCustomTypeElement )
        {
            Vector<Entity> entities;
            entities.AddRange( { Entity( 2 ), Entity( 4 ), Entity( 8 ), Entity( 1 ), Entity( 8 ), Entity( 7 ) } );
            constexpr int expected = 3;
            int result = -1;
            result = entities.IndexOf( Entity( 1 ), 2, 2 );
            Assert::IsTrue( result == expected );
        }


        TEST_METHOD( FindIndexSuccessForBasicTypeElement )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            constexpr int expected = 6;
            int result = -1;
            result = vector.FindIndex( []( int element )->bool {return element == 7; } );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( FindIndexSuccessForCustomTypeElement )
        {
            Vector<Entity> entities;
            entities.AddRange( { Entity( 2 ), Entity( 4 ), Entity( 8 ), Entity( 1 ), Entity( 8 ), Entity( 7 ) } );
            constexpr int expected = 3;
            int result = -1;
            result = entities.FindIndex( []( const Entity& e )->bool { return e == Entity( 1 ); } );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( FindIndexFailsWhenNoSuchElement )
        {
            vector.AddRange( { 1,2,3,4,6,7,8,9 } );
            constexpr int expected = -1;
            int result = 10;
            result = vector.FindIndex( []( int element )->bool {return element == 5; } );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( FindIndexWithSpecificStartSuccessForBasicTypeElement )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            constexpr int expected = 6;
            int result = -1;
            result = vector.FindIndex( []( int element )->bool {return element == 7; }, 4 );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( FindIndexWithSpecificStartSuccessForCustomTypeElement )
        {
            Vector<Entity> entities;
            entities.AddRange( { Entity( 2 ), Entity( 4 ), Entity( 8 ), Entity( 1 ), Entity( 8 ), Entity( 7 ) } );
            constexpr int expected = 3;
            int result = -1;
            result = entities.FindIndex( []( const Entity& e )->bool {return e == Entity( 1 ); }, 1 );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( FindIndexWithSpecificStartAndCountSuccessForBasicTypeElement )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            constexpr int expected = 6;
            int result = -1;
            result = vector.FindIndex( []( int element )->bool {return element == 7; }, 4, 4 );
            Assert::IsTrue( result == expected );
        }

        TEST_METHOD( FindIndexWithSpecificStartAndCountSuccessForCustomTypeElement )
        {
            Vector<Entity> entities;
            entities.AddRange( { Entity( 2 ), Entity( 4 ), Entity( 8 ), Entity( 1 ), Entity( 8 ), Entity( 7 ) } );
            constexpr int expected = 3;
            int result = -1;
            result = entities.FindIndex( []( const Entity& e )->bool {return e == Entity( 1 ); }, 2, 2 );
            Assert::IsTrue( result == expected );
        }


        TEST_METHOD( ReverseFullScopeOfContainerForOddNumberOfElementsInContainer )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            vector.Reverse();
            Assert::IsTrue( vector[0] == 9 );
            Assert::IsTrue( vector[1] == 8 );
            Assert::IsTrue( vector[2] == 7 );
            Assert::IsTrue( vector[3] == 6 );
            Assert::IsTrue( vector[4] == 5 );
            Assert::IsTrue( vector[5] == 4 );
            Assert::IsTrue( vector[6] == 3 );
            Assert::IsTrue( vector[7] == 2 );
            Assert::IsTrue( vector[8] == 1 );
        }

        TEST_METHOD( ReverseFullScopeOfContainerForEvenNumberOfElementsInContainer )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9,10 } );
            vector.Reverse();
            Assert::IsTrue( vector[0] == 10 );
            Assert::IsTrue( vector[1] == 9 );
            Assert::IsTrue( vector[2] == 8 );
            Assert::IsTrue( vector[3] == 7 );
            Assert::IsTrue( vector[4] == 6 );
            Assert::IsTrue( vector[5] == 5 );
            Assert::IsTrue( vector[6] == 4 );
            Assert::IsTrue( vector[7] == 3 );
            Assert::IsTrue( vector[8] == 2 );
            Assert::IsTrue( vector[9] == 1 );
        }

        TEST_METHOD( ReverseRangeInContainerForOddNumberOfElementsInContainer )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            vector.Reverse( 2, 4 );
            Assert::IsTrue( vector[0] == 1 );
            Assert::IsTrue( vector[1] == 2 );
            Assert::IsTrue( vector[2] == 6 );
            Assert::IsTrue( vector[3] == 5 );
            Assert::IsTrue( vector[4] == 4 );
            Assert::IsTrue( vector[5] == 3 );
            Assert::IsTrue( vector[6] == 7 );
            Assert::IsTrue( vector[7] == 8 );
            Assert::IsTrue( vector[8] == 9 );
        }

        TEST_METHOD( ReverseRangeInContainerForEvenNumberOfElementsInContainer )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9,10 } );
            vector.Reverse( 4, 2 );
            Assert::IsTrue( vector[0] == 1 );
            Assert::IsTrue( vector[1] == 2 );
            Assert::IsTrue( vector[2] == 3 );
            Assert::IsTrue( vector[3] == 4 );
            Assert::IsTrue( vector[4] == 6 );
            Assert::IsTrue( vector[5] == 5 );
            Assert::IsTrue( vector[6] == 7 );
            Assert::IsTrue( vector[7] == 8 );
            Assert::IsTrue( vector[8] == 9 );
            Assert::IsTrue( vector[9] == 10 );
        }

        TEST_METHOD( ReverseThrowsExceptionWhenExceedingContainerSize )
        {
            vector.AddRange( { 1,2,3,4,5,6,7 } );
            Assert::ExpectException<std::invalid_argument>( [&]()->void{ vector.Reverse( 3, 5 ); } );
        }


        TEST_METHOD( FindLastIndexSuccessForFullContainerRange )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            result = vector.FindLastIndex( []( const int& element )->bool
                {
                    return element == 3;
                } );
            Assert::IsTrue( result != 0 );
            Assert::IsTrue( result == 9 );
        }

        TEST_METHOD( FindLastIndexFailsForFullContainerRange )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            result = vector.FindLastIndex( []( const int& element )->bool
                {
                    return element == 15;
                } );
            Assert::IsTrue( result != 0 );
            Assert::IsTrue( result == -1 );
        }

        TEST_METHOD( FindLastIndexSuccessForContainerRangeLimitedByEndIndex )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            result = vector.FindLastIndex( 4, []( const int& element )->bool
                {
                    return element == 3;
                } );
            Assert::IsTrue( result != 0 );
            Assert::IsTrue( result == 3 );
        }

        TEST_METHOD( FindLastIndexFailsForContainerRangeLimitedByEndIndex )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            result = vector.FindLastIndex( 4, []( const int& element )->bool
                {
                    return element == 67;
                } );
            Assert::IsTrue( result != 0 );
            Assert::IsTrue( result == -1 );
        }

        TEST_METHOD( FindLastIndexSuccessForContainerRangeLimitedByStartEndIndex )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            result = vector.FindLastIndex( 3, 8, []( const int& element )->bool
                {
                    return element == 15;
                } );
            Assert::IsTrue( result != 0 );
            Assert::IsTrue( result == -1 );
        }

        TEST_METHOD( FindLastIndexFailsForContainerRangeLimitedByStartEndIndex )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            result = vector.FindLastIndex( []( const int& element )->bool
                {
                    return element == 15;
                } );
            Assert::IsTrue( result != 0 );
            Assert::IsTrue( result == -1 );
        }

        TEST_METHOD( FindLastIndexThrowsForContainerRangeLimitedByEndIndex )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            Assert::ExpectException<std::invalid_argument >( [&]()->void {result = vector.FindLastIndex( 50, []( const int& element )->bool
                {
                    return element == 15;
                } ); } );
            Assert::IsTrue( result == 0 );
        }

        TEST_METHOD( FindLastIndexThrowsForContainerRangeLimitedByStartEndIndex )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            Assert::ExpectException<std::invalid_argument >( [&]()->void {result = vector.FindLastIndex( 6, 20, []( const int& element )->bool
                {
                    return element == 15;
                } ); } );
            Assert::ExpectException<std::invalid_argument >( [&]()->void {result = vector.FindLastIndex( 15, 25, []( const int& element )->bool
                {
                    return element == 15;
                } ); } );
            Assert::ExpectException<std::invalid_argument >( [&]()->void {result = vector.FindLastIndex( 5, 2, []( const int& element )->bool
                {
                    return element == 15;
                } ); } );
            Assert::IsTrue( result == 0 );
        }


        TEST_METHOD( InsertRangeSuccessForDataAsArray )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            constexpr unsigned int dataSize = 5;
            int range[dataSize] = { 10,20,30,40,50 };
            vector.InsertRange( 3, range, dataSize );
            Assert::IsTrue( vector[0] == 1 );
            Assert::IsTrue( vector[1] == 2 );
            Assert::IsTrue( vector[2] == 3 );
            Assert::IsTrue( vector[3] == 10 );
            Assert::IsTrue( vector[4] == 20 );
            Assert::IsTrue( vector[5] == 30 );
            Assert::IsTrue( vector[6] == 40 );
            Assert::IsTrue( vector[7] == 50 );
            Assert::IsTrue( vector[8] == 4 );
            Assert::IsTrue( vector[9] == 5 );
            Assert::IsTrue( vector[10] == 6 );
            Assert::IsTrue( vector[11] == 7 );
            Assert::IsTrue( vector[12] == 8 );
            Assert::IsTrue( vector[13] == 9 );
        }

        TEST_METHOD( InsertRangeSuccessForDataAsLValueStdVector )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            std::vector<int> range = { 10,20,30,40,50 };
            vector.InsertRange( 3, range );
            Assert::IsTrue( vector[0] == 1 );
            Assert::IsTrue( vector[1] == 2 );
            Assert::IsTrue( vector[2] == 3 );
            Assert::IsTrue( vector[3] == 10 );
            Assert::IsTrue( vector[4] == 20 );
            Assert::IsTrue( vector[5] == 30 );
            Assert::IsTrue( vector[6] == 40 );
            Assert::IsTrue( vector[7] == 50 );
            Assert::IsTrue( vector[8] == 4 );
            Assert::IsTrue( vector[9] == 5 );
            Assert::IsTrue( vector[10] == 6 );
            Assert::IsTrue( vector[11] == 7 );
            Assert::IsTrue( vector[12] == 8 );
            Assert::IsTrue( vector[13] == 9 );
        }

        TEST_METHOD( InsertRangeSuccessForDataAsRValueStdVector )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            std::vector<int> range = { 10,20,30,40,50 };
            vector.InsertRange( 3, std::move( range ) );
            Assert::IsTrue( vector[0] == 1 );
            Assert::IsTrue( vector[1] == 2 );
            Assert::IsTrue( vector[2] == 3 );
            Assert::IsTrue( vector[3] == 10 );
            Assert::IsTrue( vector[4] == 20 );
            Assert::IsTrue( vector[5] == 30 );
            Assert::IsTrue( vector[6] == 40 );
            Assert::IsTrue( vector[7] == 50 );
            Assert::IsTrue( vector[8] == 4 );
            Assert::IsTrue( vector[9] == 5 );
            Assert::IsTrue( vector[10] == 6 );
            Assert::IsTrue( vector[11] == 7 );
            Assert::IsTrue( vector[12] == 8 );
            Assert::IsTrue( vector[13] == 9 );
        }

        TEST_METHOD( InsertRangeSuccessForDataAsLValueCxVector )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            Vector<int> range;
            range.AddRange( { 10,20,30,40,50 } );
            vector.InsertRange( 3, range );
            Assert::IsTrue( vector[0] == 1 );
            Assert::IsTrue( vector[1] == 2 );
            Assert::IsTrue( vector[2] == 3 );
            Assert::IsTrue( vector[3] == 10 );
            Assert::IsTrue( vector[4] == 20 );
            Assert::IsTrue( vector[5] == 30 );
            Assert::IsTrue( vector[6] == 40 );
            Assert::IsTrue( vector[7] == 50 );
            Assert::IsTrue( vector[8] == 4 );
            Assert::IsTrue( vector[9] == 5 );
            Assert::IsTrue( vector[10] == 6 );
            Assert::IsTrue( vector[11] == 7 );
            Assert::IsTrue( vector[12] == 8 );
            Assert::IsTrue( vector[13] == 9 );
        }

        TEST_METHOD( InsertRangeSuccessForDataAsRValueCxVector )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            Vector<int> range;
            range.AddRange( { 10,20,30,40,50 } );
            vector.InsertRange( 3, std::move( range ) );
            Assert::IsTrue( vector[0] == 1 );
            Assert::IsTrue( vector[1] == 2 );
            Assert::IsTrue( vector[2] == 3 );
            Assert::IsTrue( vector[3] == 10 );
            Assert::IsTrue( vector[4] == 20 );
            Assert::IsTrue( vector[5] == 30 );
            Assert::IsTrue( vector[6] == 40 );
            Assert::IsTrue( vector[7] == 50 );
            Assert::IsTrue( vector[8] == 4 );
            Assert::IsTrue( vector[9] == 5 );
            Assert::IsTrue( vector[10] == 6 );
            Assert::IsTrue( vector[11] == 7 );
            Assert::IsTrue( vector[12] == 8 );
            Assert::IsTrue( vector[13] == 9 );
        }


        TEST_METHOD( GetRangeSuccessForCorrectRange )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            Vector<int> range;
            range = vector.GetRange( 3, 7 );
            Assert::IsTrue( range[0] == 4 );
            Assert::IsTrue( range[1] == 5 );
            Assert::IsTrue( range[2] == 6 );
            Assert::IsTrue( range[3] == 7 );
            Assert::IsTrue( range.size() == (7 - 3) );
        }

        TEST_METHOD( GetRangeFailsForIncorrectRange )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            Vector<int> range;
            Assert::ExpectException<std::invalid_argument>( [&]()->void {range = vector.GetRange( 3, 20 ); }  );
            Assert::ExpectException<std::invalid_argument>( [&]()->void {range = vector.GetRange( 11, 15 ); } );
            Assert::ExpectException<std::invalid_argument>( [&]()->void {range = vector.GetRange( 5, 2 ); } );
            Assert::IsTrue( range.size() == 0 );
        }


        TEST_METHOD( LastIndexOfSuccessForFullContainerRange )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            result = vector.LastIndexOf( 3 );
            Assert::IsTrue( result != 0 );
            Assert::IsTrue( result == 9 );
        }

        TEST_METHOD( LastIndexOfFailsForFullContainerRange )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            result = vector.LastIndexOf( 15 );
            Assert::IsTrue( result != 0 );
            Assert::IsTrue( result == -1 );
        }

        TEST_METHOD( LastIndexOfSuccessForContainerRangeLimitedByEndIndex )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            result = vector.LastIndexOf( 3, 4 );
            Assert::IsTrue( result != 0 );
            Assert::IsTrue( result == 3 );
        }

        TEST_METHOD( LastIndexOfFailsForContainerRangeLimitedByEndIndex )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            result = vector.LastIndexOf( 67, 4 );
            Assert::IsTrue( result != 0 );
            Assert::IsTrue( result == -1 );
        }

        TEST_METHOD( LastIndexOfSuccessForContainerRangeLimitedByStartEndIndex )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            result = vector.LastIndexOf( 15, 3, 5 );
            Assert::IsTrue( result != 0 );
            Assert::IsTrue( result == -1 );
        }

        TEST_METHOD( LastIndexOfFailsForContainerRangeLimitedByStartEndIndex )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            result = vector.LastIndexOf( 15, 3, 5 );
            Assert::IsTrue( result != 0 );
            Assert::IsTrue( result == -1 );
        }

        TEST_METHOD( LastIndexOfThrowsForContainerRangeLimitedByEndIndex )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            Assert::ExpectException<std::invalid_argument>( [&]()->void {result = vector.LastIndexOf( 15, 50 ); } );
            Assert::IsTrue( result == 0 );
        }

        TEST_METHOD( LastIndexOfThrowsForContainerRangeLimitedByStartEndIndex )
        {
            vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
            int result = 0;
            Assert::ExpectException<std::invalid_argument>( [&]()->void {result = vector.LastIndexOf( 15, 6, 20 ); } );
            Assert::ExpectException<std::invalid_argument>( [&]()->void {result = vector.LastIndexOf( 15, 15, 25 ); } );
            Assert::IsTrue( result == 0 );
        }


        TEST_METHOD( ConvertAllSuccessForBasicType )
        {
            vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
            Vector<float> converted;
            converted = vector.ConvertAll<float>( []( int item )->float { return item + 0.5f; } );
            Assert::IsTrue( converted.size() == vector.size() );
            for( unsigned int i = 0; i < converted.size(); ++i )
                Assert::IsTrue( converted[i] == i + 1.5f );
        }


        TEST_METHOD( RemoveAtSuccessForCorrectIndex )
        {
            vector.AddRange( { 0,1,2,3,4,5,6,7,8,9 } );
            Assert::IsTrue( vector.size() == 10 );
            Assert::IsTrue( vector[4] == 4 );
            vector.RemoveAt( 4 );
            Assert::IsTrue( vector.size() == 9 );
            Assert::IsTrue( vector[3] == 3 );
            Assert::IsTrue( vector[4] == 5 );
            Assert::IsTrue( vector[5] == 6 );
        }

        TEST_METHOD( RemoveAtFailsForIncorrectIndex )
        {
            vector.AddRange( { 0,1,2,3,4,5,6,7,8,9 } );
            Assert::IsTrue( vector.size() == 10 );
            Assert::ExpectException<std::invalid_argument>( [&]()->void{ vector.RemoveAt( 15 ); } );
            Assert::IsTrue( vector.size() == 10 );
        }


        TEST_METHOD( ForEachElementActionIsPerformed )
        {
            vector.AddRange( { 0,0,0,0,0,0,0,0,0,0 } );
            int iteration = 0;
            vector.ForEach( [&]( int& element )
                {
                    element += iteration * 2;
                    iteration++;
                } );
        }


        TEST_METHOD( FindAllSuccess )
        {
            vector.AddRange( { 13,2,14,3,1,15,16,23,24 } );
            Vector<int> results;
            results = vector.FindAll( []( const int& element )->bool {return element % 2 == 0; } );
            Assert::IsTrue( results.size() == 4 );
            Assert::IsTrue( results[0] == 2 );
            Assert::IsTrue( results[1] == 14 );
            Assert::IsTrue( results[2] == 16 );
            Assert::IsTrue( results[3] == 24 );
        }

        TEST_METHOD( FindAllFailsByLeavingEmptyDefaultContainer )
        {
            vector.AddRange( { 13,2,14,3,1,15,16,23,24 } );
            Vector<int> results;
            results = vector.FindAll( []( const int& element )->bool {return element % 9 == 0; } );
            Assert::IsTrue( results.size() == 0 );
        }

	};
}
