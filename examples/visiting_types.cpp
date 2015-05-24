// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

/// @example visting_types.cpp
///
/// Visiting types in a typelist

#include <meta/typelist.hpp>

#include <typeinfo>
#include <iostream>
#include <vector>

struct print_types
{
    template<class T>
    void operator()(T)
    {
        std::cout << typeid(T).name() << std::endl;
    }
};

int main()
{
    using types = meta::typelist<std::vector<int>, int, double>;

    types::visit(print_types());
}
