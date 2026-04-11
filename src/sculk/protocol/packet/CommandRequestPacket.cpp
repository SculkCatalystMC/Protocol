// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/CommandRequestPacket.hpp"
#include "../utility/EnumName.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds CommandRequestPacket::getId() const noexcept { return MinecraftPacketIds::CommandRequest; }

std::string_view CommandRequestPacket::getName() const noexcept { return "CommandRequestPacket"; }

void CommandRequestPacket::write(BinaryStream& stream) const {
    stream.writeString(mCommand);
    mOriginData.write(stream);
    stream.writeBool(mIsInternal);
    utils::writeEnumName(stream, mVersion);
}

Result<> CommandRequestPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mCommand); !status) return status;
    if (auto status = mOriginData.read(stream); !status) return status;
    if (auto status = stream.readBool(mIsInternal); !status) return status;
    return utils::readEnumName(stream, mVersion);
}

} // namespace sculk::protocol::inline abi_v944
