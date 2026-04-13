// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/LabTablePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds LabTablePacket::getId() const noexcept { return MinecraftPacketIds::LabTable; }

std::string_view LabTablePacket::getName() const noexcept { return "LabTablePacket"; }

void LabTablePacket::write(BinaryStream& stream) const {
    stream.writeEnum(mType, &BinaryStream::writeByte);
    mPosition.write(stream);
    stream.writeEnum(mReaction, &BinaryStream::writeByte);
}

Result<> LabTablePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = mPosition.read(stream); !status) return status;
    return stream.readEnum(mReaction, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944
