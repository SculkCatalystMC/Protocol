// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/actor/ActorEvent.hpp"
#include "sculk/protocol/actor/ActorLink.hpp"
#include "sculk/protocol/actor/MetaData.hpp"
#include "sculk/protocol/actor/PropertySyncData.hpp"
#include "sculk/protocol/actor/SyncedAttribute.hpp"
#include "sculk/protocol/packet/IPacket.hpp"
#include "sculk/protocol/utility/math/Vec2.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"

namespace sculk::protocol::inline abi_v944 {

class AddActorPacket : public IPacket {
public:
    std::uint64_t                mActorRuntimeId{};
    std::int64_t                 mActorUniqueId{};
    std::string                  mIdentifier{};
    std::vector<ActorLink>       mActorLinks{};
    Vec3                         mPosition{};
    Vec3                         mVelocity{};
    Vec2                         mRotation{};
    float                        mYHeadRotation{};
    float                        mYBodyRotation{};
    MetaData                     mMetaData{};
    std::vector<SyncedAttribute> mAttributes{};
    PropertySyncData             mSynchedProperties{};

public:
    MinecraftPacketIds getId() const noexcept override;

    std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
