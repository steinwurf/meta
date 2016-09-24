// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

namespace meta
{
/// @brief Will take variadic template list and for each element invoke
///        the call operator of the Visitor object passed to the visit
///        function.
template<class... List>
struct visitor
{
    template<class Visitor>
    static void visit(Visitor&&) {}
};

// Specialization where there is at least one element in the list
template<class T, class... List>
struct visitor<T, List...>
{
    template<class Visitor>
    static void visit(Visitor&& v)
    {
        // Invoke the call operator on the v object passing in a
        // default constructed object of type T.
        v(T{});

        // Recursive pass the remaining types to visitor, to visit the
        // next element in the list
        visitor<List...>::template visit(v);
    }
};
}
