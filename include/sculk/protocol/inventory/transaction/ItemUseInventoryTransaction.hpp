// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/inventory/item/NetworkItemStackDescriptor.hpp"
#include "sculk/protocol/level/block/BlockPos.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"

namespace sculk::protocol::inline abi_v944 {

class ItemUseInventoryTransaction {
public:
    enum class ActionType : uint32_t {
        Place       = 0,
        Use         = 1,
        Destroy     = 2,
        UseAsAttack = 3,
    };

    enum class ClientCooldownState : std::uint8_t {
        Off = 0,
        On  = 1,
    };

    enum class PredictedResult : std::uint8_t {
        Failure = 0,
        Success = 1,
    };

    enum class TriggerType : std::uint32_t {
        Unknown        = 0,
        PlayerInput    = 1,
        SimulationTick = 2,
    };

public:
    ActionType                 mActionType{};
    TriggerType                mTriggerType{};
    BlockPos                   mPos{};
    std::uint32_t              mTargetBlockId{};
    std::int32_t               mFace{};
    std::int32_t               mSlot{};
    NetworkItemStackDescriptor mItem{};
    Vec3                       mFromPos{};
    Vec3                       mClickPos{};
    PredictedResult            mClientPredictedResult{};
    ClientCooldownState        mClientCooldownState{};

public:
    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
