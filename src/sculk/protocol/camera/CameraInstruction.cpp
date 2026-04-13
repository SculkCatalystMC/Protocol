// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/camera/CameraInstruction.hpp"
#include "../utility/EnumName.hpp"

namespace sculk::protocol::inline abi_v944 {

void CameraInstruction::FadeInstruction::TimeOption::write(BinaryStream& stream) const {
    stream.writeFloat(mFadeInTime);
    stream.writeFloat(mHoldTime);
    stream.writeFloat(mFadeOutTime);
}

Result<> CameraInstruction::FadeInstruction::TimeOption::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mFadeInTime); !status) return status;
    if (auto status = stream.readFloat(mHoldTime); !status) return status;
    return stream.readFloat(mFadeOutTime);
}

void CameraInstruction::FadeInstruction::ColorOption::write(BinaryStream& stream) const {
    stream.writeFloat(mRed);
    stream.writeFloat(mGreen);
    stream.writeFloat(mBlue);
}

Result<> CameraInstruction::FadeInstruction::ColorOption::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mRed); !status) return status;
    if (auto status = stream.readFloat(mGreen); !status) return status;
    return stream.readFloat(mBlue);
}

void CameraInstruction::FadeInstruction::write(BinaryStream& stream) const {
    stream.writeOptional(mTime, &TimeOption::write);
    stream.writeOptional(mColor, &ColorOption::write);
}

Result<> CameraInstruction::FadeInstruction::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readOptional(mTime, &TimeOption::read); !status) return status;
    return stream.readOptional(mColor, &ColorOption::read);
}

void CameraInstruction::SetInstruction::EaseOption::write(BinaryStream& stream) const {
    stream.writeEnum(mEasingType, &BinaryStream::writeByte);
    stream.writeFloat(mEasingTime);
}

Result<> CameraInstruction::SetInstruction::EaseOption::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mEasingType, &ReadOnlyBinaryStream::readByte); !status) return status;
    return stream.readFloat(mEasingTime);
}

void CameraInstruction::SetInstruction::write(BinaryStream& stream) const {
    stream.writeUnsignedInt(mPresetIndex);
    stream.writeOptional(mEase, &EaseOption::write);
    stream.writeOptional(mPos, &Vec3::write);
    stream.writeOptional(mRot, &Vec2::write);
    stream.writeOptional(mFacing, &Vec3::write);
    stream.writeOptional(mViewOffset, &Vec2::write);
    stream.writeOptional(mEntityOffset, &Vec3::write);
    stream.writeOptional(mDefault, &BinaryStream::writeBool);
    stream.writeBool(mRemoveIgnoreStartingValuesComponent);
}

Result<> CameraInstruction::SetInstruction::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedInt(mPresetIndex); !status) return status;
    if (auto status = stream.readOptional(mEase, &EaseOption::read); !status) return status;
    if (auto status = stream.readOptional(mPos, &Vec3::read); !status) return status;
    if (auto status = stream.readOptional(mRot, &Vec2::read); !status) return status;
    if (auto status = stream.readOptional(mFacing, &Vec3::read); !status) return status;
    if (auto status = stream.readOptional(mViewOffset, &Vec2::read); !status) return status;
    if (auto status = stream.readOptional(mEntityOffset, &Vec3::read); !status) return status;
    if (auto status = stream.readOptional(mDefault, &ReadOnlyBinaryStream::readBool); !status) return status;
    return stream.readBool(mRemoveIgnoreStartingValuesComponent);
}

void CameraInstruction::TargetInstruction::write(BinaryStream& stream) const {
    stream.writeOptional(mTargetCenterOffset, &Vec3::write);
    stream.writeSignedInt64(mTargetActorId);
}

Result<> CameraInstruction::TargetInstruction::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readOptional(mTargetCenterOffset, &Vec3::read); !status) return status;
    return stream.readSignedInt64(mTargetActorId);
}

void CameraInstruction::FovInstruction::write(BinaryStream& stream) const {
    stream.writeFloat(mFieldOfView);
    stream.writeFloat(mEaseTime);
    utils::writeEnumName(stream, mEaseType);
    stream.writeBool(mClear);
}

Result<> CameraInstruction::FovInstruction::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mFieldOfView); !status) return status;
    if (auto status = stream.readFloat(mEaseTime); !status) return status;
    if (auto status = utils::readEnumName(stream, mEaseType); !status) return status;
    return stream.readBool(mClear);
}

