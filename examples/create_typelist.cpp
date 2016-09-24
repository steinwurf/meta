// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

/// @example create_typelist.cpp
///
/// Create typelist from README.rst

#include <meta/typelist.hpp>

int main()
{
    using types = meta::typelist<double,float>;

    static_assert(std::is_same<types,
                  meta::typelist<double,float>>::value, "");
}
