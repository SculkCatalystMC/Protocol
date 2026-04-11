// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/level/DebugShape.hpp"

namespace sculk::protocol::inline abi_v944 {

void DebugShape::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mNetworkId);
    stream.writeOptional(mType, [](BinaryStream& stream, DebugShapeType value) {
        stream.writeEnum(value, &BinaryStream::writeByte);
    });
    stream.writeOptional(mLocation, &Vec3::write);
    stream.writeOptional(mScale, &BinaryStream::writeFloat);
    stream.writeOptional(mRotation, &Vec3::write);
    stream.writeOptional(mTotalTimeLeft, &BinaryStream::writeFloat);
    stream.writeOptional(mColor, &BinaryStream::writeSignedInt);
    stream.writeOptional(mDimensionId, &BinaryStream::writeVarInt);
    stream.writeOptional(mAttachedToEntityId, &BinaryStream::writeUnsignedVarInt64);
    stream.writeVariantIndex<std::uint32_t>(mShape, &BinaryStream::writeUnsignedVarInt);
    std::visit(
        Overload{
            [&](const DebugLine& line) { line.mLineEndLocation.write(stream); },
            [&](const DebugBox& box) { box.mBoxBound.write(stream); },
            [&](const DebugSegments& segments) { stream.writeByte(segments.mSegments); },
            [&](const DebugText& text) { stream.writeString(text.mText); },
            [&](const DebugArrow& arrow) {
                stream.writeOptional(arrow.mArrowEndLocation, &Vec3::write);
                stream.writeOptional(arrow.mArrowHeadLength, &BinaryStream::writeFloat);
                stream.writeOptional(arrow.mArrowHeadRadius, &BinaryStream::writeFloat);
                stream.writeOptional(arrow.mArrowSegments, &BinaryStream::writeByte);
            },
            [&](const auto&) {}
        },
        mShape
    );
}

Result<> DebugShape::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt64(mNetworkId); !status) return status;
    if (auto status = stream.readOptional(
            mType,
            [](ReadOnlyBinaryStream& stream, DebugShapeType& value) {
                return stream.readEnum(value, &ReadOnlyBinaryStream::readByte);
            }
        );
        !status) {
        return status;
    }
    if (auto status = stream.readOptional(mLocation, &Vec3::read); !status) return status;
    if (auto status = stream.readOptional(mScale, &ReadOnlyBinaryStream::readFloat); !status) return status;
    if (auto status = stream.readOptional(mRotation, &Vec3::read); !status) return status;
    if (auto status = stream.readOptional(mTotalTimeLeft, &ReadOnlyBinaryStream::readFloat); !status) return status;
    if (auto status = stream.readOptional(mColor, &ReadOnlyBinaryStream::readSignedInt); !status) return status;
    if (auto status = stream.readOptional(mDimensionId, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readOptional(mAttachedToEntityId, &ReadOnlyBinaryStream::readUnsignedVarInt64); !status)
        return status;
    if (auto status = stream.readVariantIndex<std::uint32_t>(mShape, &ReadOnlyBinaryStream::readUnsignedVarInt);
        !status)
        return status;
    return std::visit(
        Overload{
            [&](DebugLine& line) { return line.mLineEndLocation.read(stream); },
            [&](DebugBox& box) { return box.mBoxBound.read(stream); },
            [&](DebugSegments& segments) { return stream.readByte(segments.mSegments); },
            [&](DebugText& text) { return stream.readString(text.mText); },
            [&](DebugArrow& arrow) {
                if (auto status = stream.readOptional(arrow.mArrowEndLocation, &Vec3::read); !status) return status;
                if (auto status = stream.readOptional(arrow.mArrowHeadLength, &ReadOnlyBinaryStream::readFloat);
                    !status)
                    return status;
                if (auto status = stream.readOptional(arrow.mArrowHeadRadius, &ReadOnlyBinaryStream::readFloat);
                    !status)
                    return status;
                return stream.readOptional(arrow.mArrowSegments, &ReadOnlyBinaryStream::readByte);
            },
            [&](auto&) { return Result<>{}; }
        },
        mShape
    );
}

} // namespace sculk::protocol::inline abi_v944
