#include "Extension/Extension.hpp"
#include <gtest/gtest.h>
#include <iostream>


template<class T>
class Vector : public Cx::ExtendedVector<T>
{
public:
    Vector()
    {}
};


class ExtendedVectorTest : public testing::Test
{
public:
    Vector<int> vector;
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
    Vector<int> newVector;
    newVector.AddRange({1,15,23,56});
    vector.AddRange(newVector);
    ASSERT_TRUE(vector[0] == 1);
    ASSERT_TRUE(vector[1] == 15);
    ASSERT_TRUE(vector[2] == 23);
    ASSERT_TRUE(vector[3] == 56);
}


TEST_F(ExtendedVectorTest, AddRangeByAnotherCxVectorGivenByRValue)
{
    Vector<int> newVector;
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
    class Entity
    {
    public:
        Entity( int i, float j ) : i{ i }, j{ j }
        {}

        bool operator==(const Entity& element ) const
        {
            if( this->i == element.i && this->j == element.j )
                return true;
            else
                return false;
        }

        int i;
        float j;
    };

    Vector<Entity> newVector;
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
    class Entity
    {
    public:
        Entity(int i) : i{i}
        {}
        int i;
        bool operator<( const Entity& e )
        {
            return i < e.i;
        }
    };
    Vector<Entity> newVector;
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
    class Entity
    {
    public:
        Entity( int i ) : i{ i }
        {}
        int i;
        bool operator<( const Entity& e )
        {
            return i < e.i;
        }
    };
    Vector<Entity> newVector;
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
    class Entity
    {
    public:
        Entity( int i ) : i{ i }
        {}
        int i;
    };
    Vector<Entity> newVector;
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
    class Entity
    {
    public:
        Entity( int i ) : i{ i }
        {
        }
        int i;
    };
    Vector<Entity> newVector;
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
    class Entity
    {
    public:
        Entity() = default;
        Entity(int i) : i{i} {}
        int i;
    };

    Vector<Entity> newVector;
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
    class Entity
    {
    public:
        Entity( int i ) : i{ i } {}
        int i;
    };

    Vector<Entity> newVector;
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
