// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/SimpleEventPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds SimpleEventPacket::getId() const noexcept { return MinecraftPacketIds::SimpleEvent; }

std::string_view SimpleEventPacket::getName() const noexcept { return "SimpleEventPacket"; }

void SimpleEventPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mType, &BinaryStream::writeUnsignedShort);
}

Result<> SimpleEventPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readEnum(mType, &ReadOnlyBinaryStream::readUnsignedShort);
}

} // namespace sculk::protocol::inline abi_v944
