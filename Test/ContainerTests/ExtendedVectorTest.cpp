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
