// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"
#include <cstdint>
#include <optional>
#include <vector>

namespace sculk::protocol::inline abi_v944 {

struct BiomeCappedSurfaceData {
    std::vector<std::int32_t>    mFloorBlocks{};
    std::vector<std::int32_t>    mCeilingBlocks{};
    std::optional<std::uint32_t> mSeaBlock{};
    std::optional<std::uint32_t> mFoundationBlock{};
    std::optional<std::uint32_t> mBeachBlock{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
