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
    if (auto status = stream.readString(mContentKey); !status) return status;
    if (mContentKey.size() != 32) {
        return error_utils::makeError("invalid content key length");
    }
    if (auto status = stream.readString(mSubpackName); !status) return status;
    if (auto status = stream.readString(mContentIdentity); !status) return status;
    if (auto status = stream.readBool(mHasScripts); !status) return status;
    if (auto status = stream.readBool(mIsAddonPack); !status) return status;
    if (auto status = stream.readBool(mIsRayTracingCapable); !status) return status;
    return stream.readString(mCDNUrl);
}

} // namespace sculk::protocol::inline abi_v944
