// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <meta/concatenate.hpp>
#include <meta/typelist.hpp>

#include <gtest/gtest.h>

// Tests that our concatenate meta function works properly
TEST(test_concatenate, empty)
{
    using list_one = meta::typelist<>;
    using list_two = meta::typelist<>;

    using result = meta::concatenate<list_one, list_two>::type;

    bool value = std::is_same<result,
        meta::typelist<>>::value;

    EXPECT_TRUE(value);
}

TEST(test_concatenate, one_empty)
{
    using list_one = meta::typelist<>;
    using list_two = meta::typelist<int>;

    using result = meta::concatenate<list_one, list_two>::type;

    bool value = std::is_same<result,
        meta::typelist<int>>::value;

    EXPECT_TRUE(value);
}

TEST(test_concatenate, two_empty)
{
    using list_one = meta::typelist<int>;
    using list_two = meta::typelist<>;

    using result = meta::concatenate<list_one, list_two>::type;

    bool value = std::is_same<result,
        meta::typelist<int>>::value;

    EXPECT_TRUE(value);
}

TEST(test_concatenate, basic)
{
    using list_one = meta::typelist<int, double>;
    using list_two = meta::typelist<float, bool>;

    using result = meta::concatenate<list_one, list_two>::type;

    bool value = std::is_same<result,
        meta::typelist<int, double, float, bool>>::value;
    EXPECT_TRUE(value);
}

TEST(test_concatenate, basic_unequal_length)
{
    using list_one = meta::typelist<int>;
    using list_two = meta::typelist<float, bool>;

    using result = meta::concatenate<list_one, list_two>::type;

    bool value = std::is_same<result,
        meta::typelist<int, float, bool>>::value;
    EXPECT_TRUE(value);
}
