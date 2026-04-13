// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/camera/CameraPreset.hpp"

namespace sculk::protocol::inline abi_v944 {

void CameraPreset::write(BinaryStream& stream) const {
    stream.writeString(mName);
    stream.writeString(mInhertFrom);
    stream.writeOptional(mPosX, &BinaryStream::writeFloat);
    stream.writeOptional(mPosY, &BinaryStream::writeFloat);
    stream.writeOptional(mPosZ, &BinaryStream::writeFloat);
    stream.writeOptional(mRotX, &BinaryStream::writeFloat);
    stream.writeOptional(mRotY, &BinaryStream::writeFloat);
    stream.writeOptional(mRotationSpeed, &BinaryStream::writeFloat);
    stream.writeOptional(mSnapToTarget, &BinaryStream::writeBool);
    stream.writeOptional(mHorizontalRotationLimit, &Vec2::write);
    stream.writeOptional(mVerticalRotationLimit, &Vec2::write);
    stream.writeOptional(mContinueTargeting, &BinaryStream::writeBool);
    stream.writeOptional(mBlockListingRadius, &BinaryStream::writeFloat);
    stream.writeOptional(mViewOffset, &Vec2::write);
    stream.writeOptional(mEntityOffset, &Vec3::write);
    stream.writeOptional(mRadius, &BinaryStream::writeFloat);
    stream.writeOptional(mYawLimitMin, &BinaryStream::writeFloat);
    stream.writeOptional(mYawLimitMax, &BinaryStream::writeFloat);
    stream.writeOptional(mListener, [](BinaryStream& stream, AudioListener value) {
        stream.writeEnum(value, &BinaryStream::writeByte);
    });
    stream.writeOptional(mPlayerEffects, &BinaryStream::writeBool);
    stream.writeOptional(mAimAssist, &CameraPresetAimAssistDefinition::write);
    stream.writeOptional(mControlScheme, [](BinaryStream& stream, ControlScheme value) {
        stream.writeEnum(value, &BinaryStream::writeByte);
    });
}

Result<> CameraPreset::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    if (auto status = stream.readString(mInhertFrom); !status) return status;
    if (auto status = stream.readOptional(mPosX, &ReadOnlyBinaryStream::readFloat); !status) return status;
    if (auto status = stream.readOptional(mPosY, &ReadOnlyBinaryStream::readFloat); !status) return status;
    if (auto status = stream.readOptional(mPosZ, &ReadOnlyBinaryStream::readFloat); !status) return status;
    if (auto status = stream.readOptional(mRotX, &ReadOnlyBinaryStream::readFloat); !status) return status;
    if (auto status = stream.readOptional(mRotY, &ReadOnlyBinaryStream::readFloat); !status) return status;
    if (auto status = stream.readOptional(mRotationSpeed, &ReadOnlyBinaryStream::readFloat); !status) return status;
    if (auto status = stream.readOptional(mSnapToTarget, &ReadOnlyBinaryStream::readBool); !status) return status;
    if (auto status = stream.readOptional(mHorizontalRotationLimit, &Vec2::read); !status) return status;
    if (auto status = stream.readOptional(mVerticalRotationLimit, &Vec2::read); !status) return status;
    if (auto status = stream.readOptional(mContinueTargeting, &ReadOnlyBinaryStream::readBool); !status) return status;
    if (auto status = stream.readOptional(mBlockListingRadius, &ReadOnlyBinaryStream::readFloat); !status)
        return status;
    if (auto status = stream.readOptional(mViewOffset, &Vec2::read); !status) return status;
    if (auto status = stream.readOptional(mEntityOffset, &Vec3::read); !status) return status;
    if (auto status = stream.readOptional(mRadius, &ReadOnlyBinaryStream::readFloat); !status) return status;
    if (auto status = stream.readOptional(mYawLimitMin, &ReadOnlyBinaryStream::readFloat); !status) return status;
    if (auto status = stream.readOptional(mYawLimitMax, &ReadOnlyBinaryStream::readFloat); !status) return status;
    if (auto status = stream.readOptional(
            mListener,
            [](ReadOnlyBinaryStream& stream, AudioListener& value) {
                return stream.readEnum(value, &ReadOnlyBinaryStream::readByte);
            }
        );
        !status)
        return status;
    if (auto status = stream.readOptional(mPlayerEffects, &ReadOnlyBinaryStream::readBool); !status) return status;
    if (auto status = stream.readOptional(mAimAssist, &CameraPresetAimAssistDefinition::read); !status) return status;
    return stream.readOptional(mControlScheme, [](ReadOnlyBinaryStream& stream, ControlScheme& value) {
        return stream.readEnum(value, &ReadOnlyBinaryStream::readByte);
    });
}

} // namespace sculk::protocol::inline abi_v944
