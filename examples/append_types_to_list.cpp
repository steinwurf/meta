// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

/// @example append_types_to_list.cpp
///
/// Appending types to typelist

#include <meta/typelist.hpp>

int main()
{
    using types = meta::typelist<double,float>;
    using result = types::append<int>;

    static_assert(std::is_same<result,
                  meta::typelist<double,float,int>>::value, "");
}
