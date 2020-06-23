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

