// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "BiomeCappedSurfaceData.hpp"
#include "BiomeClimateData.hpp"
#include "BiomeConsolidatedFeaturesData.hpp"
#include "BiomeLegacyWorldGenRulesData.hpp"
#include "BiomeMesaSurfaceData.hpp"
#include "BiomeMountainParamsData.hpp"
#include "BiomeMultinoiseGenRulesData.hpp"
#include "BiomeOverworldGenRulesData.hpp"
#include "BiomeReplacementData.hpp"
#include "BiomeSurfaceMaterialAdjustmentData.hpp"
#include "BiomeSurfaceMaterialData.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"

namespace sculk::protocol::inline abi_v944 {

struct BiomeDefinitionChunkGenData {
    std::optional<BiomeClimateData>                   mClimate{};
    std::optional<BiomeConsolidatedFeaturesData>      mConsolidatedFeatures{};
    std::optional<BiomeMountainParamsData>            mMountainParams{};
    std::optional<BiomeSurfaceMaterialAdjustmentData> mSurfaceMaterialAdjustments{};
    std::optional<BiomeSurfaceMaterialData>           mSurfaceMaterials{};
    bool                                              mHasDefaultOverworldSurface{};
    bool                                              mHasSwampSurface{};
    bool                                              mHasFrozenOceanSurface{};
    bool                                              mHasTheEndSurface{};
    std::optional<BiomeMesaSurfaceData>               mMesaSurface{};
    std::optional<BiomeCappedSurfaceData>             mCappedSurface{};
    std::optional<BiomeOverworldGenRulesData>         mOverworldGenRules{};
    std::optional<BiomeMultinoiseGenRulesData>        mMultinoiseGenRules{};
    std::optional<BiomeLegacyWorldGenRulesData>       mLegacyWorldGenRules{};
    std::optional<BiomeReplacementData>               mBiomeReplacementData{};
    std::optional<std::uint8_t>                       mVillageType{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
