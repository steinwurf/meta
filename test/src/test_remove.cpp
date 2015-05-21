// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <meta/remove.hpp>

#include <meta/typelist.hpp>

#include <gtest/gtest.h>

// Tests that our remove meta function works properly
TEST(test_remove, basic)
{
    {
        using result =
            meta::remove<std::is_integral, int, double, float>::type;
        bool value = std::is_same<result, meta::typelist<double,float> >::value;
        EXPECT_TRUE(value);
    }

    {
        using result =
            meta::remove<std::is_integral, double, float>::type;
        bool value = std::is_same<result, meta::typelist<double,float> >::value;
        EXPECT_TRUE(value);
    }

    {
        using result =
            meta::remove<std::is_integral>::type;
        bool value = std::is_same<result, meta::typelist<> >::value;
        EXPECT_TRUE(value);
    }
}
