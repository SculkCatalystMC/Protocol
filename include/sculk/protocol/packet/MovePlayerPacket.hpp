// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/packet/IPacket.hpp"
#include "sculk/protocol/utility/math/Vec2.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"

namespace sculk::protocol::inline abi_v944 {

class MovePlayerPacket : public IPacket {
public:
    enum class PositionMode : std::uint8_t {
        Normal      = 0,
        Respawn     = 1,
        Teleport    = 2,
        OnlyHeadRot = 3,
    };

public:
    std::uint64_t mActorRuntimeId{};
    Vec3          mPosition{};
    Vec2          mRotation{};
    float         mYHeadRotation{};
    PositionMode  mPositionMode{};
    bool          mOnGround{};
    std::uint64_t mRidingRuntimeId{};
    std::int32_t  mTeleportationCause{};
    std::int32_t  mSourceActorType{};
    std::uint64_t mTick{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
