// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/CodeBuilderSourcePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds CodeBuilderSourcePacket::getId() const noexcept { return MinecraftPacketIds::CodeBuilderSource; }

std::string_view CodeBuilderSourcePacket::getName() const noexcept { return "CodeBuilderSourcePacket"; }

void CodeBuilderSourcePacket::write(BinaryStream& stream) const {
    stream.writeEnum(mOperation, &BinaryStream::writeByte);
    stream.writeEnum(mCategory, &BinaryStream::writeByte);
    stream.writeEnum(mCodeStatus, &BinaryStream::writeByte);
}

Result<> CodeBuilderSourcePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mOperation, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readEnum(mCategory, &ReadOnlyBinaryStream::readByte); !status) return status;
    return stream.readEnum(mCodeStatus, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944
