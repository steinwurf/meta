// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <type_traits>

namespace meta
{
    /// @brief Conditionally appends types to a typelist.
    ///
    /// The conditional_append meta function iterates though a variadic
    /// list of template arguments. For each type T in the list it uses the
    /// Predicate<T>::value to conditonally append the type ot the
    /// TypeList. The TypeList should be of type typelist or an otherwise
    /// compatible type.
    template
    <
        template <class> class Predicate,
        class TypeList,
        class...
    >
    struct conditional_append;

    /// Specialization for an empty list
    template
    <
        template <class> class Predicate,
        class TypeList
    >
    struct conditional_append<Predicate, TypeList>
    {
        using type = TypeList;
    };

    /// Specialization for an list with at least one element
    template
    <
        template <class> class Predicate,
        class TypeList,
        class T,
        class... List
    >
    struct conditional_append<Predicate, TypeList, T, List...>
    {
        using type = typename std::conditional<
            Predicate<T>::value,
            typename conditional_append<Predicate,
                typename TypeList::template append<T>, List...>::type,
            typename conditional_append<Predicate,
                TypeList, List...>::type>::type;
    };
}
