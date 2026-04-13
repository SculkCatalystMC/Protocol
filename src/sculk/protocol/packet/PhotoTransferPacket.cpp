// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/PhotoTransferPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PhotoTransferPacket::getId() const noexcept { return MinecraftPacketIds::PhotoTransfer; }

std::string_view PhotoTransferPacket::getName() const noexcept { return "PhotoTransferPacket"; }

void PhotoTransferPacket::write(BinaryStream& stream) const {
    stream.writeString(mPhotoName);
    stream.writeString(mPhotoData);
    stream.writeString(mBookId);
    stream.writeEnum(mType, &BinaryStream::writeByte);
    stream.writeEnum(mSourceType, &BinaryStream::writeByte);
    stream.writeSignedInt64(mOwnerId);
    stream.writeString(mNewPhotoName);
}

Result<> PhotoTransferPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mPhotoName); !status) return status;
    if (auto status = stream.readString(mPhotoData); !status) return status;
    if (auto status = stream.readString(mBookId); !status) return status;
    if (auto status = stream.readEnum(mType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readEnum(mSourceType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readSignedInt64(mOwnerId); !status) return status;
    return stream.readString(mNewPhotoName);
}

} // namespace sculk::protocol::inline abi_v944
