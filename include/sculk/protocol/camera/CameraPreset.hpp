// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/actor/player/ControlScheme.hpp"
#include "sculk/protocol/camera/CameraAimAssist.hpp"
#include "sculk/protocol/utility/math/Vec2.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"

namespace sculk::protocol::inline abi_v944 {

class CameraPreset {
public:
    enum class AudioListener : std::uint8_t {
        Camera = 0,
        Player = 1,
    };

public:
    std::string                                    mName{};
    std::string                                    mInhertFrom{};
    std::optional<float>                           mPosX{};
    std::optional<float>                           mPosY{};
    std::optional<float>                           mPosZ{};
    std::optional<float>                           mRotX{};
    std::optional<float>                           mRotY{};
    std::optional<float>                           mRotationSpeed{};
    std::optional<bool>                            mSnapToTarget{};
    std::optional<Vec2>                            mHorizontalRotationLimit{};
    std::optional<Vec2>                            mVerticalRotationLimit{};
    std::optional<bool>                            mContinueTargeting{};
    std::optional<float>                           mBlockListingRadius{};
    std::optional<Vec2>                            mViewOffset{};
    std::optional<Vec3>                            mEntityOffset{};
    std::optional<float>                           mRadius{};
    std::optional<float>                           mYawLimitMin{};
    std::optional<float>                           mYawLimitMax{};
    std::optional<AudioListener>                   mListener{};
    std::optional<bool>                            mPlayerEffects{};
    std::optional<bool>                            mAlignTargetAndCameraForward{};
    std::optional<CameraPresetAimAssistDefinition> mAimAssist{};
    std::optional<ControlScheme>                   mControlScheme{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
