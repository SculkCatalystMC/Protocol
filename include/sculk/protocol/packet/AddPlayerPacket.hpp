// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/actor/ActorLink.hpp"
#include "sculk/protocol/actor/MetaData.hpp"
#include "sculk/protocol/actor/PropertySyncData.hpp"
#include "sculk/protocol/actor/player/GameType.hpp"
#include "sculk/protocol/actor/player/SerializedAbilitiesData.hpp"
#include "sculk/protocol/actor/player/UUID.hpp"
#include "sculk/protocol/inventory/item/NetworkItemStackDescriptor.hpp"
#include "sculk/protocol/packet/IPacket.hpp"
#include "sculk/protocol/utility/math/Vec2.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"

namespace sculk::protocol::inline abi_v944 {

class AddPlayerPacket : public IPacket {
public:
    std::uint64_t              mActorRuntimeId{};
    std::vector<ActorLink>     mActorLinks{};
    std::string                mName{};
    UUID                       mUuid{};
    std::string                mPlatformOnlineId{};
    Vec3                       mPos{};
    Vec3                       mVelocity{};
    Vec2                       mRot{};
    float                      mYHeadRot{};
    SerializedAbilitiesData    mAbilities{};
    std::string                mDeviceId{};
    std::uint32_t              mBuildPlatform{};
    GameType                   mGameType{};
    NetworkItemStackDescriptor mCarriedItem{};
    MetaData                   mMetaData{};
    PropertySyncData           mSynchedProperties{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
