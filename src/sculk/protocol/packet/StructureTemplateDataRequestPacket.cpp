// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/StructureTemplateDataRequestPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds StructureTemplateDataRequestPacket::getId() const noexcept {
    return MinecraftPacketIds::StructureTemplateDataRequest;
}

std::string_view StructureTemplateDataRequestPacket::getName() const noexcept {
    return "StructureTemplateDataRequestPacket";
}

void StructureTemplateDataRequestPacket::write(BinaryStream& stream) const {
    stream.writeString(mStructureName);
    mPosition.write(stream);
    mSettings.write(stream);
    stream.writeEnum(mOperationType, &BinaryStream::writeByte);
}

Result<> StructureTemplateDataRequestPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mStructureName); !status) return status;
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = mSettings.read(stream); !status) return status;
    return stream.readEnum(mOperationType, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944
