// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/UpdatePlayerGameTypePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds UpdatePlayerGameTypePacket::getId() const noexcept {
    return MinecraftPacketIds::UpdatePlayerGameType;
}

std::string_view UpdatePlayerGameTypePacket::getName() const noexcept { return "UpdatePlayerGameTypePacket"; }

void UpdatePlayerGameTypePacket::write(BinaryStream& stream) const {
    stream.writeEnum(mGameType, &BinaryStream::writeVarInt);
    stream.writeVarInt64(mPlayerUniqueId);
    stream.writeUnsignedVarInt64(mTick);
}

Result<> UpdatePlayerGameTypePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mGameType, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readVarInt64(mPlayerUniqueId); !status) return status;
    return stream.readUnsignedVarInt64(mTick);
}

} // namespace sculk::protocol::inline abi_v944
