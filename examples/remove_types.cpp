// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

/// @example remove_types.cpp
///
/// Removing types from a typelist

#include <meta/typelist.hpp>

#include <vector>

int main()
{
    using types = meta::typelist<std::vector<int>, int, double>;

    using result = types::remove<std::is_integral>;

    static_assert(std::is_same<result,
                  meta::typelist<std::vector<int>, double>>::value, "");
}
