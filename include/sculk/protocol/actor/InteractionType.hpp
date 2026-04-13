// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <cstdint>

namespace sculk::protocol::inline abi_v944 {

enum class InteractionType : std::uint32_t {
    Breeding   = 1,
    Taming     = 2,
    Curing     = 3,
    Crafted    = 4,
    Shearing   = 5,
    Milking    = 6,
    Trading    = 7,
    Feeding    = 8,
    Igniting   = 9,
    Coloring   = 10,
    Naming     = 11,
    Leashing   = 12,
    Unleashing = 13,
    PetSleep   = 14,
    Trusting   = 15,
    Commanding = 16
};

} // namespace sculk::protocol::inline abi_v944
