#include "Vector.hpp"
#include <gtest/gtest.h>
#include <iostream>



class ExtendedVectorTest : public testing::Test
{
public:
    Cx::Vector<int> vector;

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
};



TEST_F(ExtendedVectorTest, AddRangeByInitializerListTest)
{
    vector.AddRange({1,4,12,8});
    ASSERT_TRUE(vector[0] == 1);
    ASSERT_TRUE(vector[1] == 4);
    ASSERT_TRUE(vector[2] == 12);
    ASSERT_TRUE(vector[3] == 8);
}


TEST_F(ExtendedVectorTest, AddRangeByStandardArrayTest)
{
    int range[] = {4,6,33,124};
    vector.AddRange(range, 4);
    ASSERT_TRUE(vector[0] == 4);
    ASSERT_TRUE(vector[1] == 6);
    ASSERT_TRUE(vector[2] == 33);
    ASSERT_TRUE(vector[3] == 124);
}


TEST_F(ExtendedVectorTest, AddRangeByAnotherCxVectorGivenByReference)
{
    Cx::Vector<int> newVector;
    newVector.AddRange({1,15,23,56});
    vector.AddRange(newVector);
    ASSERT_TRUE(vector[0] == 1);
    ASSERT_TRUE(vector[1] == 15);
    ASSERT_TRUE(vector[2] == 23);
    ASSERT_TRUE(vector[3] == 56);
}


TEST_F(ExtendedVectorTest, AddRangeByAnotherCxVectorGivenByRValue)
{
    Cx::Vector<int> newVector;
    newVector.AddRange({1,15,23,56});
    vector.AddRange(std::move(newVector));
    ASSERT_TRUE(vector[0] == 1);
    ASSERT_TRUE(vector[1] == 15);
    ASSERT_TRUE(vector[2] == 23);
    ASSERT_TRUE(vector[3] == 56);
}


TEST_F( ExtendedVectorTest, ContainerWithBasicTypesContainsAnElement )
{
    vector.AddRange( { 2,56,2,34,8,10 } );
    ASSERT_FALSE( vector.Contains( 11 ) );
    ASSERT_TRUE( vector.Contains( 56 ) );
    ASSERT_FALSE( vector.Contains( 9 ) );
    ASSERT_TRUE( vector.Contains( 10 ) );

    vector.AddRange( { 3,5,7,12 } );
    ASSERT_FALSE( vector.Contains( 13 ) );
    ASSERT_TRUE( vector.Contains( 7 ) );
    ASSERT_FALSE( vector.Contains( 6 ) );
    ASSERT_TRUE( vector.Contains( 12 ) );
}


TEST_F( ExtendedVectorTest, ContainerWithCustomTypesContainsAnElement )
{


    Cx::Vector<Entity> newVector;
    newVector.AddRange( {
        Entity( 2,8 ),
        Entity( 3,10 ),
        Entity( 4,12 ),
        Entity( 0,-2 ),
        Entity( -5,0.4f )
        } );

    ASSERT_FALSE( newVector.Contains( Entity( 3, 12 ) ) );
    ASSERT_TRUE( newVector.Contains( Entity( 3, 10 ) ) );
    ASSERT_FALSE( newVector.Contains( Entity( 1, -1 ) ) );
    ASSERT_TRUE( newVector.Contains( Entity( -5, 0.4f ) ) );
}


TEST_F( ExtendedVectorTest, SortingBasicTypesAtWholeScopeWithDefaultComparer )
{
    vector.AddRange( { 4,13,2,56,3 } );
    ASSERT_NO_THROW( vector.Sort() );
    ASSERT_TRUE( vector[0] == 2 );
    ASSERT_TRUE( vector[1] == 3 );
    ASSERT_TRUE( vector[2] == 4 );
    ASSERT_TRUE( vector[3] == 13 );
    ASSERT_TRUE( vector[4] == 56 );
}


TEST_F( ExtendedVectorTest, SortingCustomTypesAtWholeScopeWithDefaultComparer )
{
    Cx::Vector<Entity> newVector;
    newVector.AddRange( { Entity(4),Entity(13),Entity(2),Entity(56),Entity(3) } );
    ASSERT_NO_THROW( newVector.Sort() );
    ASSERT_TRUE( newVector[0].i == 2 );
    ASSERT_TRUE( newVector[1].i == 3 );
    ASSERT_TRUE( newVector[2].i == 4 );
    ASSERT_TRUE( newVector[3].i == 13 );
    ASSERT_TRUE( newVector[4].i == 56 );
}


TEST_F( ExtendedVectorTest, SortingBasicTypesAtSpecifiedScopeWithDefaultComparer )
{
    vector.AddRange( { 4,13,2,56,3 } );
    ASSERT_NO_THROW( vector.Sort(1,3) );
    ASSERT_TRUE( vector[0] == 4 );
    ASSERT_TRUE( vector[1] == 2 );
    ASSERT_TRUE( vector[2] == 13 );
    ASSERT_TRUE( vector[3] == 56 );
    ASSERT_TRUE( vector[4] == 3 );
}


