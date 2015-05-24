// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <meta/find.hpp>
#include <meta/template_is_same.hpp>

#include <gtest/gtest.h>

template<class T>
struct type_one;

struct type_two
{ };

struct not_found
{ };

template<class U>
using is_type_one = meta::template_is_same<type_one, U>;

template<class U>
using is_int = std::is_same<int, U>;


// Tests that our find meta function works properly
TEST(test_find, basic)
{
    {
        // Try to find the type_one struct
        using result =
            meta::find<is_type_one, not_found, int, double, type_one<int>>::type;
        bool value = std::is_same<result, type_one<int> >::value;
        EXPECT_TRUE(value);
    }

    {
        // Try to find the type_one struct, but return not_found since it
        // is not there
        using result =
            meta::find<is_type_one, not_found, int, double, type_two>::type;
        bool v1 = std::is_same<result, type_one<int> >::value;
        bool v2 = std::is_same<result, not_found>::value;
        EXPECT_FALSE(v1);
        EXPECT_TRUE(v2);
    }

    {
        // Find the int in the list
        using result =
            meta::find<is_int, not_found, int, double, type_two>::type;
        bool v1 = std::is_same<result, int>::value;
        bool v2 = std::is_same<result, not_found>::value;
        EXPECT_TRUE(v1);
        EXPECT_FALSE(v2);
    }

    {
        using result =
            meta::find<is_int, not_found, int, int, double, type_two>::type;
        bool v1 = std::is_same<result, int>::value;
        bool v2 = std::is_same<result, not_found>::value;
        EXPECT_TRUE(v1);
        EXPECT_FALSE(v2);
    }
}
