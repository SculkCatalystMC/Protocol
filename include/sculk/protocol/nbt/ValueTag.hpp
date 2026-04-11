// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"
#include <cstdint>

namespace sculk::protocol::inline abi_v944 {

template <typename T>
struct ValueTag {
    [[no_unique_address]] T mValue{};

    void serialize(BinaryStream& stream) const {
        if constexpr (std::is_same_v<T, std::monostate>) {
            // Nothing to write
        } else if constexpr (std::is_same_v<T, std::int8_t>) {
            stream.writeSignedChar(mValue);
        } else if constexpr (std::is_same_v<T, std::int16_t>) {
            stream.writeSignedShort(mValue);
        } else if constexpr (std::is_same_v<T, std::int32_t>) {
            stream.writeVarInt(mValue);
        } else if constexpr (std::is_same_v<T, std::int64_t>) {
            stream.writeVarInt64(mValue);
        } else if constexpr (std::is_same_v<T, float>) {
            stream.writeFloat(mValue);
        } else if constexpr (std::is_same_v<T, double>) {
            stream.writeDouble(mValue);
        } else if constexpr (std::is_same_v<T, std::string>) {
            stream.writeString(mValue);
        } else {
            static_assert(false, "Invalid ValueTag<T> template");
        }
    }

    [[nodiscard]] Result<> deserialize(ReadOnlyBinaryStream& stream) {
        if constexpr (std::is_same_v<T, std::monostate>) {
            return Result<>{}; // Nothing to read
        } else if constexpr (std::is_same_v<T, std::int8_t>) {
            return stream.readSignedChar(mValue);
        } else if constexpr (std::is_same_v<T, std::int16_t>) {
            return stream.readSignedShort(mValue);
        } else if constexpr (std::is_same_v<T, std::int32_t>) {
            return stream.readVarInt(mValue);
        } else if constexpr (std::is_same_v<T, std::int64_t>) {
            return stream.readVarInt64(mValue);
        } else if constexpr (std::is_same_v<T, float>) {
            return stream.readFloat(mValue);
        } else if constexpr (std::is_same_v<T, double>) {
            return stream.readDouble(mValue);
        } else if constexpr (std::is_same_v<T, std::string>) {
            return stream.readString(mValue);
        } else {
            static_assert(false, "Invalid ValueTag<T> template");
        }
    };
};

using EndTag    = ValueTag<std::monostate>;
using ByteTag   = ValueTag<std::int8_t>;
using ShortTag  = ValueTag<std::int16_t>;
using IntTag    = ValueTag<std::int32_t>;
using LongTag   = ValueTag<std::int64_t>;
using FloatTag  = ValueTag<float>;
using DoubleTag = ValueTag<double>;
using StringTag = ValueTag<std::string>;

} // namespace sculk::protocol::inline abi_v944