TEST_F( ExtendedVectorTest, SortingCustomTypesAtSpecificScopeWithDefaultComparer )
{
    Cx::Vector<Entity> newVector;
    newVector.AddRange( { Entity( 4 ),Entity( 13 ),Entity( 56 ),Entity( 2 ),Entity( 3 ) } );
    ASSERT_NO_THROW( newVector.Sort(1,3) );
    ASSERT_TRUE( newVector[0].i == 4 );
    ASSERT_TRUE( newVector[1].i == 2 );
    ASSERT_TRUE( newVector[2].i == 13 );
    ASSERT_TRUE( newVector[3].i == 56 );
    ASSERT_TRUE( newVector[4].i == 3 );
}


TEST_F( ExtendedVectorTest, SortingBasicTypesAtWholeScopeWithCustomComparer )
{
    vector.AddRange( { 4,13,2,56,3 } );
    ASSERT_NO_THROW( vector.Sort( []( int a, int b )->bool
        {
            return a > b;
        } ));
    ASSERT_TRUE( vector[0] == 56 );
    ASSERT_TRUE( vector[1] == 13 );
    ASSERT_TRUE( vector[2] == 4 );
    ASSERT_TRUE( vector[3] == 3 );
    ASSERT_TRUE( vector[4] == 2 );
}

TEST_F( ExtendedVectorTest, SortingCustomTypesAtSpecificScopeWithCustomComparer )
{
    Cx::Vector<Entity> newVector;
    newVector.AddRange( { Entity( 4 ),Entity( 13 ),Entity( 2 ),Entity( 56 ),Entity( 3 ) } );
    ASSERT_NO_THROW( newVector.Sort( 1, 3, []( Entity a, Entity b )->bool
        {
            return a.i > b.i;
        }) );
    ASSERT_TRUE( newVector[0].i == 4 );
    ASSERT_TRUE( newVector[1].i == 56 );
    ASSERT_TRUE( newVector[2].i == 13 );
    ASSERT_TRUE( newVector[3].i == 2 );
    ASSERT_TRUE( newVector[4].i == 3 );
}


TEST_F( ExtendedVectorTest, BasicTypeElementExistsInTheContainer )
{
    vector.AddRange( { 3,4,12,5,98,11 } );
    auto falsePredicate = []( const int& element )->bool {
        return element == 6;
    };
    auto truePredicate = []( const int& element )->bool {
        return element == 98;
    };
    ASSERT_FALSE( vector.Exists( falsePredicate ) );
    ASSERT_TRUE( vector.Exists( truePredicate ) );
}


TEST_F( ExtendedVectorTest, CustomTypeElementExistsInTheContainer )
{
    Cx::Vector<Entity> newVector;
    newVector.AddRange( { Entity(3),Entity(4),Entity(12),Entity(5),Entity(98),Entity(11) } );
    auto falsePredicate = []( const Entity& element )->bool {
        return element.i == 6;
    };
    auto truePredicate = []( const Entity& element )->bool {
        return element.i == 98;
    };
    ASSERT_FALSE( newVector.Exists( falsePredicate ) );
    ASSERT_TRUE( newVector.Exists( truePredicate ) );
}


TEST_F( ExtendedVectorTest, CopyToWithCustomStartingIndexesOfBothArrays )
{
    vector.AddRange( { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 } );
    int destinationArray[10] = { 0,1,2,3,4,5 };
    EXPECT_NO_THROW( vector.CopyTo( 11, destinationArray, 7, 3 ) );
    EXPECT_TRUE( destinationArray[7] == 11 );
    EXPECT_TRUE( destinationArray[8] == 12 );
    EXPECT_TRUE( destinationArray[9] == 13 );
}

TEST_F( ExtendedVectorTest, CopyToAllElements )
{
    vector.AddRange( { 10,11,12,13,14,15,16,17,18,19 } );
    int destinationArray[10] = { 0,1,2,3,4,5 };
    EXPECT_NO_THROW( vector.CopyTo( destinationArray, 10 ) );
    EXPECT_TRUE( destinationArray[0] == 10 );
    EXPECT_TRUE( destinationArray[6] == 16 );
    EXPECT_TRUE( destinationArray[7] == 17 );
    EXPECT_TRUE( destinationArray[8] == 18 );
}

TEST_F( ExtendedVectorTest, CopyToAllElementsWithCustomStartingIndex )
{
    vector.AddRange( { 6,7,8,9 } );
    int destinationArray[10] = { 0,1,2,3,4,5 };
    EXPECT_NO_THROW( vector.CopyTo( destinationArray, 10, 6 ) );
    EXPECT_TRUE( destinationArray[0] == 0 );
    EXPECT_TRUE( destinationArray[6] == 6 );
    EXPECT_TRUE( destinationArray[7] == 7 );
    EXPECT_TRUE( destinationArray[8] == 8 );
}


TEST_F( ExtendedVectorTest, FindBasicTypeElement )
{
    vector.AddRange( { 1,4,56,23,37 } );
    int result = 0;
    EXPECT_NO_THROW( result = vector.Find( []( int element )->bool
        {
            return element == 23;
        } ) );
    EXPECT_TRUE( result == 23 );
}

