// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/RespawnPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds RespawnPacket::getId() const noexcept { return MinecraftPacketIds::Respawn; }

std::string_view RespawnPacket::getName() const noexcept { return "RespawnPacket"; }

void RespawnPacket::write(BinaryStream& stream) const {
    mPosition.write(stream);
    stream.writeEnum(mState, &BinaryStream::writeByte);
    stream.writeUnsignedVarInt64(mActorRuntimeId);
}

Result<> RespawnPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = stream.readEnum(mState, &ReadOnlyBinaryStream::readByte); !status) return status;
    return stream.readUnsignedVarInt64(mActorRuntimeId);
}

} // namespace sculk::protocol::inline abi_v944
