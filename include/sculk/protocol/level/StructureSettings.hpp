// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/level/block/BlockPos.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"

namespace sculk::protocol::inline abi_v944 {

class StructureSettings {
public:
    enum class Rotation : std::uint8_t {
        None               = 0,
        Rotate90           = 1,
        Rotate180          = 2,
        Rotate270          = 3,
        Clockwise90        = 1,
        Clockwise180       = 2,
        CounterClockwise90 = 3,
    };

    enum class Mirror : std::uint8_t {
        None = 0,
        X    = 1,
        Z    = 2,
        Xz   = 3,
    };

    enum class AnimationMode : std::uint8_t {
        None   = 0,
        Layers = 1,
        Blocks = 2,
    };

public:
    std::string   mPaletteName{};
    bool          mShouldIgnoreEntities{false};
    bool          mShouldIgnoreBlocks{false};
    bool          mShouldAllowNonTickingPlayerAndTickingAreaChunks{false};
    BlockPos      mSize{};
    BlockPos      mOffset{};
    std::int64_t  mLastEditPlayer{};
    Rotation      mRotation{};
    Mirror        mMirror{};
    AnimationMode mAnimationMode{};
    float         mAnimationSeconds{};
    float         mIntegretyValue{};
    std::uint32_t mSeed{};
    Vec3          mRotationPivot{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
