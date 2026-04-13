// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/PlayerSkinPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PlayerSkinPacket::getId() const noexcept { return MinecraftPacketIds::PlayerSkin; }

std::string_view PlayerSkinPacket::getName() const noexcept { return "PlayerSkinPacket"; }

void PlayerSkinPacket::write(BinaryStream& stream) const {
    mUUID.write(stream);
    mSerializedSkin.write(stream);
    stream.writeString(mNewSkinName);
    stream.writeString(mOldSkinName);
}

Result<> PlayerSkinPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mUUID.read(stream); !status) return status;
    if (auto status = mSerializedSkin.read(stream); !status) return status;
    if (auto status = stream.readString(mNewSkinName); !status) return status;
    return stream.readString(mOldSkinName);
}

} // namespace sculk::protocol::inline abi_v944
