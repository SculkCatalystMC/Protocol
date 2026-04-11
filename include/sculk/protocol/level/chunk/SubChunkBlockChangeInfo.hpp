// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/level/block/BlockPos.hpp"

namespace sculk::protocol::inline abi_v944 {

struct SubChunkBlockChangeInfo {
    BlockPos      mPosition{};
    std::uint32_t mRuntimeId{};
    std::uint32_t mFlags{};
    std::uint64_t mSyncEntity{};
    std::uint32_t mSyncMessage{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
