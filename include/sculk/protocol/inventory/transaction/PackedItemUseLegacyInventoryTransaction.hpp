// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/inventory/container/LegacySetItemSlot.hpp"
#include "sculk/protocol/inventory/transaction/InventoryTransactionAction.hpp"
#include "sculk/protocol/inventory/transaction/InventoryTransactionData.hpp"

namespace sculk::protocol::inline abi_v944 {

struct PackedItemUseLegacyInventoryTransaction {
    std::int32_t                   mLegacyRequestRawId{};
    std::vector<LegacySetItemSlot> mLegacySetItemSlots{};
    InventoryTransactionActions    mTransactionActions{};
    ItemUseInventoryTransaction    mItemUseTransaction{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
