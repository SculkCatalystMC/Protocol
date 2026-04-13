// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/actor/player/SerializedSkin.hpp"

namespace sculk::protocol::inline abi_v944 {

void SerializedSkin::Animation::write(BinaryStream& stream) const {
    stream.writeUnsignedInt(mWidth);
    stream.writeUnsignedInt(mHeight);
    stream.writeString(mSkinImageBytes);
    stream.writeEnum(mAnimationType, &BinaryStream::writeUnsignedInt);
    stream.writeFloat(mFrameCount);
    stream.writeEnum(mAnimationExpression, &BinaryStream::writeUnsignedInt);
}

Result<> SerializedSkin::Animation::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedInt(mWidth); !status) return status;
    if (auto status = stream.readUnsignedInt(mHeight); !status) return status;
    if (auto status = stream.readString(mSkinImageBytes); !status) return status;
    if (auto status = stream.readEnum(mAnimationType, &ReadOnlyBinaryStream::readUnsignedInt); !status) return status;
    if (auto status = stream.readFloat(mFrameCount); !status) return status;
    return stream.readEnum(mAnimationExpression, &ReadOnlyBinaryStream::readUnsignedInt);
}

void SerializedSkin::PersonaPiece::write(BinaryStream& stream) const {
    stream.writeString(mPieceId);
    stream.writeString(mPieceType);
    stream.writeString(mPackId);
    stream.writeBool(mIsDefaultPiece);
    stream.writeString(mProductId);
}

Result<> SerializedSkin::PersonaPiece::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mPieceId); !status) return status;
    if (auto status = stream.readString(mPieceType); !status) return status;
    if (auto status = stream.readString(mPackId); !status) return status;
    if (auto status = stream.readBool(mIsDefaultPiece); !status) return status;
    return stream.readString(mProductId);
}

void SerializedSkin::PieceTintColors::write(BinaryStream& stream) const {
    stream.writeString(mPieceType);
    stream.writeUnsignedInt(static_cast<std::uint32_t>(mPieceTintColors.size()));
    for (const std::string& tintColor : mPieceTintColors) {
        stream.writeString(tintColor);
    }
}

Result<> SerializedSkin::PieceTintColors::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mPieceType); !status) return status;
    std::uint32_t tintColorCount{};
    if (auto status = stream.readUnsignedInt(tintColorCount); !status) return status;
    mPieceTintColors.resize(tintColorCount);
    for (std::string& tintColor : mPieceTintColors) {
        if (auto status = stream.readString(tintColor); !status) return status;
    }
    return {};
}

void SerializedSkin::write(BinaryStream& stream) const {
    stream.writeString(mId);
    stream.writeString(mPlayFabId);
    stream.writeString(mResourcePatch);
    stream.writeUnsignedInt(mSkinImageWidth);
    stream.writeUnsignedInt(mSkinImageHeight);
    stream.writeString(mSkinImageBytes);
    stream.writeUnsignedInt(static_cast<std::uint32_t>(mAnimations.size()));
    for (const Animation& animation : mAnimations) {
        animation.write(stream);
    }
    stream.writeUnsignedInt(mCapeImageWidth);
    stream.writeUnsignedInt(mCapeImageHeight);
    stream.writeString(mCapeImageBytes);
    stream.writeString(mGeometryData);
    stream.writeString(mGeometryDataMinEngineVersion);
    stream.writeString(mAnimationData);
    stream.writeString(mCapeId);
    stream.writeString(mFullId);
    stream.writeString(mArmSize);
    stream.writeString(mSkinColor);
    stream.writeUnsignedInt(static_cast<std::uint32_t>(mPersonaPieces.size()));
    for (const PersonaPiece& piece : mPersonaPieces) {
        piece.write(stream);
    }
    stream.writeUnsignedInt(static_cast<std::uint32_t>(mPieceTintColors.size()));
    for (const PieceTintColors& tintColors : mPieceTintColors) {
        tintColors.write(stream);
    }
    stream.writeBool(mIsPremiumSkin);
    stream.writeBool(mIsPersonaSkin);
    stream.writeBool(mIsPersonaCapeOnClassicSkin);
    stream.writeBool(mIsPrimaryUser);
    stream.writeBool(mOverridesPlayerAppearance);
}

Result<> SerializedSkin::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mId); !status) return status;
    if (auto status = stream.readString(mPlayFabId); !status) return status;
    if (auto status = stream.readString(mResourcePatch); !status) return status;
    if (auto status = stream.readUnsignedInt(mSkinImageWidth); !status) return status;
    if (auto status = stream.readUnsignedInt(mSkinImageHeight); !status) return status;
    if (auto status = stream.readString(mSkinImageBytes); !status) return status;

    std::uint32_t animationCount{};
    if (auto status = stream.readUnsignedInt(animationCount); !status) return status;
    mAnimations.resize(animationCount);
    for (Animation& animation : mAnimations) {
        if (auto status = animation.read(stream); !status) return status;
    }

    if (auto status = stream.readUnsignedInt(mCapeImageWidth); !status) return status;
    if (auto status = stream.readUnsignedInt(mCapeImageHeight); !status) return status;
    if (auto status = stream.readString(mCapeImageBytes); !status) return status;
    if (auto status = stream.readString(mGeometryData); !status) return status;
    if (auto status = stream.readString(mGeometryDataMinEngineVersion); !status) return status;
    if (auto status = stream.readString(mAnimationData); !status) return status;
    if (auto status = stream.readString(mCapeId); !status) return status;
    if (auto status = stream.readString(mFullId); !status) return status;
    if (auto status = stream.readString(mArmSize); !status) return status;
    if (auto status = stream.readString(mSkinColor); !status) return status;

    std::uint32_t personaPieceCount{};
    if (auto status = stream.readUnsignedInt(personaPieceCount); !status) return status;
    mPersonaPieces.resize(personaPieceCount);
    for (PersonaPiece& piece : mPersonaPieces) {
        if (auto status = piece.read(stream); !status) return status;
    }

    std::uint32_t pieceTintColorCount{};
    if (auto status = stream.readUnsignedInt(pieceTintColorCount); !status) return status;
    mPieceTintColors.resize(pieceTintColorCount);
    for (PieceTintColors& tintColors : mPieceTintColors) {
        if (auto status = tintColors.read(stream); !status) return status;
    }

    if (auto status = stream.readBool(mIsPremiumSkin); !status) return status;
    if (auto status = stream.readBool(mIsPersonaSkin); !status) return status;
    if (auto status = stream.readBool(mIsPersonaCapeOnClassicSkin); !status) return status;
    if (auto status = stream.readBool(mIsPrimaryUser); !status) return status;
    return stream.readBool(mOverridesPlayerAppearance);
}

} // namespace sculk::protocol::inline abi_v944
