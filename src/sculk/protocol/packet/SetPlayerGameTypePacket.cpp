// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/SetPlayerGameTypePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds SetPlayerGameTypePacket::getId() const noexcept { return MinecraftPacketIds::SetPlayerGameType; }

std::string_view SetPlayerGameTypePacket::getName() const noexcept { return "SetPlayerGameTypePacket"; }

void SetPlayerGameTypePacket::write(BinaryStream& stream) const {
    stream.writeEnum(mGameType, &BinaryStream::writeVarInt);
}

Result<> SetPlayerGameTypePacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readEnum(mGameType, &ReadOnlyBinaryStream::readVarInt);
}

} // namespace sculk::protocol::inline abi_v944
