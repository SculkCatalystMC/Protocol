// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/packet/IPacket.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"

namespace sculk::protocol::inline abi_v944 {

class RespawnPacket : public IPacket {
public:
    enum class PlayerRespawnState : std::uint8_t {
        SearchingForSpawn  = 0,
        ReadyToSpawn       = 1,
        ClientReadyToSpawn = 2,
    };

public:
    Vec3               mPosition{};
    PlayerRespawnState mState{};
    std::uint64_t      mActorRuntimeId{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
