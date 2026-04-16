// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "Result.hpp"
#include "SwapEndian.hpp"
#include "Variant.hpp"
#include <algorithm>
#include <bitset>
#include <cstddef>
#include <functional>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

namespace sculk::protocol::inline abi_v944 {

class ReadOnlyBinaryStream {
public:
    bool                       mHasOverflowed{};
    std::span<const std::byte> mBufferView{};
    std::size_t                mReadPointer{};

private:
    template <typename T>
    constexpr Result<> read(T* target _SCULK_SL_PARAMETER_DEF) noexcept {
        static_assert(std::is_trivially_copyable_v<T>, "ReadOnlyBinaryStream::read requires trivially copyable type");
        if (mHasOverflowed) {
            return error_utils::makeError("ReadOnlyBinaryStream::read overflowed" _SCULK_SL_PARAM_PASS);
        }
        std::size_t newReadPointer = mReadPointer + sizeof(T);

        if (newReadPointer < mReadPointer || newReadPointer > mBufferView.size()) {
            mHasOverflowed = true;
            return error_utils::makeError("ReadOnlyBinaryStream::read overflowed" _SCULK_SL_PARAM_PASS);
        }

        std::copy_n(
            reinterpret_cast<const char*>(mBufferView.data() + mReadPointer),
            sizeof(T),
            reinterpret_cast<char*>(target)
        );
        mReadPointer = newReadPointer;
        return {};
    }

public:
    [[nodiscard]] constexpr explicit ReadOnlyBinaryStream(std::span<const std::byte> buffer) noexcept
    : mBufferView(buffer) {}

    [[nodiscard]] constexpr explicit ReadOnlyBinaryStream(std::string_view buffer) noexcept
    : mBufferView(reinterpret_cast<const std::byte*>(buffer.data()), buffer.size()) {}

    [[nodiscard]] constexpr std::size_t size() const noexcept { return mBufferView.size(); }

    [[nodiscard]] constexpr std::size_t getPosition() const noexcept { return mReadPointer; }

    constexpr void setPosition(std::size_t value) noexcept {
        if (value > mBufferView.size()) {
            mReadPointer   = mBufferView.size();
            mHasOverflowed = true;
            return;
        }
        mReadPointer = value;
    }

    constexpr void resetPosition() noexcept { setPosition(0); }

    [[nodiscard]] constexpr Result<> ignoreBytes(std::size_t length _SCULK_SL_PARAM_DEFAULT) noexcept {
        std::size_t newPointer = mReadPointer + length;
        if (newPointer < mReadPointer || newPointer > mBufferView.size()) {
            mHasOverflowed = true;
            return error_utils::makeError("ReadOnlyBinaryStream::ignoreBytes overflowed" _SCULK_SL_PARAM_PASS);
        }
        mReadPointer = newPointer;
        return {};
    }

    [[nodiscard]] constexpr std::span<const std::byte> getLeftBufferView() const noexcept {
        return mBufferView.subspan(mReadPointer);
    }

    [[nodiscard]] constexpr bool isOverflowed() const noexcept { return mHasOverflowed; }

    [[nodiscard]] constexpr bool hasDataLeft() const noexcept { return mReadPointer < mBufferView.size(); }

    [[nodiscard]] constexpr std::span<const std::byte> view() const noexcept { return mBufferView; }

    [[nodiscard]] constexpr Result<> readBytes(void* target, std::size_t num _SCULK_SL_PARAM_DEFAULT) noexcept {
        if (mHasOverflowed) {
            return error_utils::makeError("ReadOnlyBinaryStream::readBytes overflowed" _SCULK_SL_PARAM_PASS);
        }
        if (num == 0) {
            return {};
        }

        std::size_t newPointer = mReadPointer + num;

        if (newPointer < mReadPointer || newPointer > mBufferView.size()) {
            mHasOverflowed = true;
            return error_utils::makeError("ReadOnlyBinaryStream::readBytes overflowed" _SCULK_SL_PARAM_PASS);
        }

        std::copy_n(reinterpret_cast<const char*>(mBufferView.data() + mReadPointer), num, static_cast<char*>(target));
        mReadPointer = newPointer;
        return {};
    }

