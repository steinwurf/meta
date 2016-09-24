// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <type_traits>

namespace meta
{

/// @brief Finds a type based on the specific feature tag
///
/// The find meta function accepts a variable list of template
/// arguments, it then instantiates the Predicate template with each
/// type and checks the Predicate<T>::value. If the value evaluates
/// true find<Predicate, Default, List>::type will equal T. If
/// Predicate<T>::value is false for all types in List then
/// find<Predicate, Default, List>::type will be set to Default.
template
<
    template <class> class Predicate,
    class NotFound,
    class... List
>
struct find;

/// Specialization for when the list is empty, we just set type = NotFound
template
<
    template <class> class Predicate,
    class NotFound
>
struct find<Predicate, NotFound>
{
    using type = NotFound;
};

/// Specialization when there is at lets one element in the list
template
<
    template <class> class Predicate,
    class NotFound,
    class T,
    class... List
>
struct find<Predicate, NotFound, T, List...>
{
    // If Predicate<T>::value is true then type = T
    // Else we call find for the next type in the list
    using type = typename std::conditional<
                 Predicate<T>::value,
                 T, typename find<Predicate, NotFound, List...>::type>::type;
};
}