void CameraInstruction::SplineInstruction::SplineProgressOption::write(BinaryStream& stream) const {
    stream.writeFloat(mKeyFrameValue);
    stream.writeFloat(mKeyFrameTime);
    utils::writeEnumName(stream, mKeyFrameEasingFunc);
}

Result<> CameraInstruction::SplineInstruction::SplineProgressOption::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mKeyFrameValue); !status) return status;
    if (auto status = stream.readFloat(mKeyFrameTime); !status) return status;
    return utils::readEnumName(stream, mKeyFrameEasingFunc);
}

void CameraInstruction::SplineInstruction::RotationOption::write(BinaryStream& stream) const {
    mKeyFrameValues.write(stream);
    stream.writeFloat(mKeyFrameTimes);
    utils::writeEnumName(stream, mKeyFrameEasingFunc);
}

Result<> CameraInstruction::SplineInstruction::RotationOption::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mKeyFrameValues.read(stream); !status) return status;
    if (auto status = stream.readFloat(mKeyFrameTimes); !status) return status;
    return utils::readEnumName(stream, mKeyFrameEasingFunc);
}

void CameraInstruction::SplineInstruction::write(BinaryStream& stream) const {
    stream.writeFloat(mTotalTime);
    stream.writeEnum(mType, &BinaryStream::writeByte);
    stream.writeArray(mCurve, &Vec3::write);
    stream.writeArray(mProgressKeyFrames, &SplineProgressOption::write);
    stream.writeArray(mRotationOptions, &RotationOption::write);
    stream.writeOptional(mSplineIdentifier, &BinaryStream::writeString);
    stream.writeOptional(mLoadFromJson, &BinaryStream::writeBool);
}

Result<> CameraInstruction::SplineInstruction::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mTotalTime); !status) return status;
    if (auto status = stream.readEnum(mType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readArray(mCurve, &Vec3::read); !status) return status;
    if (auto status = stream.readArray(mProgressKeyFrames, &SplineProgressOption::read); !status) return status;
    if (auto status = stream.readArray(mRotationOptions, &RotationOption::read); !status) return status;
    if (auto status = stream.readOptional(mSplineIdentifier, &ReadOnlyBinaryStream::readString); !status) return status;
    return stream.readOptional(mLoadFromJson, &ReadOnlyBinaryStream::readBool);
}

void CameraInstruction::AttachToEntityInstruction::write(BinaryStream& stream) const {
    stream.writeSignedInt64(mActorUniqueId);
}

Result<> CameraInstruction::AttachToEntityInstruction::read(ReadOnlyBinaryStream& stream) {
    return stream.readSignedInt64(mActorUniqueId);
}

void CameraInstruction::write(BinaryStream& stream) const {
    stream.writeOptional(mSet, &SetInstruction::write);
    stream.writeOptional(mClear, &BinaryStream::writeBool);
    stream.writeOptional(mFade, &FadeInstruction::write);
    stream.writeOptional(mTarget, &TargetInstruction::write);
    stream.writeOptional(mRemoveTarget, &BinaryStream::writeBool);
    stream.writeOptional(mFieldOfView, &FovInstruction::write);
    stream.writeOptional(mSpline, &SplineInstruction::write);
    stream.writeOptional(mAttach, &AttachToEntityInstruction::write);
    stream.writeOptional(mDetachFromEntity, &BinaryStream::writeBool);
}

Result<> CameraInstruction::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readOptional(mSet, &SetInstruction::read); !status) return status;
    if (auto status = stream.readOptional(mClear, &ReadOnlyBinaryStream::readBool); !status) return status;
    if (auto status = stream.readOptional(mFade, &FadeInstruction::read); !status) return status;
    if (auto status = stream.readOptional(mTarget, &TargetInstruction::read); !status) return status;
    if (auto status = stream.readOptional(mRemoveTarget, &ReadOnlyBinaryStream::readBool); !status) return status;
    if (auto status = stream.readOptional(mFieldOfView, &FovInstruction::read); !status) return status;
    if (auto status = stream.readOptional(mSpline, &SplineInstruction::read); !status) return status;
    if (auto status = stream.readOptional(mAttach, &AttachToEntityInstruction::read); !status) return status;
    return stream.readOptional(mDetachFromEntity, &ReadOnlyBinaryStream::readBool);
}

} // namespace sculk::protocol::inline abi_v944
