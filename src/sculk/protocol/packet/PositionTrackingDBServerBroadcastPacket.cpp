// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/PositionTrackingDBServerBroadcastPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PositionTrackingDBServerBroadcastPacket::getId() const noexcept {
    return MinecraftPacketIds::PositionTrackingDBServerBroadcast;
}

std::string_view PositionTrackingDBServerBroadcastPacket::getName() const noexcept {
    return "PositionTrackingDBServerBroadcastPacket";
}

void PositionTrackingDBServerBroadcastPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mAction, &BinaryStream::writeByte);
    stream.writeVarInt(mPositionTrackingId);
    mPositionTrackingData.write(stream);
}

Result<> PositionTrackingDBServerBroadcastPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mAction, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readVarInt(mPositionTrackingId); !status) return status;
    return mPositionTrackingData.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
