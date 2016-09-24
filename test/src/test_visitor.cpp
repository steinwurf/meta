// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <meta/visitor.hpp>

#include <gtest/gtest.h>


// Tests that our visitor meta function works properly
TEST(test_visitor, basic)
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

    using v = meta::visitor<int, float, double>;

    count t;
    v::visit(t);

    EXPECT_TRUE(t.m_int);
    EXPECT_TRUE(t.m_float);
    EXPECT_TRUE(t.m_double);
}