TEST_F( ExtendedVectorTest, FindCustomTypeElement )
{
    Cx::Vector<Entity> newVector;
    newVector.AddRange( { Entity(1),Entity(4),Entity(56),Entity(23),Entity(37) } );
    auto result = Entity(0);
    EXPECT_NO_THROW( result = newVector.Find( []( Entity element )->bool
        {
            return element.i == 23;
        } ) );
    EXPECT_TRUE( result.i == 23 );
}


TEST_F( ExtendedVectorTest, EraseSpecificElementsOfBasicType )
{
    vector.AddRange( { 3,23,12,43,12,32,12 } );
    vector.RemoveAll( []( int element )->bool
        {
            return element == 12;
        } );
    ASSERT_TRUE( vector.size() == 4 );
    ASSERT_TRUE( vector[0] == 3 );
    ASSERT_TRUE( vector[1] == 23 );
    ASSERT_TRUE( vector[2] == 43 );
    ASSERT_TRUE( vector[3] == 32 );
}


TEST_F( ExtendedVectorTest, TrueForAllWithBasicType )
{
    vector.AddRange( { 1,1,1,1,1,1,1,1 } );
    ASSERT_TRUE( vector.TrueForAll( []( int element )->bool
        {
            return element == 1;
        } ) );
    ASSERT_FALSE( vector.TrueForAll( []( int element )->bool
        {
            return element == 2;
        } ) );
}

TEST_F( ExtendedVectorTest, TrueForAllWithCustomType )
{
    Cx::Vector<Entity> newVector;
    newVector.AddRange( { Entity( 1 ),Entity( 1 ), Entity( 1 ), Entity( 1 ), Entity( 1 ) } );
    ASSERT_TRUE( newVector.TrueForAll( []( Entity element )->bool
        {
            return element.i == 1;
        } ) );
    ASSERT_FALSE( newVector.TrueForAll( []( Entity element )->bool
        {
            return element.i == 2;
        } ) );
}


TEST_F( ExtendedVectorTest, BinarySearchSuccessForBasicType )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    ASSERT_TRUE( vector.BinarySearch( 4 ) == 3 );
    ASSERT_TRUE( vector.BinarySearch( 1 ) == 0 );
    ASSERT_TRUE( vector.BinarySearch( 7 ) == 6 );
}

TEST_F( ExtendedVectorTest, BinarySearchFailureForBasicType )
{
    vector.AddRange( { 1,2,4,5,6,7,8,9 } );
    ASSERT_TRUE( vector.BinarySearch( 11 ) == -1 );
    ASSERT_TRUE( vector.BinarySearch( 3 ) == -1 );
}


TEST_F( ExtendedVectorTest, RemoveItemOfBasicType )
{
    vector.AddRange( { 1,4,2,4,67,4,23,5,34,4 } );
    EXPECT_NO_THROW( vector.Remove( 4 ) );
    ASSERT_TRUE( vector[0] == 1 );
    ASSERT_TRUE( vector[1] == 2 );
    ASSERT_TRUE( vector[2] == 4 );
    ASSERT_TRUE( vector[3] == 67 );
    EXPECT_NO_THROW( vector.Remove( 4 ) );
    ASSERT_TRUE( vector[0] == 1 );
    ASSERT_TRUE( vector[1] == 2 );
    ASSERT_TRUE( vector[2] == 67 );
    ASSERT_TRUE( vector[3] == 4 );
}


TEST_F( ExtendedVectorTest, FindLastSuccessForBasicElement )
{
    vector.AddRange( { 15,2,4,1,2,4,2,67,23,2,64,3 } );
    int result = 0;
    constexpr int expected = 64;
    EXPECT_NO_THROW( result = vector.FindLast( []( int element )->bool {return element % 2 == 0; } ) );
    EXPECT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, FindLastFailForBasicElementWhenNoSuchElement )
{
    vector.AddRange( { 15,2,4,1,2,4,2,67,23,2,64,3 } );
    int result = -1;
    constexpr int expected = 0;
    EXPECT_NO_THROW( result = vector.FindLast( []( int element )->bool { return element % 13 == 0; } ) );
    EXPECT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, FindLastSuccessForCustomElement )
{
    Cx::Vector<Entity> entities;
    entities.AddRange( { Entity( 2 ), Entity( 15 ), Entity( 17 ), Entity( 10 ), Entity( 16 ), Entity( 5 ), Entity( 21 ) } );
    auto result = Entity( 0 );
    EXPECT_NO_THROW( result = entities.FindLast( []( const Entity& e )->bool {return e.i % 5 == 0; } ) );
    ASSERT_TRUE( result == Entity( 5 ) );
}

TEST_F( ExtendedVectorTest, FindLastFailForCustomElementWhenNoSuchElement )
{
    Cx::Vector<Entity> entities;
    entities.AddRange( { Entity( 2 ), Entity( 15 ), Entity( 17 ), Entity( 10 ), Entity( 16 ), Entity( 5 ), Entity( 21 ) } );
    auto result = Entity(24);
    EXPECT_NO_THROW( result = entities.FindLast( []( const Entity& e )->bool {return e.i % 20 == 0; } ) );
    ASSERT_TRUE( result == Entity() );
}


