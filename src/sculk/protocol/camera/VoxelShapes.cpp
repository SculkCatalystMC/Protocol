// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/level/block/VoxelShapes.hpp"

namespace sculk::protocol::inline abi_v944 {

void SerializableVoxelShape::SerializableCells::write(BinaryStream& stream) const {
    stream.writeByte(mXSize);
    stream.writeByte(mYSize);
    stream.writeByte(mZSize);
    stream.writeArray(mStorage, &BinaryStream::writeByte);
}

Result<> SerializableVoxelShape::SerializableCells::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readByte(mXSize); !status) return status;
    if (auto status = stream.readByte(mYSize); !status) return status;
    if (auto status = stream.readByte(mZSize); !status) return status;
    return stream.readArray(mStorage, &ReadOnlyBinaryStream::readByte);
}

void SerializableVoxelShape::write(BinaryStream& stream) const {
    stream.writeArray(mCells, &SerializableCells::write);
    stream.writeArray(mXCoordinates, &BinaryStream::writeFloat);
    stream.writeArray(mYCoordinates, &BinaryStream::writeFloat);
    stream.writeArray(mZCoordinates, &BinaryStream::writeFloat);
}

Result<> SerializableVoxelShape::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readArray(mCells, &SerializableCells::read); !status) return status;
    if (auto status = stream.readArray(mXCoordinates, &ReadOnlyBinaryStream::readFloat); !status) return status;
    if (auto status = stream.readArray(mYCoordinates, &ReadOnlyBinaryStream::readFloat); !status) return status;
    return stream.readArray(mZCoordinates, &ReadOnlyBinaryStream::readFloat);
}

} // namespace sculk::protocol::inline abi_v944
