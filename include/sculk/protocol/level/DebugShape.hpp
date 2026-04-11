// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <variant>

namespace sculk::protocol::inline abi_v944 {

enum class DebugShapeType : std::uint8_t {
    Line          = 0,
    Box           = 1,
    Sphere        = 2,
    Circle        = 3,
    Text          = 4,
    Arrow         = 5,
    NumShapeTypes = 6,
};

struct DebugArrow {
    std::optional<Vec3>         mArrowEndLocation{};
    std::optional<float>        mArrowHeadLength{};
    std::optional<float>        mArrowHeadRadius{};
    std::optional<std::uint8_t> mArrowSegments{};
};

struct DebugBox {
    Vec3 mBoxBound{};
};

struct DebugSegments {
    std::uint8_t mSegments{};
};

struct DebugLine {
    Vec3 mLineEndLocation{};
};

struct DebugText {
    std::string mText{};
};

using DebugShapeVariant = std::variant<std::monostate, DebugArrow, DebugText, DebugBox, DebugLine, DebugSegments>;

struct DebugShape {
    std::uint64_t                 mNetworkId{};
    std::optional<Vec3>           mLocation{};
    std::optional<DebugShapeType> mType{};
    std::optional<std::int32_t>   mDimensionId{};
    std::optional<float>          mScale{};
    std::optional<Vec3>           mRotation{};
    std::optional<float>          mTotalTimeLeft{};
    std::optional<std::int32_t>   mColor{};
    std::optional<std::uint64_t>  mAttachedToEntityId{};
    DebugShapeVariant             mShape{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
