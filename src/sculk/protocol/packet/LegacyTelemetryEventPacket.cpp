// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/LegacyTelemetryEventPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds LegacyTelemetryEventPacket::getId() const noexcept {
    return MinecraftPacketIds::LegacyTelemetryEvent;
}

std::string_view LegacyTelemetryEventPacket::getName() const noexcept { return "LegacyTelemetryEventPacket"; }

void LegacyTelemetryEventPacket::write(BinaryStream& stream) const {
    stream.writeVarInt64(mActorUniqueId);
    stream.writeEnum(mEventType, &BinaryStream::writeVarInt);
    stream.writeByte(mUsePlayerId);
    stream.writeVariantIndex<std::uint32_t>(mEventData, &BinaryStream::writeUnsignedVarInt);
    std::visit(
        Overload{
            [&](const Achievement& data) { stream.writeVarInt(static_cast<std::int32_t>(data.mAchievementId)); },
            [&](const Interaction& data) {
                stream.writeVarInt64(data.mInteractedEntityId);
                stream.writeVarInt(static_cast<std::int32_t>(data.mInteractionType));
                stream.writeVarInt(data.mInteractionActorType);
                stream.writeVarInt(data.mInteractionActorVariant);
                stream.writeByte(data.mInteractionActorColor);
            },
            [&](const PortalCreated& data) { stream.writeVarInt(data.mDimensionType); },
            [&](const PortalUsed& data) {
                stream.writeVarInt(data.mSourceDimensionType);
                stream.writeVarInt(data.mTargetDimensionType);
            },
            [&](const MobKilled& data) {
                stream.writeVarInt64(data.mKillerActorId);
                stream.writeVarInt64(data.mKilledActorId);
                stream.writeVarInt(static_cast<std::int32_t>(data.mKillerChildActorType));
                stream.writeVarInt(data.mDamageSource);
                stream.writeVarInt(data.mTradeTier);
                stream.writeString(data.mTraderName);
            },
            [&](const CauldronUsed& data) {
                stream.writeUnsignedVarInt(data.mContentsColor);
                stream.writeVarInt(data.mContentsType);
                stream.writeVarInt(data.mFillLevel);
            },
            [&](const PlayerDied& data) {
                stream.writeVarInt(data.mKillerId);
                stream.writeVarInt(data.mKillerVariant);
                stream.writeVarInt(data.mDamageSource);
                stream.writeBool(data.mDiedInRaid);
            },
            [&](const BossKilled& data) {
                stream.writeVarInt64(data.mBossUniqueId);
                stream.writeVarInt(data.mPartySize);
                stream.writeVarInt(data.mBossType);
            },
            [&](const SlashCommand& data) {
                stream.writeVarInt(data.mSuccessCount);
                stream.writeVarInt(data.mErrorCount);
                stream.writeString(data.mCommandName);
                stream.writeString(data.mErrorList);
            },
            [&](const MobBorn& data) {
                stream.writeEnum(data.mMobType, &BinaryStream::writeVarInt);
                stream.writeVarInt(data.mMobVariant);
                stream.writeByte(data.mColor);
            },
            [&](const POICauldronUsed& data) {
                stream.writeVarInt(static_cast<std::int32_t>(data.mInteractionType));
                stream.writeVarInt(data.mItemId);
            },
            [&](const ComposterUsed& data) {
                stream.writeVarInt(static_cast<std::int32_t>(data.mInteractionType));
                stream.writeVarInt(data.mItemId);
            },
            [&](const BellUsed& data) { stream.writeVarInt(data.mItemId); },
            [&](const ActorDefinition& data) { stream.writeString(data.mEventName); },
            [&](const RaidUpdate& data) {
                stream.writeVarInt(data.mCurrentWave);
                stream.writeVarInt(data.mTotalWaves);
                stream.writeBool(data.mSuccess);
            },
            [&](const TargetBlockHit& data) { stream.writeVarInt(data.mRedstoneLevel); },
            [&](const PiglinBarter& data) {
                stream.writeVarInt(data.mItemId);
                stream.writeBool(data.mWasTargetingBarteringPlayer);
            },
            [&](const PlayerWaxedOrUnwaxedCopper& data) { stream.writeVarInt(data.mBlockId); },
            [&](const CodeBuilderRuntimeAction& data) { stream.writeString(data.mCodeBuilderRuntimeAction); },
            [&](const CodeBuilderScoreboard& data) {
                stream.writeString(data.mObjectiveName);
                stream.writeVarInt(data.mScore);
            },
            [&](const ItemUsed& data) {
                stream.writeSignedShort(data.mItemId);
                stream.writeSignedInt(data.mItemAux);
                stream.writeSignedInt(data.mUseMethod);
                stream.writeSignedInt(data.mCount);
            },
            [&](const std::monostate&) {}
        },
        mEventData
    );
}

Result<> LegacyTelemetryEventPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt64(mActorUniqueId); !status) return status;
    if (auto status = stream.readEnum(mEventType, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readByte(mUsePlayerId); !status) return status;
    if (auto status = stream.readVariantIndex<std::uint32_t>(mEventData, &ReadOnlyBinaryStream::readUnsignedVarInt);
        !status)
        return status;
    return std::visit(
        Overload{
            [&](Achievement& data) {
                std::int32_t achievementId{};
                if (auto status = stream.readVarInt(achievementId); !status) return status;
                data.mAchievementId = static_cast<AchievementIds>(achievementId);
                return Result<>{};
            },
            [&](Interaction& data) {
                if (auto status = stream.readVarInt64(data.mInteractedEntityId); !status) return status;
                int interactionType{};
                if (auto status = stream.readVarInt(interactionType); !status) return status;
                data.mInteractionType = static_cast<InteractionType>(interactionType);
                if (auto status = stream.readVarInt(data.mInteractionActorType); !status) return status;
                if (auto status = stream.readVarInt(data.mInteractionActorVariant); !status) return status;
                if (auto status = stream.readByte(data.mInteractionActorColor); !status) return status;
                return Result<>{};
            },
            [&](PortalCreated& data) { return stream.readVarInt(data.mDimensionType); },
            [&](PortalUsed& data) {
                if (auto status = stream.readVarInt(data.mSourceDimensionType); !status) return status;
                if (auto status = stream.readVarInt(data.mTargetDimensionType); !status) return status;
                return Result<>{};
            },
            [&](MobKilled& data) {
                if (auto status = stream.readVarInt64(data.mKillerActorId); !status) return status;
                if (auto status = stream.readVarInt64(data.mKilledActorId); !status) return status;
                if (auto status = stream.readEnum(data.mKillerChildActorType, &ReadOnlyBinaryStream::readVarInt);
                    !status)
                    return status;
                if (auto status = stream.readVarInt(data.mDamageSource); !status) return status;
                if (auto status = stream.readVarInt(data.mTradeTier); !status) return status;
                if (auto status = stream.readString(data.mTraderName); !status) return status;
                return Result<>{};
            },
            [&](CauldronUsed& data) {
                if (auto status = stream.readUnsignedVarInt(data.mContentsColor); !status) return status;
                if (auto status = stream.readVarInt(data.mContentsType); !status) return status;
                if (auto status = stream.readVarInt(data.mFillLevel); !status) return status;
                return Result<>{};
            },
            [&](PlayerDied& data) {
                if (auto status = stream.readVarInt(data.mKillerId); !status) return status;
                if (auto status = stream.readVarInt(data.mKillerVariant); !status) return status;
                if (auto status = stream.readVarInt(data.mDamageSource); !status) return status;
                if (auto status = stream.readBool(data.mDiedInRaid); !status) return status;
                return Result<>{};
            },
            [&](BossKilled& data) {
                if (auto status = stream.readVarInt64(data.mBossUniqueId); !status) return status;
                if (auto status = stream.readVarInt(data.mPartySize); !status) return status;
                if (auto status = stream.readVarInt(data.mBossType); !status) return status;
                return Result<>{};
            },
            [&](SlashCommand& data) {
                if (auto status = stream.readVarInt(data.mSuccessCount); !status) return status;
                if (auto status = stream.readVarInt(data.mErrorCount); !status) return status;
                if (auto status = stream.readString(data.mCommandName); !status) return status;
                if (auto status = stream.readString(data.mErrorList); !status) return status;
                return Result<>{};
            },
            [&](MobBorn& data) {
                if (auto status = stream.readEnum(data.mMobType, &ReadOnlyBinaryStream::readVarInt); !status)
                    return status;
                if (auto status = stream.readVarInt(data.mMobVariant); !status) return status;
                if (auto status = stream.readByte(data.mColor); !status) return status;
                return Result<>{};
            },
            [&](POICauldronUsed& data) {
                int interactionType{};
                if (auto status = stream.readVarInt(interactionType); !status) return status;
                data.mInteractionType = static_cast<POIBlockInteractionType>(interactionType);
                if (auto status = stream.readVarInt(data.mItemId); !status) return status;
                return Result<>{};
            },
            [&](ComposterUsed& data) {
                int interactionType{};
                if (auto status = stream.readVarInt(interactionType); !status) return status;
                data.mInteractionType = static_cast<POIBlockInteractionType>(interactionType);
                if (auto status = stream.readVarInt(data.mItemId); !status) return status;
                return Result<>{};
            },
            [&](BellUsed& data) {
                if (auto status = stream.readVarInt(data.mItemId); !status) return status;
                return Result<>{};
            },
            [&](ActorDefinition& data) { return stream.readString(data.mEventName); },
            [&](RaidUpdate& data) {
                if (auto status = stream.readVarInt(data.mCurrentWave); !status) return status;
                if (auto status = stream.readVarInt(data.mTotalWaves); !status) return status;
                if (auto status = stream.readBool(data.mSuccess); !status) return status;
                return Result<>{};
            },
            [&](TargetBlockHit& data) { return stream.readVarInt(data.mRedstoneLevel); },
            [&](PiglinBarter& data) {
                if (auto status = stream.readVarInt(data.mItemId); !status) return status;
                if (auto status = stream.readBool(data.mWasTargetingBarteringPlayer); !status) return status;
                return Result<>{};
            },
            [&](PlayerWaxedOrUnwaxedCopper& data) { return stream.readVarInt(data.mBlockId); },
            [&](CodeBuilderRuntimeAction& data) { return stream.readString(data.mCodeBuilderRuntimeAction); },
            [&](CodeBuilderScoreboard& data) {
                if (auto status = stream.readString(data.mObjectiveName); !status) return status;
                if (auto status = stream.readVarInt(data.mScore); !status) return status;
                return Result<>{};
            },
            [&](ItemUsed& data) {
                if (auto status = stream.readSignedShort(data.mItemId); !status) return status;
                if (auto status = stream.readSignedInt(data.mItemAux); !status) return status;
                if (auto status = stream.readSignedInt(data.mUseMethod); !status) return status;
                if (auto status = stream.readSignedInt(data.mCount); !status) return status;
                return Result<>{};
            },
            [&](std::monostate&) { return Result<>{}; }
        },
        mEventData
    );
}

} // namespace sculk::protocol::inline abi_v944
