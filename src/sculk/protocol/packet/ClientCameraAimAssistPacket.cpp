// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/ClientCameraAimAssistPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ClientCameraAimAssistPacket::getId() const noexcept {
    return MinecraftPacketIds::ClientCameraAimAssist;
}

std::string_view ClientCameraAimAssistPacket::getName() const noexcept { return "ClientCameraAimAssistPacket"; }

void ClientCameraAimAssistPacket::write(BinaryStream& stream) const {
    stream.writeString(mPresetId);
    stream.writeEnum(mAction, &BinaryStream::writeByte);
    stream.writeBool(mAllowAimAssist);
}

Result<> ClientCameraAimAssistPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mPresetId); !status) return status;
    if (auto status = stream.readEnum(mAction, &ReadOnlyBinaryStream::readByte); !status) return status;
    return stream.readBool(mAllowAimAssist);
}

} // namespace sculk::protocol::inline abi_v944
