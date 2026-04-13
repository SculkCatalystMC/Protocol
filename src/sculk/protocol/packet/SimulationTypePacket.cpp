// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/SimulationTypePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds SimulationTypePacket::getId() const noexcept { return MinecraftPacketIds::SimulationType; }

std::string_view SimulationTypePacket::getName() const noexcept { return "SimulationTypePacket"; }

void SimulationTypePacket::write(BinaryStream& stream) const { stream.writeEnum(mType, &BinaryStream::writeByte); }

Result<> SimulationTypePacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readEnum(mType, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944
