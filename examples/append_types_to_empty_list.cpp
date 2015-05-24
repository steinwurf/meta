// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

/// @example append_types_to_empty_list.cpp
///
/// Appending types to empty typelist

#include <meta/typelist.hpp>

int main()
{
    using types = meta::typelist<>::append<double>::append<float>;

    static_assert(std::is_same<types,
        meta::typelist<double,float>>::value, "");
}
