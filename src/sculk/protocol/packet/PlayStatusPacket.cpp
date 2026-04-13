// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/PlayStatusPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PlayStatusPacket::getId() const noexcept { return MinecraftPacketIds::PlayStatus; }

std::string_view PlayStatusPacket::getName() const noexcept { return "PlayStatusPacket"; }

void PlayStatusPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mStatus, &BinaryStream::writeSignedBigEndianInt);
}

Result<> PlayStatusPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readEnum(mStatus, &ReadOnlyBinaryStream::readSignedBigEndianInt);
}

} // namespace sculk::protocol::inline abi_v944
