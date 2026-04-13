// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <cstdint>

namespace sculk::protocol::inline abi_v944 {

enum class ActorDamageCause : std::int32_t {
    Override        = 0,
    Contact         = 1,
    EntityAttack    = 2,
    Projectile      = 3,
    Suffocation     = 4,
    Fall            = 5,
    Fire            = 6,
    FireTick        = 7,
    Lava            = 8,
    Drowning        = 9,
    BlockExplosion  = 10,
    EntityExplosion = 11,
    Void            = 12,
    SelfDestruct    = 13,
    Magic           = 14,
    Wither          = 15,
    Starve          = 16,
    Anvil           = 17,
    Thorns          = 18,
    FallingBlock    = 19,
    Piston          = 20,
    FlyIntoWall     = 21,
    Magma           = 22,
    Fireworks       = 23,
    Lightning       = 24,
    Charging        = 25,
    Temperature     = 26,
    Freezing        = 27,
    Stalactite      = 28,
    Stalagmite      = 29,
    RamAttack       = 30,
    SonicBoom       = 31,
    Campfire        = 32,
    SoulCampfire    = 33,
    MaceSmash       = 34
};

} // namespace sculk::protocol::inline abi_v944