TEST_F( ExtendedVectorTest, RemoveRangeSuccessForBasicType )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    EXPECT_NO_THROW( vector.RemoveRange( 3, 3 ) );
    ASSERT_TRUE( vector[0] == 1 );
    ASSERT_TRUE( vector[1] == 2 );
    ASSERT_TRUE( vector[2] == 3 );
    ASSERT_TRUE( vector[3] == 7 );
    ASSERT_TRUE( vector[4] == 8 );
}

TEST_F( ExtendedVectorTest, RemoveRangeFails )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    EXPECT_THROW( vector.RemoveRange( 5, 6 ), std::invalid_argument );
}

TEST_F( ExtendedVectorTest, RemoveRangeSuccessForCustomType )
{
    Cx::Vector<Entity> entities;
    entities.AddRange( { Entity( 1 ),Entity( 2 ), Entity( 3 ), Entity( 4 ), Entity( 5 ), Entity( 6 ) } );
    EXPECT_NO_THROW( entities.RemoveRange( 3, 2 ) );
    ASSERT_TRUE( entities[0] == Entity(1) );
    ASSERT_TRUE( entities[1] == Entity(2) );
    ASSERT_TRUE( entities[2] == Entity(3) );
    ASSERT_TRUE( entities[3] == Entity(6) );
}


TEST_F( ExtendedVectorTest, RemoveItemOfCustomType )
{
    Cx::Vector<Entity> entities;
    entities.AddRange( { Entity(2), Entity(4), Entity(8), Entity(1), Entity(8), Entity(7) } );
    EXPECT_NO_THROW( entities.Remove( Entity( 8 ) ) );
    ASSERT_TRUE( entities[0] == Entity( 2 ) );
    ASSERT_TRUE( entities[1] == Entity( 4 ) );
    ASSERT_TRUE( entities[2] == Entity( 1 ) );
    ASSERT_TRUE( entities[3] == Entity( 8 ) );
    EXPECT_NO_THROW( entities.Remove( Entity( 8 ) ) );
    ASSERT_TRUE( entities[0] == Entity( 2 ) );
    ASSERT_TRUE( entities[1] == Entity( 4 ) );
    ASSERT_TRUE( entities[2] == Entity( 1 ) );
    ASSERT_TRUE( entities[3] == Entity( 7 ) );
}


TEST_F( ExtendedVectorTest, IndexOfSuccessForBasicTypeElement )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    constexpr int expected = 6;
    int result = -1;
    EXPECT_NO_THROW( result = vector.IndexOf( 7 ) );
    ASSERT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, IndexOfSuccessForCustomTypeElement )
{
    Cx::Vector<Entity> entities;
    entities.AddRange( { Entity( 2 ), Entity( 4 ), Entity( 8 ), Entity( 1 ), Entity( 8 ), Entity( 7 ) } );
    constexpr int expected = 3;
    int result = -1;
    EXPECT_NO_THROW( result = entities.IndexOf( Entity(1) ) );
    ASSERT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, IndexOfFailsWhenNoSuchElement )
{
    vector.AddRange( { 1,2,3,4,6,7,8,9 } );
    constexpr int expected = -1;
    int result = 10;
    EXPECT_NO_THROW( result = vector.IndexOf( 5 ) );
    ASSERT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, IndexOfWithSpecificStartSuccessForBasicTypeElement )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    constexpr int expected = 6;
    int result = -1;
    EXPECT_NO_THROW( result = vector.IndexOf( 7, 4 ) );
    ASSERT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, IndexOfWithSpecificStartSuccessForCustomTypeElement )
{
    Cx::Vector<Entity> entities;
    entities.AddRange( { Entity( 2 ), Entity( 4 ), Entity( 8 ), Entity( 1 ), Entity( 8 ), Entity( 7 ) } );
    constexpr int expected = 3;
    int result = -1;
    EXPECT_NO_THROW( result = entities.IndexOf( Entity( 1 ), 1 ) );
    ASSERT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, IndexOfWithSpecificStartAndCountSuccessForBasicTypeElement )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    constexpr int expected = 6;
    int result = -1;
    EXPECT_NO_THROW( result = vector.IndexOf( 7, 4, 4 ) );
    ASSERT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, IndexOfWithSpecificStartAndCountSuccessForCustomTypeElement )
{
    Cx::Vector<Entity> entities;
    entities.AddRange( { Entity( 2 ), Entity( 4 ), Entity( 8 ), Entity( 1 ), Entity( 8 ), Entity( 7 ) } );
    constexpr int expected = 3;
    int result = -1;
    EXPECT_NO_THROW( result = entities.IndexOf( Entity( 1 ), 2, 2 ) );
    ASSERT_TRUE( result == expected );
}


