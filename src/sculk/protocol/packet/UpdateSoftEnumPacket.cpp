// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/UpdateSoftEnumPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds UpdateSoftEnumPacket::getId() const noexcept { return MinecraftPacketIds::UpdateSoftEnum; }

std::string_view UpdateSoftEnumPacket::getName() const noexcept { return "UpdateSoftEnumPacket"; }

void UpdateSoftEnumPacket::write(BinaryStream& stream) const {
    stream.writeString(mEnumName);
    stream.writeArray(mEnumValues, &BinaryStream::writeString);
    stream.writeEnum(mUpdateType, &BinaryStream::writeByte);
}

Result<> UpdateSoftEnumPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mEnumName); !status) return status;
    if (auto status = stream.readArray(mEnumValues, &ReadOnlyBinaryStream::readString); !status) return status;
    return stream.readEnum(mUpdateType, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944
