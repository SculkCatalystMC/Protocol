// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/StructureTemplateDataResponsePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds StructureTemplateDataResponsePacket::getId() const noexcept {
    return MinecraftPacketIds::StructureTemplateDataResponse;
}

std::string_view StructureTemplateDataResponsePacket::getName() const noexcept {
    return "StructureTemplateDataResponsePacket";
}

void StructureTemplateDataResponsePacket::write(BinaryStream& stream) const {
    stream.writeString(mStructureName);
    stream.writeBool(mSuccess);
    if (mSuccess) {
        mNbt.write(stream);
    }
    stream.writeEnum(mResponseType, &BinaryStream::writeByte);
}

Result<> StructureTemplateDataResponsePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mStructureName); !status) return status;
    if (auto status = stream.readBool(mSuccess); !status) return status;
    if (mSuccess) {
        if (auto status = mNbt.read(stream); !status) return status;
    }
    return stream.readEnum(mResponseType, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944