TEST_F( ExtendedVectorTest, FindIndexSuccessForBasicTypeElement )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    constexpr int expected = 6;
    int result = -1;
    EXPECT_NO_THROW( result = vector.FindIndex( []( int element )->bool {return element == 7; } ) );
    ASSERT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, FindIndexSuccessForCustomTypeElement )
{
    Cx::Vector<Entity> entities;
    entities.AddRange( { Entity( 2 ), Entity( 4 ), Entity( 8 ), Entity( 1 ), Entity( 8 ), Entity( 7 ) } );
    constexpr int expected = 3;
    int result = -1;
    EXPECT_NO_THROW( result = entities.FindIndex( []( const Entity& e )->bool { return e == Entity( 1 ); } ) );
    ASSERT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, FindIndexFailsWhenNoSuchElement )
{
    vector.AddRange( { 1,2,3,4,6,7,8,9 } );
    constexpr int expected = -1;
    int result = 10;
    EXPECT_NO_THROW( result = vector.FindIndex( []( int element )->bool {return element == 5; } ) );
    ASSERT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, FindIndexWithSpecificStartSuccessForBasicTypeElement )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    constexpr int expected = 6;
    int result = -1;
    EXPECT_NO_THROW( result = vector.FindIndex( []( int element )->bool {return element == 7; }, 4 ) );
    ASSERT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, FindIndexWithSpecificStartSuccessForCustomTypeElement )
{
    Cx::Vector<Entity> entities;
    entities.AddRange( { Entity( 2 ), Entity( 4 ), Entity( 8 ), Entity( 1 ), Entity( 8 ), Entity( 7 ) } );
    constexpr int expected = 3;
    int result = -1;
    EXPECT_NO_THROW( result = entities.FindIndex( []( const Entity& e )->bool {return e == Entity( 1 ); }, 1 ) );
    ASSERT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, FindIndexWithSpecificStartAndCountSuccessForBasicTypeElement )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    constexpr int expected = 6;
    int result = -1;
    EXPECT_NO_THROW( result = vector.FindIndex( []( int element )->bool {return element == 7; }, 4, 4 ) );
    ASSERT_TRUE( result == expected );
}

TEST_F( ExtendedVectorTest, FindIndexWithSpecificStartAndCountSuccessForCustomTypeElement )
{
    Cx::Vector<Entity> entities;
    entities.AddRange( { Entity( 2 ), Entity( 4 ), Entity( 8 ), Entity( 1 ), Entity( 8 ), Entity( 7 ) } );
    constexpr int expected = 3;
    int result = -1;
    EXPECT_NO_THROW( result = entities.FindIndex( []( const Entity& e )->bool {return e == Entity( 1 ); }, 2, 2 ) );
    ASSERT_TRUE( result == expected );
}


TEST_F( ExtendedVectorTest, ReverseFullScopeOfContainerForOddNumberOfElementsInContainer )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    EXPECT_NO_THROW( vector.Reverse() );
    ASSERT_TRUE( vector[0] == 9 );
    ASSERT_TRUE( vector[1] == 8 );
    ASSERT_TRUE( vector[2] == 7 );
    ASSERT_TRUE( vector[3] == 6 );
    ASSERT_TRUE( vector[4] == 5 );
    ASSERT_TRUE( vector[5] == 4 );
    ASSERT_TRUE( vector[6] == 3 );
    ASSERT_TRUE( vector[7] == 2 );
    ASSERT_TRUE( vector[8] == 1 );
}

TEST_F( ExtendedVectorTest, ReverseFullScopeOfContainerForEvenNumberOfElementsInContainer )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9,10 } );
    EXPECT_NO_THROW( vector.Reverse() );
    ASSERT_TRUE( vector[0] == 10 );
    ASSERT_TRUE( vector[1] == 9 );
    ASSERT_TRUE( vector[2] == 8 );
    ASSERT_TRUE( vector[3] == 7 );
    ASSERT_TRUE( vector[4] == 6 );
    ASSERT_TRUE( vector[5] == 5 );
    ASSERT_TRUE( vector[6] == 4 );
    ASSERT_TRUE( vector[7] == 3 );
    ASSERT_TRUE( vector[8] == 2 );
    ASSERT_TRUE( vector[9] == 1 );
}

TEST_F( ExtendedVectorTest, ReverseRangeInContainerForOddNumberOfElementsInContainer )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    EXPECT_NO_THROW( vector.Reverse(2,4) );
    ASSERT_TRUE( vector[0] == 1 );
    ASSERT_TRUE( vector[1] == 2 );
    ASSERT_TRUE( vector[2] == 6 );
    ASSERT_TRUE( vector[3] == 5 );
    ASSERT_TRUE( vector[4] == 4 );
    ASSERT_TRUE( vector[5] == 3 );
    ASSERT_TRUE( vector[6] == 7 );
    ASSERT_TRUE( vector[7] == 8 );
    ASSERT_TRUE( vector[8] == 9 );
}

TEST_F( ExtendedVectorTest, ReverseRangeInContainerForEvenNumberOfElementsInContainer )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9,10 } );
    EXPECT_NO_THROW( vector.Reverse(4,2) );
    ASSERT_TRUE( vector[0] == 1 );
    ASSERT_TRUE( vector[1] == 2 );
    ASSERT_TRUE( vector[2] == 3 );
    ASSERT_TRUE( vector[3] == 4 );
    ASSERT_TRUE( vector[4] == 6 );
    ASSERT_TRUE( vector[5] == 5 );
    ASSERT_TRUE( vector[6] == 7 );
    ASSERT_TRUE( vector[7] == 8 );
    ASSERT_TRUE( vector[8] == 9 );
    ASSERT_TRUE( vector[9] == 10 );
}

