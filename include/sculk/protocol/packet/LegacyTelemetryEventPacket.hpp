// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/actor/ActorType.hpp"
#include "sculk/protocol/actor/InteractionType.hpp"
#include "sculk/protocol/actor/POIBlockInteractionType.hpp"
#include "sculk/protocol/actor/player/AchievementIds.hpp"
#include "sculk/protocol/level/LegacyTelemetryEventType.hpp"
#include "sculk/protocol/packet/IPacket.hpp"
#include <variant>

namespace sculk::protocol::inline abi_v944 {

class LegacyTelemetryEventPacket : public IPacket {
public:
    struct Achievement {
        AchievementIds mAchievementId{};
    };

    struct Interaction {
        std::int64_t    mInteractedEntityId{};
        InteractionType mInteractionType{};
        int             mInteractionActorType{};
        int             mInteractionActorVariant{};
        std::uint8_t    mInteractionActorColor{};
    };

    struct PortalCreated {
        int mDimensionType{};
    };

    struct PortalUsed {
        int mSourceDimensionType{};
        int mTargetDimensionType{};
    };

    struct MobKilled {
        std::int64_t mKillerActorId{};
        std::int64_t mKilledActorId{};
        ActorType    mKillerChildActorType{};
        int          mDamageSource{};
        int          mTradeTier{};
        std::string  mTraderName{};
    };

    struct CauldronUsed {
        std::uint32_t mContentsColor{};
        std::int32_t  mContentsType{};
        std::int32_t  mFillLevel{};
    };

    struct PlayerDied {
        int  mKillerId{};
        int  mKillerVariant{};
        int  mDamageSource{};
        bool mDiedInRaid{};
    };

    struct BossKilled {
        std::int64_t mBossUniqueId{};
        int          mPartySize{};
        int          mBossType{};
    };

    struct SlashCommand {
        int         mSuccessCount{};
        int         mErrorCount{};
        std::string mCommandName{};
        std::string mErrorList{};
    };

    struct MobBorn {
        ActorType    mMobType{};
        int          mMobVariant{};
        std::uint8_t mColor{};
    };

    struct POICauldronUsed {
        POIBlockInteractionType mInteractionType{};
        std::int32_t            mItemId{};
    };

    struct ComposterUsed {
        POIBlockInteractionType mInteractionType{};
        std::int32_t            mItemId{};
    };

    struct BellUsed {
        std::int32_t mItemId{};
    };

    struct ActorDefinition {
        std::string mEventName{};
    };

    struct RaidUpdate {
        int  mCurrentWave{};
        int  mTotalWaves{};
        bool mSuccess{};
    };

    struct TargetBlockHit {
        int mRedstoneLevel{};
    };

    struct PiglinBarter {
        int  mItemId{};
        bool mWasTargetingBarteringPlayer{};
    };

    struct PlayerWaxedOrUnwaxedCopper {
        int mBlockId{};
    };

    struct CodeBuilderRuntimeAction {
        std::string mCodeBuilderRuntimeAction{};
    };

    struct CodeBuilderScoreboard {
        std::string mObjectiveName{};
        int         mScore{};
    };

    struct ItemUsed {
        std::int16_t mItemId{};
        std::int32_t mItemAux{};
        std::int32_t mUseMethod{};
        std::int32_t mCount{};
    };

    using LegacyTelemetryEventVariant = std::variant<
        Achievement,
        Interaction,
        PortalCreated,
        PortalUsed,
        MobKilled,
        CauldronUsed,
        PlayerDied,
        BossKilled,
        SlashCommand,
        MobBorn,
        POICauldronUsed,
        ComposterUsed,
        BellUsed,
        ActorDefinition,
        RaidUpdate,
        TargetBlockHit,
        PiglinBarter,
        PlayerWaxedOrUnwaxedCopper,
        CodeBuilderRuntimeAction,
        CodeBuilderScoreboard,
        ItemUsed,
        std::monostate>;

public:
    std::int64_t                mActorUniqueId{};
    LegacyTelemetryEventType    mEventType{};
    std::uint8_t                mUsePlayerId{};
    LegacyTelemetryEventVariant mEventData{std::monostate{}};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
