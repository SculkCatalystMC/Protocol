// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "EasingType.hpp"
#include "sculk/protocol/utility/math/Vec2.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"

namespace sculk::protocol::inline abi_v944 {

struct CameraInstruction {
    struct FadeInstruction {
        struct TimeOption {
            float mFadeInTime{};
            float mHoldTime{};
            float mFadeOutTime{};

            void write(BinaryStream& stream) const;

            [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
        };

        struct ColorOption {
            float mRed{};
            float mGreen{};
            float mBlue{};

            void write(BinaryStream& stream) const;

            [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
        };

        std::optional<TimeOption>  mTime{};
        std::optional<ColorOption> mColor{};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

    struct SetInstruction {
        struct EaseOption {
            EasingType mEasingType{};
            float      mEasingTime{};

            void write(BinaryStream& stream) const;

            [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
        };

        std::uint32_t             mPresetIndex{};
        std::optional<EaseOption> mEase{};
        std::optional<Vec3>       mPos{};
        std::optional<Vec2>       mRot{};
        std::optional<Vec3>       mFacing{};
        std::optional<Vec2>       mViewOffset{};
        std::optional<Vec3>       mEntityOffset{};
        std::optional<bool>       mDefault{};
        bool                      mRemoveIgnoreStartingValuesComponent{false};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

    struct TargetInstruction {
        std::optional<Vec3> mTargetCenterOffset{};
        std::int64_t        mTargetActorId{};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

    struct FovInstruction {
        float      mFieldOfView{};
        float      mEaseTime{};
        EasingType mEaseType{};
        bool       mClear{};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

    struct SplineInstruction {
        enum class Type : std::uint8_t {
            CatmullRom = 0,
            Linear     = 1,
        };

        struct SplineProgressOption {
            float      mKeyFrameValue{};
            float      mKeyFrameTime{};
            EasingType mKeyFrameEasingFunc{};

            void write(BinaryStream& stream) const;

            [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
        };

        struct RotationOption {
            Vec3       mKeyFrameValues{};
            float      mKeyFrameTimes{};
            EasingType mKeyFrameEasingFunc{};

            void write(BinaryStream& stream) const;

            [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
        };

        float                             mTotalTime{};
        Type                              mType{};
        std::vector<Vec3>                 mCurve{};
        std::vector<SplineProgressOption> mProgressKeyFrames{};
        std::vector<RotationOption>       mRotationOptions{};
        std::optional<std::string>        mSplineIdentifier{};
        std::optional<bool>               mLoadFromJson{};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

    struct AttachToEntityInstruction {
        std::int64_t mActorUniqueId{};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

    std::optional<SetInstruction>            mSet{};
    std::optional<bool>                      mClear{};
    std::optional<FadeInstruction>           mFade{};
    std::optional<TargetInstruction>         mTarget{};
    std::optional<bool>                      mRemoveTarget{};
    std::optional<FovInstruction>            mFieldOfView{};
    std::optional<SplineInstruction>         mSpline{};
    std::optional<AttachToEntityInstruction> mAttach{};
    std::optional<bool>                      mDetachFromEntity{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
