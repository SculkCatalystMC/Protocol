// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "BiomeWeightedData.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"
#include <cstdint>
#include <vector>

namespace sculk::protocol::inline abi_v944 {

struct BiomeConditionalTransformationData {
    std::vector<BiomeWeightedData> mTransformsInto{};
    std::int16_t                   mConditionJSON{};
    std::uint32_t                  mMinPassingNeighbors{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
