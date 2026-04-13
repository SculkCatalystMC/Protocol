// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/SetPlayerInventoryOptionsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds SetPlayerInventoryOptionsPacket::getId() const noexcept {
    return MinecraftPacketIds::SetPlayerInventoryOptions;
}

std::string_view SetPlayerInventoryOptionsPacket::getName() const noexcept { return "SetPlayerInventoryOptionsPacket"; }

void SetPlayerInventoryOptionsPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mLeftInventoryTab, &BinaryStream::writeVarInt);
    stream.writeEnum(mRightInventoryTab, &BinaryStream::writeVarInt);
    stream.writeBool(mFiltering);
    stream.writeEnum(mLayoutInventory, &BinaryStream::writeVarInt);
    stream.writeEnum(mLayoutCraft, &BinaryStream::writeVarInt);
}

Result<> SetPlayerInventoryOptionsPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mLeftInventoryTab, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readEnum(mRightInventoryTab, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readBool(mFiltering); !status) return status;
    if (auto status = stream.readEnum(mLayoutInventory, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    return stream.readEnum(mLayoutCraft, &ReadOnlyBinaryStream::readVarInt);
}

} // namespace sculk::protocol::inline abi_v944
