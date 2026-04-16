// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <expected>
#include <string_view>

#ifdef SCULK_PROTOCOL_DEBUG
#include <source_location>
#endif

namespace sculk::protocol::inline abi_v944 {

#ifdef SCULK_PROTOCOL_DEBUG
#define _SCULK_SL_PARAM_DEFAULT , std::source_location location = std::source_location::current()
#define _SCULK_SL_PARAMETER_DEF , std::source_location location
#define _SCULK_SL_PARAM_PASS    , location
#define _SCULK_SL_PARAMETER     , std::source_location
#else
#define _SCULK_SL_PARAM_DEFAULT
#define _SCULK_SL_PARAMETER_DEF
#define _SCULK_SL_PARAM_PASS
#define _SCULK_SL_PARAMETER
#endif

struct ErrorInfo {
    std::string_view mMessage{};
#ifdef SCULK_PROTOCOL_DEBUG
    std::source_location mLocation{};
#endif

#ifdef SCULK_PROTOCOL_DEBUG
    [[nodiscard]] constexpr ErrorInfo(std::string_view message, std::source_location location) noexcept
    : mMessage(message),
      mLocation(location) {}
#else
    [[nodiscard]] constexpr explicit ErrorInfo(std::string_view message) noexcept : mMessage(message) {}
#endif
};

template <typename T = void>
using Result = std::expected<T, ErrorInfo>;

namespace error_utils {

[[nodiscard]] constexpr std::unexpected<ErrorInfo> makeError(std::string_view error _SCULK_SL_PARAM_DEFAULT) noexcept {
    return std::unexpected(ErrorInfo(error _SCULK_SL_PARAM_PASS));
}

} // namespace error_utils

} // namespace sculk::protocol::inline abi_v944