TEST_F( ExtendedVectorTest, ReverseThrowsExceptionWhenExceedingContainerSize )
{
    vector.AddRange( { 1,2,3,4,5,6,7 } );
    EXPECT_THROW( vector.Reverse( 3, 5 ), std::invalid_argument );
}


TEST_F( ExtendedVectorTest, FindLastIndexSuccessForFullContainerRange )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_NO_THROW( result = vector.FindLastIndex( []( const int& element )->bool
        {
            return element == 3;
        } ) );
    ASSERT_TRUE( result != 0 );
    ASSERT_TRUE( result == 9 );
}

TEST_F( ExtendedVectorTest, FindLastIndexFailsForFullContainerRange )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_NO_THROW( result = vector.FindLastIndex( []( const int& element )->bool
        {
            return element == 15;
        } ) );
    ASSERT_TRUE( result != 0 );
    ASSERT_TRUE( result == -1 );
}

TEST_F( ExtendedVectorTest, FindLastIndexSuccessForContainerRangeLimitedByEndIndex )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_NO_THROW( result = vector.FindLastIndex( 4, []( const int& element )->bool
        {
            return element == 3;
        } ) );
    ASSERT_TRUE( result != 0 );
    ASSERT_TRUE( result == 3 );
}

TEST_F( ExtendedVectorTest, FindLastIndexFailsForContainerRangeLimitedByEndIndex )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_NO_THROW( result = vector.FindLastIndex( 4, []( const int& element )->bool
        {
            return element == 67;
        } ) );
    ASSERT_TRUE( result != 0 );
    ASSERT_TRUE( result == -1 );
}

TEST_F( ExtendedVectorTest, FindLastIndexSuccessForContainerRangeLimitedByStartEndIndex )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_NO_THROW( result = vector.FindLastIndex( 3, 8, []( const int& element )->bool
        {
            return element == 15;
        } ) );
    ASSERT_TRUE( result != 0 );
    ASSERT_TRUE( result == -1 );
}

TEST_F( ExtendedVectorTest, FindLastIndexFailsForContainerRangeLimitedByStartEndIndex )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_NO_THROW( result = vector.FindLastIndex( []( const int& element )->bool
        {
            return element == 15;
        } ) );
    ASSERT_TRUE( result != 0 );
    ASSERT_TRUE( result == -1 );
}

TEST_F( ExtendedVectorTest, FindLastIndexThrowsForContainerRangeLimitedByEndIndex )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_THROW( result = vector.FindLastIndex( 50, []( const int& element )->bool
        {
            return element == 15;
        } ),
        std::invalid_argument );
    ASSERT_TRUE( result == 0 );
}

TEST_F( ExtendedVectorTest, FindLastIndexThrowsForContainerRangeLimitedByStartEndIndex )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_THROW( result = vector.FindLastIndex( 6, 20, []( const int& element )->bool
        {
            return element == 15;
        } ),
        std::invalid_argument );
    EXPECT_THROW( result = vector.FindLastIndex( 15, 25, []( const int& element )->bool
        {
            return element == 15;
        } ),
        std::invalid_argument );
    EXPECT_THROW( result = vector.FindLastIndex( 5, 2, []( const int& element )->bool
        {
            return element == 15;
        } ),
        std::invalid_argument );
    ASSERT_TRUE( result == 0 );
}


TEST_F( ExtendedVectorTest, InsertRangeSuccessForDataAsArray )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    constexpr unsigned int dataSize = 5;
    int range[dataSize] = { 10,20,30,40,50 };
    EXPECT_NO_THROW( vector.InsertRange( 3, range, dataSize ) );
    ASSERT_TRUE( vector[0] == 1 );
    ASSERT_TRUE( vector[1] == 2 );
    ASSERT_TRUE( vector[2] == 3 );
    ASSERT_TRUE( vector[3] == 10 );
    ASSERT_TRUE( vector[4] == 20 );
    ASSERT_TRUE( vector[5] == 30 );
    ASSERT_TRUE( vector[6] == 40 );
    ASSERT_TRUE( vector[7] == 50 );
    ASSERT_TRUE( vector[8] == 4 );
    ASSERT_TRUE( vector[9] == 5 );
    ASSERT_TRUE( vector[10] == 6 );
    ASSERT_TRUE( vector[11] == 7 );
    ASSERT_TRUE( vector[12] == 8 );
    ASSERT_TRUE( vector[13] == 9 );
}

