// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"

namespace sculk::protocol::inline abi_v944 {

enum class EasingFunction : std::int32_t {
    Linear       = 0,
    Spring       = 1,
    InQuad       = 2,
    OutQuad      = 3,
    InOutQuad    = 4,
    InCubic      = 5,
    OutCubic     = 6,
    InOutCubic   = 7,
    InQuart      = 8,
    OutQuart     = 9,
    InOutQuart   = 10,
    InQuint      = 11,
    OutQuint     = 12,
    InOutQuint   = 13,
    InSine       = 14,
    OutSine      = 15,
    InOutSine    = 16,
    InExpo       = 17,
    OutExpo      = 18,
    InOutExpo    = 19,
    InCirc       = 20,
    OutCirc      = 21,
    InOutCirc    = 22,
    InBounce     = 23,
    OutBounce    = 24,
    InOutBounce  = 25,
    InBack       = 26,
    OutBack      = 27,
    InOutBack    = 28,
    InElastic    = 29,
    OutElastic   = 30,
    InOutElastic = 31,
};

} // namespace sculk::protocol::inline abi_v944