// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/level/block/BlockPos.hpp"
#include "sculk/protocol/packet/IPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

class LabTablePacket : public IPacket {
public:
    enum class Type : std::uint8_t {
        StartCombine  = 0,
        StartReaction = 1,
        Reset         = 2,
    };

    enum class ReactionType : std::uint8_t {
        None               = 0,
        IceBomb            = 1,
        Bleach             = 2,
        ElephantToothpaste = 3,
        Fertilizer         = 4,
        HeatBlock          = 5,
        MagnesiumSalts     = 6,
        MiscFire           = 7,
        MiscExplosion      = 8,
        MiscLava           = 9,
        MiscMystical       = 10,
        MiscSmoke          = 11,
        MiscLargeSmoke     = 12
    };

public:
    Type         mType{};
    BlockPos     mPosition{};
    ReactionType mReaction{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
