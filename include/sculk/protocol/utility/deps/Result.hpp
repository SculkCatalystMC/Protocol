// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <expected>
#include <format>
#include <source_location>
#include <string_view>

namespace sculk::protocol::inline abi_v944 {

struct ErrorInfo {
    std::string_view     mMessage{};
    std::source_location mLocation{};

    [[nodiscard]] constexpr ErrorInfo(std::string_view message, std::source_location location) noexcept
    : mMessage(message),
      mLocation(location) {}
};

template <typename T = void>
using Result = std::expected<T, ErrorInfo>;

namespace error_utils {

[[nodiscard]] constexpr std::unexpected<ErrorInfo>
makeError(std::string_view error, std::source_location location) noexcept {
    return std::unexpected(ErrorInfo(error, location));
}

} // namespace error_utils

} // namespace sculk::protocol::inline abi_v944