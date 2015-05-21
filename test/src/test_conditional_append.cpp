// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <meta/conditional_append.hpp>

#include <meta/typelist.hpp>

#include <gtest/gtest.h>

// Tests that our conditional_append meta function works properly
TEST(test_conditional_append, basic)
{
    {
        using result =
            meta::conditional_append<std::is_integral, meta::typelist<>,
                int, double, float>::type;

        bool value = std::is_same<result, meta::typelist<int> >::value;
        EXPECT_TRUE(value);
    }

    {
        using result =
            meta::conditional_append<std::is_integral, meta::typelist<>,
                double, float>::type;

        bool value = std::is_same<result, meta::typelist<> >::value;
        EXPECT_TRUE(value);
    }

    {
        using result =
            meta::conditional_append<std::is_integral, meta::typelist<>>::type;

        bool value = std::is_same<result, meta::typelist<> >::value;
        EXPECT_TRUE(value);
    }
}
