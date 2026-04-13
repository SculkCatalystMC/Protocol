// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/PlayerActionPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PlayerActionPacket::getId() const noexcept { return MinecraftPacketIds::PlayerAction; }

std::string_view PlayerActionPacket::getName() const noexcept { return "PlayerActionPacket"; }

void PlayerActionPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mPlayerRuntimeId);
    stream.writeEnum(mAction, &BinaryStream::writeVarInt);
    mBlockPosition.write(stream);
    mResultPosition.write(stream);
    stream.writeVarInt(mFace);
}

Result<> PlayerActionPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt64(mPlayerRuntimeId); !status) return status;
    if (auto status = stream.readEnum(mAction, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = mBlockPosition.read(stream); !status) return status;
    if (auto status = mResultPosition.read(stream); !status) return status;
    return stream.readVarInt(mFace);
}

} // namespace sculk::protocol::inline abi_v944
