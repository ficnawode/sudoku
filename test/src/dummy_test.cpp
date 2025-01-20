#include "gtest/gtest.h"
#include "dummy/dummy.hpp"

namespace
{
    // NOLINTBEGIN
    TEST(dummy_tests, add)
    {
        EXPECT_EQ(5, dummy::add(2, 3));
    }
    // NOLINTEND
}