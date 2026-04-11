// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/utility/math/Vec3.hpp"

namespace sculk::protocol::inline abi_v944 {

struct CameraSplineProgressKeyFrame {
    float       mProgress{};
    float       mTime{};
    std::string mEasing{};

    void                   write(BinaryStream& stream) const;
    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct CameraSplineRotationKeyFrame {
    Vec3        mRotation{};
    float       mTime{};
    std::string mEasing{};

    void                   write(BinaryStream& stream) const;
    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct CameraSplineDefinition {
    std::string                               mName{};
    float                                     mTotalTime{};
    std::string                               mSplineType{};
    std::vector<Vec3>                         mControlPoints{};
    std::vector<CameraSplineProgressKeyFrame> mProgressKeyFrames{};
    std::vector<CameraSplineRotationKeyFrame> mRotationKeyFrames{};

    void                   write(BinaryStream& stream) const;
    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
