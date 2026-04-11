// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "BiomeSurfaceMaterialData.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"

namespace sculk::protocol::inline abi_v944 {

struct BiomeElementData {
    float                    mNoiseFrequencyScale{};
    float                    mNoiseLowerBound{};
    float                    mNoiseUpperBound{};
    std::int32_t             mHeightMinType{};
    std::int16_t             mHeightMin{};
    std::int32_t             mHeightMaxType{};
    std::int16_t             mHeightMax{};
    BiomeSurfaceMaterialData mAdjustedMaterials{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
