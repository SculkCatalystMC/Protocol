// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/level/resource/PackInfoData.hpp"

namespace sculk::protocol::inline abi_v944 {

void PackInfoData::write(BinaryStream& stream) const {
    mPackId.write(stream);
    stream.writeString(mPackVersion);
    stream.writeUnsignedInt64(mPackSize);
    stream.writeString(mContentKey);
    stream.writeString(mSubpackName);
    stream.writeString(mContentIdentity);
    stream.writeBool(mHasScripts);
    stream.writeBool(mIsAddonPack);
    stream.writeBool(mIsRayTracingCapable);
    stream.writeString(mCDNUrl);
}

Result<> PackInfoData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mPackId.read(stream); !status) return status;
    if (auto status = stream.readString(mPackVersion); !status) return status;
    if (auto status = stream.readUnsignedInt64(mPackSize); !status) return status;

    std::uint32_t contentKeySize = {};
    if (auto status = stream.readUnsignedVarInt(contentKeySize); !status) return status;

    if (contentKeySize != 0) {
        // Vanilla client only reads the first 32 bytes of the mContentKey. The rest - ignores
        if (auto status = stream.readRawBytes(mContentKey, 32); !status) return status;
        if (auto status = stream.ignoreBytes(static_cast<std::size_t>(contentKeySize) - 32); !status) return status;
    }
    
    if (auto status = stream.readString(mSubpackName); !status) return status;
    if (auto status = stream.readString(mContentIdentity); !status) return status;
    if (auto status = stream.readBool(mHasScripts); !status) return status;
    if (auto status = stream.readBool(mIsAddonPack); !status) return status;
    if (auto status = stream.readBool(mIsRayTracingCapable); !status) return status;
    return stream.readString(mCDNUrl);
}

} // namespace sculk::protocol::inline abi_v944
