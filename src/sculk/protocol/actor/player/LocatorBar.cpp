// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/actor/player/LocatorBar.hpp"

namespace sculk::protocol::inline abi_v944 {

void LocatorBarWorldPosition::write(BinaryStream& stream) const {
    mPosition.write(stream);
    stream.writeVarInt(mDimensionType);
}

Result<> LocatorBarWorldPosition::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mPosition.read(stream); !status) return status;
    return stream.readVarInt(mDimensionType);
}

void LocatorBarWaypointHandle::write(BinaryStream& stream) const { mUUID.write(stream); }

Result<> LocatorBarWaypointHandle::read(ReadOnlyBinaryStream& stream) { return mUUID.read(stream); }

void LocatorBarServerWaypointPayload::write(BinaryStream& stream) const {
    stream.writeUnsignedInt(mUpdateFlag);
    stream.writeOptional(mIsVisible, &BinaryStream::writeBool);
    stream.writeOptional(mWorldPosition, &LocatorBarWorldPosition::write);
    stream.writeOptional(mTextureId, &BinaryStream::writeUnsignedInt);
    stream.writeOptional(mColor, &BinaryStream::writeSignedInt);
    stream.writeOptional(mClientPositionAuthority, &BinaryStream::writeBool);
    stream.writeOptional(mActorUniqueId, &BinaryStream::writeVarInt64);
}

Result<> LocatorBarServerWaypointPayload::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedInt(mUpdateFlag); !status) return status;
    if (auto status = stream.readOptional(mIsVisible, &ReadOnlyBinaryStream::readBool); !status) return status;
    if (auto status = stream.readOptional(mWorldPosition, &LocatorBarWorldPosition::read); !status) return status;
    if (auto status = stream.readOptional(mTextureId, &ReadOnlyBinaryStream::readUnsignedInt); !status) return status;
    if (auto status = stream.readOptional(mColor, &ReadOnlyBinaryStream::readSignedInt); !status) return status;
    if (auto status = stream.readOptional(mClientPositionAuthority, &ReadOnlyBinaryStream::readBool); !status)
        return status;
    return stream.readOptional(mActorUniqueId, &ReadOnlyBinaryStream::readVarInt64);
}

void LocatorBarWaypointPayload::write(BinaryStream& stream) const {
    mGroupHandle.write(stream);
    mServerWaypointPayload.write(stream);
    stream.writeEnum(mActionFlag, &BinaryStream::writeByte);
}

Result<> LocatorBarWaypointPayload::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mGroupHandle.read(stream); !status) return status;
    if (auto status = mServerWaypointPayload.read(stream); !status) return status;
    return stream.readEnum(mActionFlag, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944
