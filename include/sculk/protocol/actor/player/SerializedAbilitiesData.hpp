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

struct SerializedAbilitiesData {
    struct SerializedLayer {
        std::uint16_t mLayer{};
        std::uint32_t mAbilitiesSet{};
        std::uint32_t mAbilitiesValue{};
        float         mFlySpeed{};
        float         mVerticalFlySpeed{};
        float         mWalkSpeed{};
    };

    std::int64_t                 mPlayerRawId{};
    std::uint8_t                 mPlayerPermission{};
    std::uint8_t                 mCommandPermission{};
    std::vector<SerializedLayer> mLayers{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
