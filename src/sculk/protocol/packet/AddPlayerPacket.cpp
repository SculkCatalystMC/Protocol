// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/AddPlayerPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds AddPlayerPacket::getId() const noexcept { return MinecraftPacketIds::AddPlayer; }

std::string_view AddPlayerPacket::getName() const noexcept { return "AddPlayerPacket"; }

void AddPlayerPacket::write(BinaryStream& stream) const {
    mUuid.write(stream);
    stream.writeString(mName);
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    stream.writeString(mPlatformOnlineId);
    mPos.write(stream);
    mVelocity.write(stream);
    mRot.write(stream);
    stream.writeFloat(mYHeadRot);
    mCarriedItem.write(stream);
    stream.writeEnum(mGameType, &BinaryStream::writeVarInt);
    mMetaData.write(stream);
    mSynchedProperties.write(stream);
    mAbilities.write(stream);
    stream.writeArray(mActorLinks, &ActorLink::write);
    stream.writeString(mDeviceId);
    stream.writeUnsignedInt(mBuildPlatform);
}

Result<> AddPlayerPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mUuid.read(stream); !status) return status;
    if (auto status = stream.readString(mName); !status) return status;
    if (auto status = stream.readUnsignedVarInt64(mActorRuntimeId); !status) return status;
    if (auto status = stream.readString(mPlatformOnlineId); !status) return status;
    if (auto status = mPos.read(stream); !status) return status;
    if (auto status = mVelocity.read(stream); !status) return status;
    if (auto status = mRot.read(stream); !status) return status;
    if (auto status = stream.readFloat(mYHeadRot); !status) return status;
    if (auto status = mCarriedItem.read(stream); !status) return status;
    if (auto status = stream.readEnum(mGameType, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = mMetaData.read(stream); !status) return status;
    if (auto status = mSynchedProperties.read(stream); !status) return status;
    if (auto status = mAbilities.read(stream); !status) return status;
    if (auto status = stream.readArray(mActorLinks, &ActorLink::read); !status) return status;
    if (auto status = stream.readString(mDeviceId); !status) return status;
    return stream.readUnsignedInt(mBuildPlatform);
}

} // namespace sculk::protocol::inline abi_v944
