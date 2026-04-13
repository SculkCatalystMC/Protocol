// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/ResourcePackDataInfoPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ResourcePackDataInfoPacket::getId() const noexcept {
    return MinecraftPacketIds::ResourcePackDataInfo;
}

std::string_view ResourcePackDataInfoPacket::getName() const noexcept { return "ResourcePackDataInfoPacket"; }

void ResourcePackDataInfoPacket::write(BinaryStream& stream) const {
    stream.writeString(mResourceName);
    stream.writeUnsignedInt(mChunkSize);
    stream.writeUnsignedInt(mChunkIndex);
    stream.writeUnsignedInt64(mFileSize);
    stream.writeString(mFileHash);
    stream.writeBool(mIsPremiumPack);
    stream.writeEnum(mPackType, &BinaryStream::writeByte);
}

Result<> ResourcePackDataInfoPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mResourceName); !status) return status;
    if (auto status = stream.readUnsignedInt(mChunkSize); !status) return status;
    if (auto status = stream.readUnsignedInt(mChunkIndex); !status) return status;
    if (auto status = stream.readUnsignedInt64(mFileSize); !status) return status;
    if (auto status = stream.readString(mFileHash); !status) return status;
    if (auto status = stream.readBool(mIsPremiumPack); !status) return status;
    return stream.readEnum(mPackType, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944
