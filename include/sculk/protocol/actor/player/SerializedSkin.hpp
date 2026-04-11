// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"

namespace sculk::protocol::inline abi_v944 {

struct SerializedSkin {
    struct Animation {
        std::uint32_t mWidth{};
        std::uint32_t mHeight{};
        std::string   mSkinImageBytes{};
        std::uint32_t mAnimationType{};
        float         mFrameCount{};
        std::uint32_t mAnimationExpression{};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

    struct PersonaPiece {
        std::string mPieceId{};
        std::string mPieceType{};
        std::string mPackId{};
        bool        mIsDefaultPiece{};
        std::string mProductId{};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

    struct PieceTintColors {
        std::string              mPieceType{};
        std::vector<std::string> mPieceTintColors{};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

    std::string                  mId{};
    std::string                  mPlayFabId{};
    std::string                  mResourcePatch{};
    std::uint32_t                mSkinImageWidth{};
    std::uint32_t                mSkinImageHeight{};
    std::string                  mSkinImageBytes{};
    std::vector<Animation>       mAnimations{};
    std::uint32_t                mCapeImageWidth{};
    std::uint32_t                mCapeImageHeight{};
    std::string                  mCapeImageBytes{};
    std::string                  mGeometryData{};
    std::string                  mGeometryDataMinEngineVersion{};
    std::string                  mAnimationData{};
    std::string                  mCapeId{};
    std::string                  mFullId{};
    std::string                  mArmSize{};
    std::string                  mSkinColor{};
    std::vector<PersonaPiece>    mPersonaPieces{};
    std::vector<PieceTintColors> mPieceTintColors{};
    bool                         mIsPremiumSkin{};
    bool                         mIsPersonaSkin{};
    bool                         mIsPersonaCapeOnClassicSkin{};
    bool                         mIsPrimaryUser{};
    bool                         mOverridesPlayerAppearance{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
