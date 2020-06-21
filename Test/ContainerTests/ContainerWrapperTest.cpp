#include "Wrapper/Container.hpp"
#include <gtest/gtest.h>


class WrapperTest : public testing::Test
{
public:
    Cx::VectorContainer<int> wrapped;
};


TEST_F(WrapperTest, InitializerListConstructorTest)
{
    Cx::VectorContainer<int> container {2, 3, 4};
    ASSERT_TRUE(container[0] == 2);
    ASSERT_TRUE(container[1] == 3);
    ASSERT_TRUE(container[2] == 4);
}
