// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/camera/CameraSplineDefinition.hpp"

namespace sculk::protocol::inline abi_v944 {

void CameraSplineProgressKeyFrame::write(BinaryStream& stream) const {
    stream.writeFloat(mProgress);
    stream.writeFloat(mTime);
    stream.writeString(mEasing);
}

Result<> CameraSplineProgressKeyFrame::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mProgress); !status) return status;
    if (auto status = stream.readFloat(mTime); !status) return status;
    return stream.readString(mEasing);
}

void CameraSplineRotationKeyFrame::write(BinaryStream& stream) const {
    mRotation.write(stream);
    stream.writeFloat(mTime);
    stream.writeString(mEasing);
}

Result<> CameraSplineRotationKeyFrame::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mRotation.read(stream); !status) return status;
    if (auto status = stream.readFloat(mTime); !status) return status;
    return stream.readString(mEasing);
}

void CameraSplineDefinition::write(BinaryStream& stream) const {
    stream.writeString(mName);
    stream.writeFloat(mTotalTime);
    stream.writeString(mSplineType);
    stream.writeArray(mControlPoints, &Vec3::write);
    stream.writeArray(mProgressKeyFrames, &CameraSplineProgressKeyFrame::write);
    stream.writeArray(mRotationKeyFrames, &CameraSplineRotationKeyFrame::write);
}

Result<> CameraSplineDefinition::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    if (auto status = stream.readFloat(mTotalTime); !status) return status;
    if (auto status = stream.readString(mSplineType); !status) return status;
    if (auto status = stream.readArray(mControlPoints, &Vec3::read); !status) return status;
    if (auto status = stream.readArray(mProgressKeyFrames, &CameraSplineProgressKeyFrame::read); !status) return status;
    return stream.readArray(mRotationKeyFrames, &CameraSplineRotationKeyFrame::read);
}

} // namespace sculk::protocol::inline abi_v944
