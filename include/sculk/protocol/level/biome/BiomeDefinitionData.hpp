// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "BiomeDefinitionChunkGenData.hpp"
#include "BiomeTagsData.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"

namespace sculk::protocol::inline abi_v944 {

struct BiomeDefinitionData {
    std::int16_t                               mBiomeId{};
    float                                      mTemperature{};
    float                                      mDownfall{};
    float                                      mFoliageSnow{};
    float                                      mDepth{};
    float                                      mScale{};
    std::int32_t                               mMapWaterColorARGB{};
    bool                                       mRain{};
    std::optional<BiomeTagsData>               mTags{};
    std::optional<BiomeDefinitionChunkGenData> mChunkGenData{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
