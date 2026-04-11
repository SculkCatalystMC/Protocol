// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/inventory/item/NetworkItemStackDescriptor.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"

namespace sculk::protocol::inline abi_v944 {

class ItemReleaseInventoryTransaction {
public:
    enum class ActionType : std::uint32_t {
        Release = 0,
        Use     = 1,
    };

public:
    ActionType                 mActionType{};
    std::int32_t               mSlot{};
    NetworkItemStackDescriptor mItem{};
    Vec3                       mFromPos{};

public:
    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
