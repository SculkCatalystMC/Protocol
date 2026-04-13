// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/PositionTrackingDBClientRequestPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PositionTrackingDBClientRequestPacket::getId() const noexcept {
    return MinecraftPacketIds::PositionTrackingDBClientRequest;
}

std::string_view PositionTrackingDBClientRequestPacket::getName() const noexcept {
    return "PositionTrackingDBClientRequestPacket";
}

void PositionTrackingDBClientRequestPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mAction, &BinaryStream::writeByte);
    stream.writeVarInt(mPositionTrackingId);
}

Result<> PositionTrackingDBClientRequestPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mAction, &ReadOnlyBinaryStream::readByte); !status) return status;
    return stream.readVarInt(mPositionTrackingId);
}

} // namespace sculk::protocol::inline abi_v944
