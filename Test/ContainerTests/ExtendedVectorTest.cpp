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
