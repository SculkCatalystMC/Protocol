// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/SetSpawnPositionPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds SetSpawnPositionPacket::getId() const noexcept { return MinecraftPacketIds::SetSpawnPosition; }

std::string_view SetSpawnPositionPacket::getName() const noexcept { return "SetSpawnPositionPacket"; }

void SetSpawnPositionPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mSpawnPositionType, &BinaryStream::writeVarInt);
    mBlockPosition.write(stream);
    stream.writeVarInt(mDimensionType);
    mSpawnBlockPos.write(stream);
}

Result<> SetSpawnPositionPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mSpawnPositionType, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = mBlockPosition.read(stream); !status) return status;
    if (auto status = stream.readVarInt(mDimensionType); !status) return status;
    return mSpawnBlockPos.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
