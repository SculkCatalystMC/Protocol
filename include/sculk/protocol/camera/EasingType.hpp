// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <cstdint>

namespace sculk::protocol::inline abi_v944 {

enum class EasingType : std::uint8_t {
    LINEAR         = 0,
    SPRING         = 1,
    IN_QUAD        = 2,
    OUT_QUAD       = 3,
    IN_OUT_QUAD    = 4,
    IN_CUBIC       = 5,
    OUT_CUBIC      = 6,
    IN_OUT_CUBIC   = 7,
    IN_QUART       = 8,
    OUT_QUART      = 9,
    IN_OUT_QUART   = 10,
    IN_QUINT       = 11,
    OUT_QUINT      = 12,
    IN_OUT_QUINT   = 13,
    IN_SINE        = 14,
    OUT_SINE       = 15,
    IN_OUT_SINE    = 16,
    IN_EXPO        = 17,
    OUT_EXPO       = 18,
    IN_OUT_EXPO    = 19,
    IN_CIRC        = 20,
    OUT_CIRC       = 21,
    IN_OUT_CIRC    = 22,
    IN_BOUNCE      = 23,
    OUT_BOUNCE     = 24,
    IN_OUT_BOUNCE  = 25,
    IN_BACK        = 26,
    OUT_BACK       = 27,
    IN_OUT_BACK    = 28,
    IN_ELASTIC     = 29,
    OUT_ELASTIC    = 30,
    IN_OUT_ELASTIC = 31
};

} // namespace sculk::protocol::inline abi_v944
