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
