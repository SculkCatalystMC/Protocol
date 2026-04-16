// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"
#include <magic_enum/magic_enum.hpp>
#include <sculk/reflection/utils/string_utils.hpp>
#include <type_traits>

namespace sculk::protocol::inline abi_v944::utils {

template <typename Enum>
    requires std::is_enum_v<Enum>
constexpr std::string_view enum_to_str(Enum value) {
    auto name = magic_enum::enum_name(value);
    if (name.empty()) return magic_enum::enum_name(Enum{});
    return name;
}

template <typename Enum>
    requires std::is_enum_v<Enum>
constexpr Enum str_to_enum(std::string_view value) {
    auto opt = magic_enum::enum_cast<Enum>(value, magic_enum::case_insensitive);
    if (!opt.has_value()) return Enum{};
    return *opt;
}

template <typename T>
    requires std::is_enum_v<T>
[[nodiscard]] constexpr Result<>
readEnumName(ReadOnlyBinaryStream& stream, T& outValue _SCULK_SL_PARAM_DEFAULT) noexcept {
    std::string enumName{};
    if (!stream.readString(enumName _SCULK_SL_PARAM_PASS)) {
        return error_utils::makeError("ReadOnlyBinaryStream::readEnumName overflowed" _SCULK_SL_PARAM_PASS);
    }
    outValue = utils::str_to_enum<T>(enumName);
    return {};
}

template <typename T>
    requires std::is_enum_v<T>
constexpr void writeEnumName(BinaryStream& stream, T value) {
    stream.writeString(reflection::string_utils::to_lower_case(utils::enum_to_str(value)));
}

} // namespace sculk::protocol::inline abi_v944::utils