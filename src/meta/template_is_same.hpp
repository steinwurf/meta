// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <type_traits>

namespace meta
{
/// Template is same allows us to determine whether a specific type is an
/// instantiation of a specific template.
///
///     using is_vector = template_is_same<std::vector, std::vector<int>>;
///     std::cout << is_vector::value << std::endl;
///
/// Prints "1", on the other hand:
///
///     using is_vector = template_is_same<std::vector, std::map<int,int>>;
///     std::cout << is_vector::value << std::endl;
///
/// Prints "0"
///
template<template <class...> class T, class U>
struct template_is_same : std::false_type
{ };

template<template <class...> class T, class... Arg>
struct template_is_same<T, T<Arg...>> : std::true_type
{ };
}
