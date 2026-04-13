// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/inventory/InventoryLayout.hpp"
#include "sculk/protocol/inventory/InventoryLeftTabIndex.hpp"
#include "sculk/protocol/inventory/InventoryRightTabIndex.hpp"
#include "sculk/protocol/packet/IPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

class SetPlayerInventoryOptionsPacket : public IPacket {
public:
    InventoryLeftTabIndex  mLeftInventoryTab{};
    InventoryRightTabIndex mRightInventoryTab{};
    bool                   mFiltering{};
    InventoryLayout        mLayoutInventory{};
    InventoryLayout        mLayoutCraft{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
