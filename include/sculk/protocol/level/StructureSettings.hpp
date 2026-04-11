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

struct StructureSettings {
    std::string   mPaletteName{};
    bool          mShouldIgnoreEntities{false};
    bool          mShouldIgnoreBlocks{false};
    bool          mShouldAllowNonTickingPlayerAndTickingAreaChunks{false};
    BlockPos      mSize{};
    BlockPos      mOffset{};
    std::int64_t  mLastEditPlayer{};
    std::uint8_t  mRotation{};
    std::uint8_t  mMirror{};
    std::uint8_t  mAnimationMode{};
    float         mAnimationSeconds{};
    float         mIntegretyValue{};
    std::uint32_t mSeed{};
    Vec3          mRotationPivot{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
