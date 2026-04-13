// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/level/LevelSettings.hpp"

namespace sculk::protocol::inline abi_v944 {

void LevelSettings::write(BinaryStream& stream) const {
    stream.writeUnsignedInt64(mSeed);
    mSpawnSettings.write(stream);
    stream.writeVarInt(mGeneratorType);
    stream.writeEnum(mGameType, &BinaryStream::writeVarInt);
    stream.writeBool(mIsHardCore);
    stream.writeEnum(mDifficulty, &BinaryStream::writeVarInt);
    mSpawnPosition.write(stream);
    stream.writeBool(mAchievementDisabled);
    stream.writeVarInt(mEditorWorldType);
    stream.writeBool(mIsCreatedInEditor);
    stream.writeBool(mIsExportedFromEditor);
    stream.writeVarInt(mDayCycleStopTime);
    stream.writeVarInt(mEduOffer);
    stream.writeBool(mIsEdu);
    stream.writeString(mEduProductId);
    stream.writeFloat(mRainLevel);
    stream.writeFloat(mLightningLevel);
    stream.writeBool(mPlatformLocked);
    stream.writeBool(mMultiplayer);
    stream.writeBool(mLanBroadcast);
    stream.writeVarInt(mXboxLiveBroadcastSetting);
    stream.writeVarInt(mPlatformBroadcastSetting);
    stream.writeBool(mCommandsEnabled);
    stream.writeBool(mTextureRequired);
    stream.writeArray(mGameRules, &GameRuleData::writeLevelSettings);
    mExperiments.write(stream);
    stream.writeBool(mBonusChest);
    stream.writeBool(mStartsWithMap);
    stream.writeEnum(mPlayerPermission, &BinaryStream::writeVarInt);
    stream.writeSignedInt(mTickRange);
    stream.writeBool(mLockBehaviorPack);
    stream.writeBool(mLockResourcePack);
    stream.writeBool(mIsFromLockedTemplate);
    stream.writeBool(mOnlyMsaGamertags);
    stream.writeBool(mIsFromWorldTemplate);
    stream.writeBool(mIsWorldTemplateOptionLocked);
    stream.writeBool(mSpawnV1Villagers);
    stream.writeBool(mPersonaDisabled);
    stream.writeBool(mCustomSkinsDisabled);
    stream.writeBool(mEmoteChatMuted);
    stream.writeString(mBaseGameVersion);
    stream.writeSignedInt(mLimitedWorldWidth);
    stream.writeSignedInt(mLimitedWorldDepth);
    stream.writeBool(mNetherType);
    stream.writeString(mEduResourceButtonName);
    stream.writeString(mEduResourceUri);
    stream.writeBool(mForceExperimentalGameplay);
    stream.writeByte(mChatRestrictionLevel);
    stream.writeBool(mDisablePlayerInteractions);
}

Result<> LevelSettings::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedInt64(mSeed); !status) return status;
    if (auto status = mSpawnSettings.read(stream); !status) return status;
    if (auto status = stream.readVarInt(mGeneratorType); !status) return status;
    if (auto status = stream.readEnum(mGameType, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readBool(mIsHardCore); !status) return status;
    if (auto status = stream.readEnum(mDifficulty, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = mSpawnPosition.read(stream); !status) return status;
    if (auto status = stream.readBool(mAchievementDisabled); !status) return status;
    if (auto status = stream.readVarInt(mEditorWorldType); !status) return status;
    if (auto status = stream.readBool(mIsCreatedInEditor); !status) return status;
    if (auto status = stream.readBool(mIsExportedFromEditor); !status) return status;
    if (auto status = stream.readVarInt(mDayCycleStopTime); !status) return status;
    if (auto status = stream.readVarInt(mEduOffer); !status) return status;
    if (auto status = stream.readBool(mIsEdu); !status) return status;
    if (auto status = stream.readString(mEduProductId); !status) return status;
    if (auto status = stream.readFloat(mRainLevel); !status) return status;
    if (auto status = stream.readFloat(mLightningLevel); !status) return status;
    if (auto status = stream.readBool(mPlatformLocked); !status) return status;
    if (auto status = stream.readBool(mMultiplayer); !status) return status;
    if (auto status = stream.readBool(mLanBroadcast); !status) return status;
    if (auto status = stream.readVarInt(mXboxLiveBroadcastSetting); !status) return status;
    if (auto status = stream.readVarInt(mPlatformBroadcastSetting); !status) return status;
    if (auto status = stream.readBool(mCommandsEnabled); !status) return status;
    if (auto status = stream.readBool(mTextureRequired); !status) return status;
    if (auto status = stream.readArray(mGameRules, &GameRuleData::readLevelSettings); !status) return status;
    if (auto status = mExperiments.read(stream); !status) return status;
    if (auto status = stream.readBool(mBonusChest); !status) return status;
    if (auto status = stream.readBool(mStartsWithMap); !status) return status;
    if (auto status = stream.readEnum(mPlayerPermission, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readSignedInt(mTickRange); !status) return status;
    if (auto status = stream.readBool(mLockBehaviorPack); !status) return status;
    if (auto status = stream.readBool(mLockResourcePack); !status) return status;
    if (auto status = stream.readBool(mIsFromLockedTemplate); !status) return status;
    if (auto status = stream.readBool(mOnlyMsaGamertags); !status) return status;
    if (auto status = stream.readBool(mIsFromWorldTemplate); !status) return status;
    if (auto status = stream.readBool(mIsWorldTemplateOptionLocked); !status) return status;
    if (auto status = stream.readBool(mSpawnV1Villagers); !status) return status;
    if (auto status = stream.readBool(mPersonaDisabled); !status) return status;
    if (auto status = stream.readBool(mCustomSkinsDisabled); !status) return status;
    if (auto status = stream.readBool(mEmoteChatMuted); !status) return status;
    if (auto status = stream.readString(mBaseGameVersion); !status) return status;
    if (auto status = stream.readSignedInt(mLimitedWorldWidth); !status) return status;
    if (auto status = stream.readSignedInt(mLimitedWorldDepth); !status) return status;
    if (auto status = stream.readBool(mNetherType); !status) return status;
    if (auto status = stream.readString(mEduResourceButtonName); !status) return status;
    if (auto status = stream.readString(mEduResourceUri); !status) return status;
    if (auto status = stream.readBool(mForceExperimentalGameplay); !status) return status;
    if (auto status = stream.readByte(mChatRestrictionLevel); !status) return status;
    return stream.readBool(mDisablePlayerInteractions);
}

} // namespace sculk::protocol::inline abi_v944
