// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "Result.hpp"
#include <type_traits>
#include <variant>

namespace sculk::protocol::inline abi_v944 {

namespace detail {

template <typename Var, std::size_t... Is>
Result<>
emplace_variant_impl(Var& v, std::size_t idx, std::source_location location, std::index_sequence<Is...>) noexcept {
    using emplace_func             = void (*)(Var&);
    constexpr emplace_func table[] = {+[](Var& var) { var.template emplace<Is>(); }...};

    if (idx >= sizeof...(Is)) {
        return error_utils::makeError("emplace_variant_impl: index out of range", location);
    }

    table[idx](v);
    return {};
}

} // namespace detail

template <typename... Ts>
struct Overload : Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
Overload(Ts...) -> Overload<Ts...>;

template <typename Var>
Result<> emplace_variant(Var& v, std::size_t idx, std::source_location location) noexcept {
    constexpr std::size_t N = std::variant_size_v<std::remove_reference_t<Var>>;
    return detail::emplace_variant_impl(v, idx, location, std::make_index_sequence<N>{});
}

} // namespace sculk::protocol::inline abi_v944
