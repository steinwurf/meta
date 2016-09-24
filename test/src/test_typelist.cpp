// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <meta/typelist.hpp>
#include <meta/template_is_same.hpp>

#include <gtest/gtest.h>

#include <vector>

namespace
{
struct dummy {};
}

// Tests that our concatenate meta function works properly
TEST(test_type_list, append)
{
    {
        using types = meta::typelist<>::append<int>::append<bool>;

        bool value = std::is_same<types,
                     meta::typelist<int,bool>>::value;

        EXPECT_TRUE(value);
    }

    {
        using types = meta::typelist<double, float>::append<int>::append<bool>;

        bool value = std::is_same<types,
                     meta::typelist<double,float,int,bool>>::value;

        EXPECT_TRUE(value);
    }
}

TEST(test_type_list, append_multiple)
{
    {
        using types = meta::typelist<>::append<int,bool>;

        bool value = std::is_same<types,
                     meta::typelist<int,bool>>::value;

        EXPECT_TRUE(value);
    }

    {
        using types = meta::typelist<double, float>::append<int,bool>;

        bool value = std::is_same<types,
                     meta::typelist<double,float,int,bool>>::value;

        EXPECT_TRUE(value);
    }
}

TEST(test_type_list, extend)
{
    {
        using list_one = meta::typelist<>;
        using list_two = meta::typelist<>;

        using result = list_one::extend<list_two>;

        bool value = std::is_same<result,
                     meta::typelist<>>::value;

        EXPECT_TRUE(value);
    }

    {
        using list_one = meta::typelist<>;
        using list_two = meta::typelist<int>;

        using result = list_one::extend<list_two>;

        bool value = std::is_same<result,
                     meta::typelist<int>>::value;

        EXPECT_TRUE(value);
    }

    {
        using list_one = meta::typelist<int>;
        using list_two = meta::typelist<>;

        using result = list_one::extend<list_two>;

        bool value = std::is_same<result,
                     meta::typelist<int>>::value;

        EXPECT_TRUE(value);
    }

    {
        using list_one = meta::typelist<int, double>;
        using list_two = meta::typelist<float, bool>;

        using result = list_one::extend<list_two>;

        bool value = std::is_same<result,
                     meta::typelist<int, double, float, bool>>::value;
        EXPECT_TRUE(value);
    }

    {
        using list_one = meta::typelist<int>;
        using list_two = meta::typelist<float, bool>;

        using result = list_one::extend<list_two>;

        bool value = std::is_same<result,
                     meta::typelist<int, float, bool>>::value;
        EXPECT_TRUE(value);
    }
}


TEST(test_type_list, find)
{
    {
        // Test find when no type exists using default NotFound
        using types = meta::typelist<double,float>;
        using result = types::find<std::is_integral>;

        bool value = std::is_same<result, meta::not_found>::value;

        EXPECT_TRUE(value);
    }

    {
        // Test find when no type exists using custom NotFound
        using types = meta::typelist<double,float>;
        using result = types::find<std::is_integral, dummy>;

        bool value = std::is_same<result, dummy>::value;

        EXPECT_TRUE(value);
    }

    {
        // Test find when type exists
        using types = meta::typelist<double,int,float>;
        using result = types::find<std::is_integral>;

        bool value = std::is_same<result, int>::value;

        EXPECT_TRUE(value);
    }

    {
        // Test find when type exists and custom NotFound is used
        using types = meta::typelist<double,int,float>;
        using result = types::find<std::is_integral, dummy>;

        bool value = std::is_same<result, int>::value;

        EXPECT_TRUE(value);
    }
}

TEST(test_type_list, visit)
{
    struct count
    {
        void operator()(int) { m_int = true; }
        void operator()(float) { m_float = true; }
        void operator()(double) { m_double = true; }

        bool m_int = false;
        bool m_float = false;
        bool m_double = false;
    };

    using types1 = meta::typelist<double,float>;

    count check1;
    types1::visit(check1);

    EXPECT_FALSE(check1.m_int);
    EXPECT_TRUE(check1.m_float);
    EXPECT_TRUE(check1.m_double);

    using types2 = types1::append<int>;

    count check2;
    types2::visit(check2);

    EXPECT_TRUE(check2.m_int);
    EXPECT_TRUE(check2.m_float);
    EXPECT_TRUE(check2.m_double);
}

TEST(test_type_list, remove)
{
    {
        // Test remove when type matches
        using types = meta::typelist<double,int,float,int>;
        using result = types::remove<std::is_integral>;

        bool value = std::is_same<result,
                     meta::typelist<double,float>>::value;

        EXPECT_TRUE(value);
    }

    {
        // Test remove when no type matches
        using types = meta::typelist<double, float>;
        using result = types::remove<std::is_integral>;

        bool value = std::is_same<result,
                     meta::typelist<double,float>>::value;

        EXPECT_TRUE(value);
    }

    {
        // Test remove with empty list
        using types = meta::typelist<>;
        using result = types::remove<std::is_integral>;

        bool value = std::is_same<result,
                     meta::typelist<>>::value;

        EXPECT_TRUE(value);
    }
}
