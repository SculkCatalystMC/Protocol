// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/level/StructureSettings.hpp"

namespace sculk::protocol::inline abi_v944 {

void StructureSettings::write(BinaryStream& stream) const {
    stream.writeString(mPaletteName);
    stream.writeBool(mShouldIgnoreEntities);
    stream.writeBool(mShouldIgnoreBlocks);
    stream.writeBool(mShouldAllowNonTickingPlayerAndTickingAreaChunks);
    mSize.write(stream);
    mOffset.write(stream);
    stream.writeVarInt64(mLastEditPlayer);
    stream.writeEnum(mRotation, &BinaryStream::writeByte);
    stream.writeEnum(mMirror, &BinaryStream::writeByte);
    stream.writeEnum(mAnimationMode, &BinaryStream::writeByte);
    stream.writeFloat(mAnimationSeconds);
    stream.writeFloat(mIntegretyValue);
    stream.writeUnsignedInt(mSeed);
    mRotationPivot.write(stream);
}

Result<> StructureSettings::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mPaletteName); !status) return status;
    if (auto status = stream.readBool(mShouldIgnoreEntities); !status) return status;
    if (auto status = stream.readBool(mShouldIgnoreBlocks); !status) return status;
    if (auto status = stream.readBool(mShouldAllowNonTickingPlayerAndTickingAreaChunks); !status) return status;
    if (auto status = mSize.read(stream); !status) return status;
    if (auto status = mOffset.read(stream); !status) return status;
    if (auto status = stream.readVarInt64(mLastEditPlayer); !status) return status;
    if (auto status = stream.readEnum(mRotation, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readEnum(mMirror, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readEnum(mAnimationMode, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readFloat(mAnimationSeconds); !status) return status;
    if (auto status = stream.readFloat(mIntegretyValue); !status) return status;
    if (auto status = stream.readUnsignedInt(mSeed); !status) return status;
    return mRotationPivot.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
