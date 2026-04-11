// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/level/chunk/SubChunkBlockChangeInfo.hpp"

namespace sculk::protocol::inline abi_v944 {

void SubChunkBlockChangeInfo::write(BinaryStream& stream) const {
    mPosition.write(stream);
    stream.writeUnsignedVarInt(mRuntimeId);
    stream.writeUnsignedVarInt(mFlags);
    stream.writeUnsignedVarInt64(mSyncEntity);
    stream.writeUnsignedVarInt(mSyncMessage);
}

Result<> SubChunkBlockChangeInfo::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mRuntimeId); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mFlags); !status) return status;
    if (auto status = stream.readUnsignedVarInt64(mSyncEntity); !status) return status;
    return stream.readUnsignedVarInt(mSyncMessage);
}

} // namespace sculk::protocol::inline abi_v944
