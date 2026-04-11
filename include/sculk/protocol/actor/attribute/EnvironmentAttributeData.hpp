// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "AttributeData.hpp"
#include "EasingFunction.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"

namespace sculk::protocol::inline abi_v944 {

struct EnvironmentAttributeData {
    std::string                  mAttributeName{};
    std::optional<AttributeData> mFromAttribute{};
    AttributeData                mAttribute{};
    std::optional<AttributeData> mToAttribute{};
    std::uint32_t                mCurrentTransitionTicks{};
    std::uint32_t                mTotalTransitionTicks{};
    EasingFunction               mEasing{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
