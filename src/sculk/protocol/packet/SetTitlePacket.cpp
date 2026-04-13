// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/SetTitlePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds SetTitlePacket::getId() const noexcept { return MinecraftPacketIds::SetTitle; }

std::string_view SetTitlePacket::getName() const noexcept { return "SetTitlePacket"; }

void SetTitlePacket::write(BinaryStream& stream) const {
    stream.writeEnum(mTitleType, &BinaryStream::writeVarInt);
    stream.writeString(mTitleText);
    stream.writeVarInt(mFadeInTime);
    stream.writeVarInt(mStayTime);
    stream.writeVarInt(mFadeOutTime);
    stream.writeString(mXuid);
    stream.writeString(mPlatformId);
    stream.writeString(mFilteredMessage);
}

Result<> SetTitlePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mTitleType, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readString(mTitleText); !status) return status;
    if (auto status = stream.readVarInt(mFadeInTime); !status) return status;
    if (auto status = stream.readVarInt(mStayTime); !status) return status;
    if (auto status = stream.readVarInt(mFadeOutTime); !status) return status;
    if (auto status = stream.readString(mXuid); !status) return status;
    if (auto status = stream.readString(mPlatformId); !status) return status;
    return stream.readString(mFilteredMessage);
}

} // namespace sculk::protocol::inline abi_v944
