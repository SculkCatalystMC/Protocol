// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/ServerboundLoadingScreenPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ServerboundLoadingScreenPacket::getId() const noexcept {
    return MinecraftPacketIds::ServerboundLoadingScreen;
}

std::string_view ServerboundLoadingScreenPacket::getName() const noexcept { return "ServerboundLoadingScreenPacket"; }

void ServerboundLoadingScreenPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mType, &BinaryStream::writeVarInt);
    stream.writeOptional(mLoadingScreenId, &BinaryStream::writeUnsignedInt);
}

Result<> ServerboundLoadingScreenPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mType, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    return stream.readOptional(mLoadingScreenId, &ReadOnlyBinaryStream::readUnsignedInt);
}

} // namespace sculk::protocol::inline abi_v944
