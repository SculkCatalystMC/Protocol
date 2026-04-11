// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "CompoundTag.hpp"
#include "ListTag.hpp"
#include "TagType.hpp"
#include "ValueArrayTag.hpp"
#include "ValueTag.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"
#include <variant>

namespace sculk::protocol::inline abi_v944 {

struct TagVariant {
    using VariantType = std::variant<
        EndTag,
        ByteTag,
        ShortTag,
        IntTag,
        LongTag,
        FloatTag,
        DoubleTag,
        ByteArrayTag,
        StringTag,
        ListTag,
        CompoundTag,
        IntArrayTag>;

    VariantType mValue{};

    void serialize(BinaryStream& stream) const;

    [[nodiscard]] Result<> deserialize(ReadOnlyBinaryStream& stream);

    TagVariant& emplace(TagType type);

    [[nodiscard]] TagType getType() const noexcept;
};

} // namespace sculk::protocol::inline abi_v944
