// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/MobEffectPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds MobEffectPacket::getId() const noexcept { return MinecraftPacketIds::MobEffect; }

std::string_view MobEffectPacket::getName() const noexcept { return "MobEffectPacket"; }

void MobEffectPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    stream.writeEnum(mEventId, &BinaryStream::writeByte);
    stream.writeVarInt(mEffectId);
    stream.writeVarInt(mEffectAmplifier);
    stream.writeBool(mShowParticles);
    stream.writeVarInt(mEffectDurationTicks);
    stream.writeUnsignedVarInt64(mTick);
    stream.writeBool(mAmbient);
}

Result<> MobEffectPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt64(mActorRuntimeId); !status) return status;
    if (auto status = stream.readEnum(mEventId, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readVarInt(mEffectId); !status) return status;
    if (auto status = stream.readVarInt(mEffectAmplifier); !status) return status;
    if (auto status = stream.readBool(mShowParticles); !status) return status;
    if (auto status = stream.readVarInt(mEffectDurationTicks); !status) return status;
    if (auto status = stream.readUnsignedVarInt64(mTick); !status) return status;
    return stream.readBool(mAmbient);
}

} // namespace sculk::protocol::inline abi_v944