TEST_F( ExtendedVectorTest, InsertRangeSuccessForDataAsLValueStdVector )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    std::vector<int> range = { 10,20,30,40,50 };
    EXPECT_NO_THROW( vector.InsertRange( 3, range ) );
    ASSERT_TRUE( vector[0] == 1 );
    ASSERT_TRUE( vector[1] == 2 );
    ASSERT_TRUE( vector[2] == 3 );
    ASSERT_TRUE( vector[3] == 10 );
    ASSERT_TRUE( vector[4] == 20 );
    ASSERT_TRUE( vector[5] == 30 );
    ASSERT_TRUE( vector[6] == 40 );
    ASSERT_TRUE( vector[7] == 50 );
    ASSERT_TRUE( vector[8] == 4 );
    ASSERT_TRUE( vector[9] == 5 );
    ASSERT_TRUE( vector[10] == 6 );
    ASSERT_TRUE( vector[11] == 7 );
    ASSERT_TRUE( vector[12] == 8 );
    ASSERT_TRUE( vector[13] == 9 );
}

TEST_F( ExtendedVectorTest, InsertRangeSuccessForDataAsRValueStdVector )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    std::vector<int> range = { 10,20,30,40,50 };
    EXPECT_NO_THROW( vector.InsertRange( 3, std::move(range) ) );
    ASSERT_TRUE( vector[0] == 1 );
    ASSERT_TRUE( vector[1] == 2 );
    ASSERT_TRUE( vector[2] == 3 );
    ASSERT_TRUE( vector[3] == 10 );
    ASSERT_TRUE( vector[4] == 20 );
    ASSERT_TRUE( vector[5] == 30 );
    ASSERT_TRUE( vector[6] == 40 );
    ASSERT_TRUE( vector[7] == 50 );
    ASSERT_TRUE( vector[8] == 4 );
    ASSERT_TRUE( vector[9] == 5 );
    ASSERT_TRUE( vector[10] == 6 );
    ASSERT_TRUE( vector[11] == 7 );
    ASSERT_TRUE( vector[12] == 8 );
    ASSERT_TRUE( vector[13] == 9 );
}

TEST_F( ExtendedVectorTest, InsertRangeSuccessForDataAsLValueCxVector )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    Cx::Vector<int> range;
    range.AddRange({ 10,20,30,40,50 });
    EXPECT_NO_THROW( vector.InsertRange( 3, range ) );
    ASSERT_TRUE( vector[0] == 1 );
    ASSERT_TRUE( vector[1] == 2 );
    ASSERT_TRUE( vector[2] == 3 );
    ASSERT_TRUE( vector[3] == 10 );
    ASSERT_TRUE( vector[4] == 20 );
    ASSERT_TRUE( vector[5] == 30 );
    ASSERT_TRUE( vector[6] == 40 );
    ASSERT_TRUE( vector[7] == 50 );
    ASSERT_TRUE( vector[8] == 4 );
    ASSERT_TRUE( vector[9] == 5 );
    ASSERT_TRUE( vector[10] == 6 );
    ASSERT_TRUE( vector[11] == 7 );
    ASSERT_TRUE( vector[12] == 8 );
    ASSERT_TRUE( vector[13] == 9 );
}

TEST_F( ExtendedVectorTest, InsertRangeSuccessForDataAsRValueCxVector )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    Cx::Vector<int> range;
    range.AddRange( { 10,20,30,40,50 } );
    EXPECT_NO_THROW( vector.InsertRange( 3, std::move(range) ) );
    ASSERT_TRUE( vector[0] == 1 );
    ASSERT_TRUE( vector[1] == 2 );
    ASSERT_TRUE( vector[2] == 3 );
    ASSERT_TRUE( vector[3] == 10 );
    ASSERT_TRUE( vector[4] == 20 );
    ASSERT_TRUE( vector[5] == 30 );
    ASSERT_TRUE( vector[6] == 40 );
    ASSERT_TRUE( vector[7] == 50 );
    ASSERT_TRUE( vector[8] == 4 );
    ASSERT_TRUE( vector[9] == 5 );
    ASSERT_TRUE( vector[10] == 6 );
    ASSERT_TRUE( vector[11] == 7 );
    ASSERT_TRUE( vector[12] == 8 );
    ASSERT_TRUE( vector[13] == 9 );
}


TEST_F( ExtendedVectorTest, GetRangeSuccessForCorrectRange )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    Cx::Vector<int> range;
    EXPECT_NO_THROW( range = vector.GetRange( 3, 7 ) );
    ASSERT_TRUE( range[0] == 4 );
    ASSERT_TRUE( range[1] == 5 );
    ASSERT_TRUE( range[2] == 6 );
    ASSERT_TRUE( range[3] == 7 );
    ASSERT_TRUE( range.size() == (7 - 3) );
}

TEST_F( ExtendedVectorTest, GetRangeFailsForIncorrectRange )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    Cx::Vector<int> range;
    EXPECT_THROW( range = vector.GetRange( 3, 20 ), std::invalid_argument );
    EXPECT_THROW( range = vector.GetRange( 11, 15 ), std::invalid_argument );
    EXPECT_THROW( range = vector.GetRange( 5, 2 ), std::invalid_argument );
    ASSERT_TRUE( range.size() == 0 );
}


TEST_F( ExtendedVectorTest, LastIndexOfSuccessForFullContainerRange )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_NO_THROW( result = vector.LastIndexOf( 3 ) );
    ASSERT_TRUE( result != 0 );
    ASSERT_TRUE( result == 9 );
}

