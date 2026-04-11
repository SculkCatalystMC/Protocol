// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "BiomeConditionalTransformationData.hpp"
#include "BiomeWeightedData.hpp"
#include "BiomeWeightedTemperatureData.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"

namespace sculk::protocol::inline abi_v944 {

struct BiomeOverworldGenRulesData {
    std::vector<BiomeWeightedData>                  mHillsTransformations{};
    std::vector<BiomeWeightedData>                  mMutateTransformations{};
    std::vector<BiomeWeightedData>                  mRiverTransformations{};
    std::vector<BiomeWeightedData>                  mShoreTransformations{};
    std::vector<BiomeConditionalTransformationData> mPreHillsEdge{};
    std::vector<BiomeConditionalTransformationData> mPreShoreEdge{};
    std::vector<BiomeWeightedTemperatureData>       mClimate{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
