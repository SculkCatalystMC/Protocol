// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "TagType.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"
#include <vector>

namespace sculk::protocol::inline abi_v944 {

struct TagVariant;
struct ListTag {
    TagType                 mType{};
    std::vector<TagVariant> mValue{};

    void serialize(BinaryStream& stream) const;

    [[nodiscard]] Result<> deserialize(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
