// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "BiomeCoordinateData.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"

namespace sculk::protocol::inline abi_v944 {

struct BiomeScatterParamData {
    std::vector<BiomeCoordinateData> mCoordinate{};
    std::int32_t                     mEvalOrder{};
    std::int32_t                     mChancePercentType{};
    std::int16_t                     mChancePercent{};
    std::int32_t                     mChanceNumeartor{};
    std::int32_t                     mChanceDenominator{};
    std::int32_t                     mIterationsType{};
    std::int16_t                     mIterations{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
