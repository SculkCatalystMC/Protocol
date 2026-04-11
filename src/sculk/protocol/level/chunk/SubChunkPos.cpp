// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/level/chunk/SubChunkPos.hpp"

namespace sculk::protocol::inline abi_v944 {

void SubChunkPos::write(BinaryStream& stream) const {
    stream.writeVarInt(mX);
    stream.writeVarInt(mY);
    stream.writeVarInt(mZ);
}

Result<> SubChunkPos::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mX); !status) return status;
    if (auto status = stream.readVarInt(mY); !status) return status;
    return stream.readVarInt(mZ);
}

} // namespace sculk::protocol::inline abi_v944
