// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/StartGamePacket.hpp"
#include "sculk/protocol/nbt/TagType.hpp"
#include "sculk/protocol/nbt/TagVariant.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds StartGamePacket::getId() const noexcept { return MinecraftPacketIds::StartGame; }

std::string_view StartGamePacket::getName() const noexcept { return "StartGamePacket"; }

void StartGamePacket::write(BinaryStream& stream) const {
    stream.writeVarInt64(mActorUniqueId);
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    stream.writeEnum(mGameType, &BinaryStream::writeVarInt);
    mPosition.write(stream);
    mRotation.write(stream);
    mLevelSettings.write(stream);
    stream.writeString(mLevelId);
    stream.writeString(mLevelName);
    stream.writeString(mTemplateContentIdentity);
    stream.writeBool(mIsTrial);
    mMovementSettings.write(stream);
    stream.writeUnsignedInt64(mCurrentTime);
    stream.writeVarInt(mEnchantmentSeed);
    stream.writeArray(mBlockProperties, &BlockProperty::write);
    stream.writeString(mMultiPlayerCorrelationId);
    stream.writeBool(mEnableItemStackNetManager);
    stream.writeString(mServerVersion);
    mPlayerPropertyData.write(stream);
    stream.writeUnsignedInt64(mServerBlockCheckSum);
    mWorldTemplateId.write(stream);
    stream.writeBool(mClientGen);
    stream.writeBool(mEnableHashId);
    stream.writeBool(mServerAuthSound);
    stream.writeOptional(mServerConfigurationJoinInfo, &ServerConfigurationJoinInfo::write);
    mServerTelemetryData.write(stream);
}

Result<> StartGamePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt64(mActorUniqueId); !status) return status;
    if (auto status = stream.readUnsignedVarInt64(mActorRuntimeId); !status) return status;
    if (auto status = stream.readEnum(mGameType, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = mRotation.read(stream); !status) return status;
    if (auto status = mLevelSettings.read(stream); !status) return status;
    if (auto status = stream.readString(mLevelId); !status) return status;
    if (auto status = stream.readString(mLevelName); !status) return status;
    if (auto status = stream.readString(mTemplateContentIdentity); !status) return status;
    if (auto status = stream.readBool(mIsTrial); !status) return status;
    if (auto status = mMovementSettings.read(stream); !status) return status;
    if (auto status = stream.readUnsignedInt64(mCurrentTime); !status) return status;
    if (auto status = stream.readVarInt(mEnchantmentSeed); !status) return status;
    if (auto status = stream.readArray(mBlockProperties, &BlockProperty::read); !status) return status;
    if (auto status = stream.readString(mMultiPlayerCorrelationId); !status) return status;
    if (auto status = stream.readBool(mEnableItemStackNetManager); !status) return status;
    if (auto status = stream.readString(mServerVersion); !status) return status;
    if (auto status = mPlayerPropertyData.read(stream); !status) return status;
    if (auto status = stream.readUnsignedInt64(mServerBlockCheckSum); !status) return status;
    if (auto status = mWorldTemplateId.read(stream); !status) return status;
    if (auto status = stream.readBool(mClientGen); !status) return status;
    if (auto status = stream.readBool(mEnableHashId); !status) return status;
    if (auto status = stream.readBool(mServerAuthSound); !status) return status;
    if (auto status = stream.readOptional(mServerConfigurationJoinInfo, &ServerConfigurationJoinInfo::read); !status)
        return status;
    return mServerTelemetryData.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
