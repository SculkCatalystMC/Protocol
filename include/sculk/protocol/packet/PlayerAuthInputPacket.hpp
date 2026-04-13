// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/actor/player/PlayerAuthInputData.hpp"
#include "sculk/protocol/actor/player/PlayerBlockActions.hpp"
#include "sculk/protocol/inventory/item/ItemStackRequest.hpp"
#include "sculk/protocol/inventory/transaction/PackedItemUseLegacyInventoryTransaction.hpp"
#include "sculk/protocol/packet/IPacket.hpp"
#include "sculk/protocol/utility/math/Vec2.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"

namespace sculk::protocol::inline abi_v944 {

class PlayerAuthInputPacket : public IPacket {
public:
    Vec2                                    mPlayerRotation{};
    Vec3                                    mPosition{};
    Vec2                                    mMoveVector{};
    float                                   mPlayerHeadRotation{};
    std::bitset<65>                         mInputData{};
    std::uint32_t                           mInputType{};
    std::uint32_t                           mPlayMode{};
    std::uint32_t                           mNewInteractionModel{};
    Vec2                                    mInteractRotation{};
    std::uint64_t                           mClientTick{};
    Vec3                                    mPosDelta{};
    PackedItemUseLegacyInventoryTransaction mItemUseTransaction{};
    ItemStackRequestData                    mItemStackRequestData{};
    PlayerBlockActions                      mPlayerBlockActions{};
    Vec2                                    mVehicleRotation{};
    std::int64_t                            mClientPredictedVihicle{};
    Vec2                                    mAnologMoveVector{};
    Vec3                                    mCameraOrientation{};
    Vec2                                    mRawMoveVector{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
