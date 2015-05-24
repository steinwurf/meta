// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <type_traits>

#include "conditional_append.hpp"
#include "typelist_fwd.hpp"

namespace meta
{
    /// @brief Removes types for the variadic template list if the match
    ///        the predicate.
    ///
    /// To implement this feature we rely on the conditional_append meta
    /// function which will append types to a typelist if they match the
    /// Predicate. Removing elements can therefore be implemented by
    /// iterating the variadic types and only appending those that do not
    /// match the predicate. So a conditional_append with negated prefix
    /// will return a list of types without the types matching the
    /// Predicate.
    template
    <
        template <class> class Predicate,
        class... Args
    >
    struct remove
    {
        // Small helper negates the Predicate
        template<class U>
        struct negate_prediate : public std::conditional<
            Predicate<U>::value, std::false_type, std::true_type>::type
        { };

        // Call conditional append
        using type = typename
            conditional_append<negate_prediate, typelist<>, Args...>::type;
    };
}
