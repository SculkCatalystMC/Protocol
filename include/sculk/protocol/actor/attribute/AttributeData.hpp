// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/actor/attribute/BoolAttributeData.hpp"
#include "sculk/protocol/actor/attribute/ColorAttributeData.hpp"
#include "sculk/protocol/actor/attribute/FloatAttributeData.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"
#include <variant>

namespace sculk::protocol::inline abi_v944 {

struct AttributeData {
    std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> mData{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
