// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <cstdint>

namespace sculk::protocol::inline abi_v944 {

enum class InventoryLeftTabIndex : std::int32_t {
    None               = 0,
    RecipeConstruction = 1,
    RecipeEquipment    = 2,
    RecipeItems        = 3,
    RecipeNature       = 4,
    RecipeSearch       = 5,
    Survival           = 6,
};

} // namespace sculk::protocol::inline abi_v944
