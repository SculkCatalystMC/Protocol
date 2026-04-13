// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/NpcDialoguePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds NpcDialoguePacket::getId() const noexcept { return MinecraftPacketIds::NpcDialogue; }

std::string_view NpcDialoguePacket::getName() const noexcept { return "NpcDialoguePacket"; }

void NpcDialoguePacket::write(BinaryStream& stream) const {
    stream.writeUnsignedInt64(mNpcId);
    stream.writeEnum(mActionType, &BinaryStream::writeVarInt);
    stream.writeString(mDialogue);
    stream.writeString(mSceneName);
    stream.writeString(mNpcName);
    stream.writeString(mActionJSON);
}

Result<> NpcDialoguePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedInt64(mNpcId); !status) return status;
    if (auto status = stream.readEnum(mActionType, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readString(mDialogue); !status) return status;
    if (auto status = stream.readString(mSceneName); !status) return status;
    if (auto status = stream.readString(mNpcName); !status) return status;
    return stream.readString(mActionJSON);
}

} // namespace sculk::protocol::inline abi_v944