TEST_F( ExtendedVectorTest, LastIndexOfFailsForFullContainerRange )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_NO_THROW( result = vector.LastIndexOf( 15 ) );
    ASSERT_TRUE( result != 0 );
    ASSERT_TRUE( result == -1 );
}

TEST_F( ExtendedVectorTest, LastIndexOfSuccessForContainerRangeLimitedByEndIndex )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_NO_THROW( result = vector.LastIndexOf( 3, 4 ) );
    ASSERT_TRUE( result != 0 );
    ASSERT_TRUE( result == 3 );
}

TEST_F( ExtendedVectorTest, LastIndexOfFailsForContainerRangeLimitedByEndIndex )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_NO_THROW( result = vector.LastIndexOf( 67, 4 ) );
    ASSERT_TRUE( result != 0 );
    ASSERT_TRUE( result == -1 );
}

TEST_F( ExtendedVectorTest, LastIndexOfSuccessForContainerRangeLimitedByStartEndIndex )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_NO_THROW( result = vector.LastIndexOf( 15, 3, 5 ) );
    ASSERT_TRUE( result != 0 );
    ASSERT_TRUE( result == -1 );
}

TEST_F( ExtendedVectorTest, LastIndexOfFailsForContainerRangeLimitedByStartEndIndex )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_NO_THROW( result = vector.LastIndexOf( 15, 3, 5 ) );
    ASSERT_TRUE( result != 0 );
    ASSERT_TRUE( result == -1 );
}

TEST_F( ExtendedVectorTest, LastIndexOfThrowsForContainerRangeLimitedByEndIndex )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_THROW( result = vector.LastIndexOf( 15, 50 ), std::invalid_argument );
    ASSERT_TRUE( result == 0 );
}

TEST_F( ExtendedVectorTest, LastIndexOfThrowsForContainerRangeLimitedByStartEndIndex )
{
    vector.AddRange( { 1,3,2,3,5,67,3,2,54,3,12 } );
    int result = 0;
    EXPECT_THROW( result = vector.LastIndexOf( 15, 6, 20 ), std::invalid_argument );
    EXPECT_THROW( result = vector.LastIndexOf( 15, 15, 25 ), std::invalid_argument );
    ASSERT_TRUE( result == 0 );
}


TEST_F( ExtendedVectorTest, ConvertAllSuccessForBasicType )
{
    vector.AddRange( { 1,2,3,4,5,6,7,8,9 } );
    Cx::Vector<float> converted;
    ASSERT_NO_THROW( converted = vector.ConvertAll<float>( []( int item )->float{ return item + 0.5f; } ) );
    ASSERT_TRUE( converted.size() == vector.size() );
    for( unsigned int i = 0; i < converted.size(); ++i )
        ASSERT_TRUE( converted[i] == i + 1.5f );
}


TEST_F( ExtendedVectorTest, RemoveAtSuccessForCorrectIndex )
{
    vector.AddRange( { 0,1,2,3,4,5,6,7,8,9 } );
    ASSERT_TRUE( vector.size() == 10 );
    ASSERT_TRUE( vector[4] == 4 );
    ASSERT_NO_THROW( vector.RemoveAt( 4 ) );
    ASSERT_TRUE( vector.size() == 9 );
    ASSERT_TRUE( vector[3] == 3 );
    ASSERT_TRUE( vector[4] == 5 );
    ASSERT_TRUE( vector[5] == 6 );
}

TEST_F( ExtendedVectorTest, RemoveAtFailsForIncorrectIndex )
{
    vector.AddRange( { 0,1,2,3,4,5,6,7,8,9 } );
    ASSERT_TRUE( vector.size() == 10 );
    ASSERT_THROW( vector.RemoveAt( 15 ), std::invalid_argument );
    ASSERT_TRUE( vector.size() == 10 );
}


TEST_F( ExtendedVectorTest, ForEachElementActionIsPerformed )
{
    vector.AddRange( { 0,0,0,0,0,0,0,0,0,0 } );
    int iteration = 0;
    EXPECT_NO_THROW( vector.ForEach( [&]( int& element )
        {
            element += iteration * 2;
            iteration++;
        } ) );
}


TEST_F( ExtendedVectorTest, FindAllSuccess )
{
    vector.AddRange( { 13,2,14,3,1,15,16,23,24 } );
    Cx::Vector<int> results;
    EXPECT_NO_THROW( results = vector.FindAll( []( const int& element )->bool {return element % 2 == 0; } ) );
    ASSERT_TRUE( results.size() == 4 );
    ASSERT_TRUE( results[0] == 2 );
    ASSERT_TRUE( results[1] == 14 );
    ASSERT_TRUE( results[2] == 16 );
    ASSERT_TRUE( results[3] == 24 );
}

TEST_F( ExtendedVectorTest, FindAllFailsByLeavingEmptyDefaultContainer )
{
    vector.AddRange( { 13,2,14,3,1,15,16,23,24 } );
    Cx::Vector<int> results;
    EXPECT_NO_THROW( results = vector.FindAll( []( const int& element )->bool {return element % 9 == 0; } ) );
    ASSERT_TRUE( results.size() == 0 );
}