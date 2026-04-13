// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/HurtArmorPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds HurtArmorPacket::getId() const noexcept { return MinecraftPacketIds::HurtArmor; }

std::string_view HurtArmorPacket::getName() const noexcept { return "HurtArmorPacket"; }

void HurtArmorPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mCause, &BinaryStream::writeVarInt);
    stream.writeVarInt(mDamage);
    stream.writeUnsignedVarInt64(mArmorSlots);
}

Result<> HurtArmorPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mCause, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readVarInt(mDamage); !status) return status;
    return stream.readUnsignedVarInt64(mArmorSlots);
}

} // namespace sculk::protocol::inline abi_v944
