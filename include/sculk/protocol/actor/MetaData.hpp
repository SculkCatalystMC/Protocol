// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/actor/ActorDataIDs.hpp"
#include "sculk/protocol/level/block/BlockPos.hpp"
#include "sculk/protocol/nbt/TagVariant.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"
#include <variant>

namespace sculk::protocol::inline abi_v944 {

class MetaData {
public:
    using DataItemVariant = std::variant<uint8_t, short, int, float, std::string, CompoundTag, BlockPos, int64_t, Vec3>;

    enum class DataItemType {
        Byte        = 0,
        Short       = 1,
        Int         = 2,
        Float       = 3,
        String      = 4,
        CompoundTag = 5,
        Pos         = 6,
        Int64       = 7,
        Vec3        = 8,
        Unknown     = 9,
    };

    struct DataItem {
        ActorDataIDs    mId{};
        DataItemVariant mData{};
    };

public:
    std::vector<DataItem> mDataItems{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};


} // namespace sculk::protocol::inline abi_v944
