// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <cstdint>

namespace sculk::protocol::inline abi_v944 {

enum class POIBlockInteractionType : std::uint32_t {
    None                = 0,
    Extend              = 1,
    Clone               = 2,
    Lock                = 3,
    Create              = 4,
    CreateLocator       = 5,
    Rename              = 6,
    ItemPlaced          = 7,
    ItemRemoved         = 8,
    Cooking             = 9,
    Dousing             = 10,
    Lighting            = 11,
    Haystack            = 12,
    Filled              = 13,
    Emptied             = 14,
    AddDye              = 15,
    DyeItem             = 16,
    ClearItem           = 17,
    EnchantArrow        = 18,
    CompostItemPlaced   = 19,
    RecoveredBonemeal   = 20,
    BookPlaced          = 21,
    BookOpened          = 22,
    Disenchant          = 23,
    Repair              = 24,
    DisenchantAndRepair = 25
};

} // namespace sculk::protocol::inline abi_v944
