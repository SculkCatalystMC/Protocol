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

enum class BoolAttributeOperation : std::int32_t {
    Override   = 0,
    AlphaBlend = 1,
    And        = 2,
    Nand       = 3,
    Or         = 4,
    Nor        = 5,
    Xor        = 6,
    Xnor       = 7,
};

struct BoolAttributeData {
    bool                   mValue{};
    BoolAttributeOperation mOperation{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
