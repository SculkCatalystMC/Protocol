// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/IPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

void IPacket::writeWithHeader(BinaryStream& stream) const {
    writeHeader(stream);
    write(stream);
}

void IPacket::writeHeader(BinaryStream& stream) const {
    stream.writeUnsignedVarInt(
        static_cast<std::uint32_t>(
            (static_cast<std::int32_t>(getId()) & 0x3FF) | ((mSenderSubClientId & 3) << 10)
            | ((mTargetSubClientId & 3) << 12)
        )
    );
}

Result<> IPacket::readWithHeader(ReadOnlyBinaryStream& stream) {
    if (auto status = readHeader(stream); !status) {
        return status;
    }
    return read(stream);
}

Result<> IPacket::readHeader(ReadOnlyBinaryStream& stream) {
    std::uint32_t header{};
    if (auto status = stream.readUnsignedVarInt(header); !status) return status;
    mSenderSubClientId = (header >> 10) & 3;
    mTargetSubClientId = (header >> 12) & 3;
    return {};
}

} // namespace sculk::protocol::inline abi_v944