    [[nodiscard]] constexpr Result<> readBool(bool& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        return read(&value _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readByte(std::uint8_t& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        return read(&value _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readSignedChar(std::int8_t& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        return read(&value _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readUnsignedShort(std::uint16_t& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        return read(&value _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readUnsignedInt(std::uint32_t& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        return read(&value _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readUnsignedInt64(std::uint64_t& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        return read(&value _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readDouble(double& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        return read(&value _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readFloat(float& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        return read(&value _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readSignedInt(std::int32_t& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        return read(&value _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readSignedInt64(std::int64_t& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        return read(&value _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readSignedShort(std::int16_t& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        return read(&value _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readUnsignedVarInt(std::uint32_t& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        value = 0;
        std::uint32_t shift{};
        std::uint8_t  byte{};

        do {
            if (shift >= 35) {
                mHasOverflowed = true;
                return error_utils::makeError(
                    "ReadOnlyBinaryStream::readUnsignedVarInt overflowed" _SCULK_SL_PARAM_PASS
                );
            }

            if (mReadPointer >= mBufferView.size()) {
                mHasOverflowed = true;
                return error_utils::makeError(
                    "ReadOnlyBinaryStream::readUnsignedVarInt overflowed" _SCULK_SL_PARAM_PASS
                );
            }

            byte = std::to_integer<std::uint8_t>(mBufferView[mReadPointer++]);
            if (shift == 28 && (byte & 0x80) == 0 && (byte & 0x70) != 0) {
                mHasOverflowed = true;
                return error_utils::makeError(
                    "ReadOnlyBinaryStream::readUnsignedVarInt overflowed" _SCULK_SL_PARAM_PASS
                );
            }
            value |= (byte & 0x7F) << shift;
            shift += 7;

        } while (byte & 0x80);

        return {};
    }

    [[nodiscard]] constexpr Result<> readUnsignedVarInt64(std::uint64_t& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        value = 0;
        std::uint32_t shift{};
        std::uint8_t  byte{};

        do {
            if (shift >= 70) {
                mHasOverflowed = true;
                return error_utils::makeError(
                    "ReadOnlyBinaryStream::readUnsignedVarInt64 overflowed" _SCULK_SL_PARAM_PASS
                );
            }

            if (mReadPointer >= mBufferView.size()) {
                mHasOverflowed = true;
                return error_utils::makeError(
                    "ReadOnlyBinaryStream::readUnsignedVarInt64 overflowed" _SCULK_SL_PARAM_PASS
                );
            }

            byte = std::to_integer<std::uint8_t>(mBufferView[mReadPointer++]);
            if (shift == 63 && (byte & 0x80) == 0 && (byte & 0x7E) != 0) {
                mHasOverflowed = true;
                return error_utils::makeError(
                    "ReadOnlyBinaryStream::readUnsignedVarInt64 overflowed" _SCULK_SL_PARAM_PASS
                );
            }
            value |= static_cast<std::uint64_t>(byte & 0x7F) << shift;
            shift += 7;

        } while (byte & 0x80);

        return {};
    }

    [[nodiscard]] constexpr Result<> readVarInt(std::int32_t& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        std::uint32_t temp{};
        if (!readUnsignedVarInt(temp _SCULK_SL_PARAM_PASS)) {
            return error_utils::makeError("ReadOnlyBinaryStream::readVarInt failed" _SCULK_SL_PARAM_PASS);
        }
        value = (temp & 1) ? ~(temp >> 1) : (temp >> 1);
        return {};
    }

    [[nodiscard]] constexpr Result<> readVarInt64(std::int64_t& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        std::uint64_t temp{};
        if (!readUnsignedVarInt64(temp _SCULK_SL_PARAM_PASS)) {
            return error_utils::makeError("ReadOnlyBinaryStream::readVarInt64 failed" _SCULK_SL_PARAM_PASS);
        }
        value = (temp & 1) ? ~(temp >> 1) : (temp >> 1);
        return {};
    }

    [[nodiscard]] constexpr Result<> readSignedBigEndianInt(std::int32_t& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        if (read(&value _SCULK_SL_PARAM_PASS)) {
            value = swapEndian(value);
            return {};
        }
        return error_utils::makeError("ReadOnlyBinaryStream::readSignedBigEndianInt failed" _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readString(std::string& outString _SCULK_SL_PARAM_DEFAULT) noexcept {
        std::uint32_t length{};
        if (!readUnsignedVarInt(length _SCULK_SL_PARAM_PASS)) {
            outString.clear();
            return error_utils::makeError("ReadOnlyBinaryStream::readString failed" _SCULK_SL_PARAM_PASS);
        }
        return readRawBytes(outString, static_cast<std::size_t>(length) _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readLongString(std::string& value _SCULK_SL_PARAM_DEFAULT) noexcept {
        std::int32_t length{};
        if (!readSignedInt(length _SCULK_SL_PARAM_PASS)) {
            return error_utils::makeError("ReadOnlyBinaryStream::readLongString overflowed" _SCULK_SL_PARAM_PASS);
        }
        if (length < 0) {
            return error_utils::makeError(
                "ReadOnlyBinaryStream::readLongString failed: negative length" _SCULK_SL_PARAM_PASS
            );
        }
        return readRawBytes(value, static_cast<std::size_t>(length) _SCULK_SL_PARAM_PASS);
    }

    [[nodiscard]] constexpr Result<> readRawBytes(std::string& rawBuffer, std::size_t length _SCULK_SL_PARAM_DEFAULT) {
        if (length == 0) {
            rawBuffer.clear();
            return {};
        }

        if (mReadPointer > mBufferView.size()) {
            mHasOverflowed = true;
            rawBuffer.clear();
            return error_utils::makeError("ReadOnlyBinaryStream::readRawBytes overflowed" _SCULK_SL_PARAM_PASS);
        }
        std::size_t remaining = mBufferView.size() - mReadPointer;
        if (length > remaining) {
            mHasOverflowed = true;
            rawBuffer.clear();
            return error_utils::makeError("ReadOnlyBinaryStream::readRawBytes overflowed" _SCULK_SL_PARAM_PASS);
        }

        rawBuffer.assign(reinterpret_cast<const char*>(mBufferView.data() + mReadPointer), length);
        mReadPointer += length;
        return {};
    }

    template <typename T, typename F>
    [[nodiscard]] constexpr Result<> readArray(std::vector<T>& outVector, F&& func _SCULK_SL_PARAM_DEFAULT) {
        std::uint32_t length{};
        if (!readUnsignedVarInt(length _SCULK_SL_PARAM_PASS)) {
            return error_utils::makeError("ReadOnlyBinaryStream::readArray overflowed" _SCULK_SL_PARAM_PASS);
        }

        outVector.resize(length);
        for (auto& element : outVector) {
            if constexpr (std::is_invocable_r_v<Result<>, F, ReadOnlyBinaryStream&, T&>) {
                if (auto status = std::invoke(std::forward<F>(func), *this, element); !status) {
                    return status;
                }
            } else if constexpr (std::is_invocable_r_v<Result<>, F, ReadOnlyBinaryStream&, T & _SCULK_SL_PARAMETER>) {
                if (auto status = std::invoke(std::forward<F>(func), *this, element _SCULK_SL_PARAM_PASS); !status) {
                    return status;
                }
            } else if constexpr (std::is_invocable_r_v<Result<>, F, T&, ReadOnlyBinaryStream&>) {
                if (auto status = std::invoke(std::forward<F>(func), element, *this); !status) {
                    return status;
                }
            } else if constexpr (std::is_invocable_r_v<Result<>, F, T&>) {
                if (auto status = std::invoke(std::forward<F>(func), element); !status) {
                    return status;
                }
            } else {
                static_assert(false, "invalid read array function");
            }
        }
        return {};
    }

    template <typename T, typename F>
    constexpr Result<> readOptional(std::optional<T>& outOpt, F&& func _SCULK_SL_PARAM_DEFAULT) noexcept {
        outOpt.reset();
        bool hasValue{};
        if (!readBool(hasValue _SCULK_SL_PARAM_PASS)) {
            return error_utils::makeError("ReadOnlyBinaryStream::readOptional overflowed" _SCULK_SL_PARAM_PASS);
        }
        if (hasValue) {
            outOpt.emplace();
            if constexpr (std::is_invocable_r_v<Result<>, F, ReadOnlyBinaryStream&, T & _SCULK_SL_PARAMETER>) {
                return std::invoke(std::forward<F>(func), *this, *outOpt _SCULK_SL_PARAM_PASS);
            } else if constexpr (std::is_invocable_r_v<Result<>, F, ReadOnlyBinaryStream&, T&>) {
                return std::invoke(std::forward<F>(func), *this, *outOpt);
            } else if constexpr (std::is_invocable_r_v<Result<>, F, T&, ReadOnlyBinaryStream&>) {
                return std::invoke(std::forward<F>(func), *outOpt, *this);
            } else if constexpr (std::is_invocable_r_v<Result<>, F, T&>) {
                return std::invoke(std::forward<F>(func), *outOpt);
            } else {
                static_assert(false, "invalid read optional function");
            }
        }
        return {};
    }

    template <std::size_t N>
    [[nodiscard]] constexpr Result<> readBitset(std::bitset<N>& outBitset _SCULK_SL_PARAM_DEFAULT) noexcept {
        auto bitLength8 = [](std::uint8_t value) constexpr -> std::size_t {
            std::size_t length{};
            while (value != 0) {
                value >>= 1;
                length++;
            }
            return length;
        };

        outBitset.reset();
        std::size_t chunkCount{};
        bool        seenSetBit{};
        for (std::size_t bitIndex = 0; bitIndex < outBitset.size(); bitIndex += 7) {
            std::uint8_t byte{};
            if (!readByte(byte _SCULK_SL_PARAM_PASS)) {
                return error_utils::makeError("ReadOnlyBinaryStream::readBitset overflowed" _SCULK_SL_PARAM_PASS);
            }
            chunkCount++;

            if (bitIndex + bitLength8(byte) > outBitset.size()) {
                mHasOverflowed = true;
                return error_utils::makeError("ReadOnlyBinaryStream::readBitset overflowed" _SCULK_SL_PARAM_PASS);
            }

            const std::uint8_t payload = byte & 0x7Fu;
            if (payload != 0) {
                seenSetBit = true;
            }

            for (int i = 0; i < 7; i++) {
                const std::size_t currentBit = bitIndex + static_cast<std::size_t>(i);
                if (currentBit < outBitset.size()) {
                    outBitset.set(currentBit, (byte & static_cast<std::uint8_t>(1u << i)) != 0);
                }
            }

            if ((byte & 0x80u) == 0) {
                if (!seenSetBit && chunkCount != 1) {
                    mHasOverflowed = true;
                    return error_utils::makeError("ReadOnlyBinaryStream::readBitset overflowed" _SCULK_SL_PARAM_PASS);
                }
                if (seenSetBit && payload == 0) {
                    mHasOverflowed = true;
                    return error_utils::makeError("ReadOnlyBinaryStream::readBitset overflowed" _SCULK_SL_PARAM_PASS);
                }
                return {};
            }
        }

        mHasOverflowed = true;
        return error_utils::makeError("ReadOnlyBinaryStream::readBitset overflowed" _SCULK_SL_PARAM_PASS);
    }

    template <typename T, typename F>
        requires std::is_enum_v<T>
    [[nodiscard]] constexpr Result<> readEnum(T& outValue, F&& func _SCULK_SL_PARAM_DEFAULT) noexcept {
        using UT = std::underlying_type_t<T>;
        if constexpr (std::is_invocable_r_v<Result<>, F, ReadOnlyBinaryStream&, UT & _SCULK_SL_PARAMETER>) {
            UT value{};
            if (!std::invoke(std::forward<F>(func), *this, value _SCULK_SL_PARAM_PASS)) {
                return error_utils::makeError("ReadOnlyBinaryStream::readEnum overflowed" _SCULK_SL_PARAM_PASS);
            }
            outValue = static_cast<T>(value);
            return {};
        } else {
            static_assert(false, "invalid read enum function, maybe underlying type mismatch?");
        }
    }

    template <typename U, typename T, typename F>
    [[nodiscard]] constexpr Result<> readVariantIndex(T& var, F&& func _SCULK_SL_PARAM_DEFAULT) noexcept {
        U index{};
        if (!std::invoke(std::forward<F>(func), *this, index _SCULK_SL_PARAM_PASS)) {
            return error_utils::makeError("ReadOnlyBinaryStream::readVariantIndex overflowed" _SCULK_SL_PARAM_PASS);
        }
        return emplace_variant(var, index _SCULK_SL_PARAM_PASS);
    }
};

} // namespace sculk::protocol::inline abi_v944
