// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <algorithm>
#include <array>
#include <bit>
#include <type_traits>

namespace sculk::protocol::inline abi_v944 {

template <typename T>
    requires std::is_trivially_copyable_v<T>
[[nodiscard]] constexpr T swapEndian(T u) noexcept {
    if constexpr (sizeof(T) == 1) {
        return u;
    } else {
        auto bytes = std::bit_cast<std::array<std::byte, sizeof(T)>>(u);
        std::reverse(bytes.begin(), bytes.end());
        return std::bit_cast<T>(bytes);
    }
}

} // namespace sculk::protocol::inline abi_v944
