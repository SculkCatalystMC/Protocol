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

struct UUID {
    std::uint64_t mMostSignificantBits{};
    std::uint64_t mLeastSignificantBits{};

    void write(BinaryStream& stream) const {
        stream.writeUnsignedInt64(mMostSignificantBits);
        stream.writeUnsignedInt64(mLeastSignificantBits);
    }

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) {
        if (auto status = stream.readUnsignedInt64(mMostSignificantBits); !status) return status;
        return stream.readUnsignedInt64(mLeastSignificantBits);
    }
};

} // namespace sculk::protocol::inline abi_v944
