// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/utility/deps/Result.hpp"
#include <sculk/reflection/jsonc/reflection.hpp>

namespace sculk::protocol::inline abi_v944::utils {

namespace {
static constexpr auto json_key_formatter = [](std::string_view sv) noexcept -> std::string {
    if (sv.starts_with('m')) {
        sv.remove_prefix(1); // Remove the first character (m)
    }
    return std::string(sv);
};
static auto json_options = reflection::jsonc::options{.allow_trailing_comma = false, .enum_cast_prefer_string = false};
} // namespace

template <typename T>
inline std::string serialize_json(const T& value) {
    return reflection::jsonc::serialize<false, false>(value, json_key_formatter, json_options).dump(-1);
}

template <typename T>
inline jsonc::json serialize_to_json(const T& value) {
    return reflection::jsonc::serialize<false, false>(value, json_key_formatter, json_options);
}

template <typename T>
inline Result<> deserialize_json(T& value, std::string_view json _SCULK_SL_PARAM_DEFAULT) {
    auto jsonObj = jsonc::jsonc::parse(json);
    if (!jsonObj) return error_utils::makeError("Failed to parse JSON: {}" _SCULK_SL_PARAM_PASS);
    if (!reflection::jsonc::deserialize<false, false>(value, *jsonObj, json_key_formatter, json_options)) {
        return error_utils::makeError("Failed to deserialize JSON: {}" _SCULK_SL_PARAM_PASS);
    }
    return {};
}

template <typename T>
inline Result<> deserialize_from_json(T& value, const jsonc::json& json _SCULK_SL_PARAM_DEFAULT) {
    if (!reflection::jsonc::deserialize<false, false>(value, json, json_key_formatter, json_options)) {
        return error_utils::makeError("Failed to deserialize JSON: {}" _SCULK_SL_PARAM_PASS);
    }
    return {};
}


} // namespace sculk::protocol::inline abi_v944::utils