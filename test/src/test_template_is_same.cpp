// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <meta/template_is_same.hpp>
#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <map>

// Tests that our is template_is_same meta function works properly
TEST(test_template_is_same, basic)
{
    {
        using is_vector = meta::template_is_same<std::vector, std::vector<int>>;
        EXPECT_TRUE(is_vector::value);
    }

    {
        using is_vector = meta::template_is_same<std::vector, std::string>;
        EXPECT_FALSE(is_vector::value);
    }

    {
        using is_vector = meta::template_is_same<std::vector, std::map<int,int>>;
        EXPECT_FALSE(is_vector::value);
    }

    {
        using is_basic_string =
            meta::template_is_same<std::basic_string, std::string>;

        EXPECT_TRUE(is_basic_string::value);
    }
}
