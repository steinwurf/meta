// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include "typelist_fwd.hpp"

namespace meta
{
/// @brief Concatenates two typelists
template<class ListOne, class ListTwo>
struct concatenate;

// Specialization where we "extract" the types contained in the two lists
template<class... TypesOne, class... TypesTwo>
struct concatenate<typelist<TypesOne...>, typelist<TypesTwo...>>
{
    using type = typelist<TypesOne...,TypesTwo...>;
};
}
