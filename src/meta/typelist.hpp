// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include "find.hpp"
#include "visitor.hpp"
#include "remove.hpp"
#include "not_found.hpp"

namespace meta
{
    /// @brief Typelist list which basically is a "container" for a
    ///        variable number of template arguments.
    ///
    /// Using the "meta" methods define here we can manipulate the content
    /// of the type list.
    template<class... Types>
    struct typelist
    {
        /// Appends a type to the list.
        ///
        ///     using result = typelist<>::template
        ///         append<std::vector<int>>::template
        ///         append<double>;
        ///
        /// The results is typelist<std::vector<int>,double>
        ///
        template<class Type>
        using append = typelist<Types..., Type>;

        /// Finds a type in the list.
        ///
        ///     using types =
        ///         typelist<std::vector<int>, int, double>;
        ///
        ///     using result = types::template
        ///         find<std::is_integral>;
        ///
        /// The results is int
        ///
        template
        <
            template <class> class Predicate,
            class NotFound = not_found
        >
        using find = typename find<Predicate, NotFound, Types...>::type;

        /// Visit each type in the list.
        ///
        ///    using types = typelist<my_type_one, my_type_two>;
        ///
        ///    struct print
        ///    {
        ///        template<class T>
        ///        void operator()(T)
        ///        {
        ///            std::cout << T::to_string() << std::endl;
        ///        }
        ///    };
        ///
        ///    types::template visit(print());
        ///
        /// To use visit the types contained in the list must be default
        /// constructed. Furthermore in the specific example show above we
        /// use a static member of the types called to_string() this would
        /// need to be adapted to the specific types in the type list.
        ///
        template<class Visitor>
        static void visit(Visitor&& v)
        {
            visitor<Types...>::template visit(v);
        }

        /// Removes an item from the list if present
        ///
        ///    using types =
        ///         typelist<std::vector<int>, int, double>;
        ///
        ///    using result = types::template
        ///        remove<std::is_integral>;
        ///
        /// The results is typelist<std::vector<int>, double>
        ///
        template<template <class> class Predicate>
        using remove = typename remove<Predicate, Types...>::type;
    };
}
