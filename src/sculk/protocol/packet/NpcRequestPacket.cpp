// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/NpcRequestPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds NpcRequestPacket::getId() const noexcept { return MinecraftPacketIds::NpcRequest; }

std::string_view NpcRequestPacket::getName() const noexcept { return "NpcRequestPacket"; }

void NpcRequestPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    stream.writeEnum(mRequestType, &BinaryStream::writeByte);
    stream.writeString(mActions);
    stream.writeByte(mActionIndex);
    stream.writeString(mSceneName);
}

Result<> NpcRequestPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt64(mActorRuntimeId); !status) return status;
    if (auto status = stream.readEnum(mRequestType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readString(mActions); !status) return status;
    if (auto status = stream.readByte(mActionIndex); !status) return status;
    return stream.readString(mSceneName);
}

} // namespace sculk::protocol::inline abi_v944
