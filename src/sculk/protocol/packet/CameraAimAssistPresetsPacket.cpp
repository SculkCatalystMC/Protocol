// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/CameraAimAssistPresetsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds CameraAimAssistPresetsPacket::getId() const noexcept {
    return MinecraftPacketIds::CameraAimAssistPresets;
}

std::string_view CameraAimAssistPresetsPacket::getName() const noexcept { return "CameraAimAssistPresetsPacket"; }

void CameraAimAssistPresetsPacket::write(BinaryStream& stream) const {
    stream.writeArray(mCatagory, &CameraAimAssistCategoryDefinition::write);
    stream.writeArray(mPreset, &CameraAimAssistPresetDefinition::write);
    stream.writeEnum(mOperation, &BinaryStream::writeByte);
}

Result<> CameraAimAssistPresetsPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readArray(mCatagory, &CameraAimAssistCategoryDefinition::read); !status) return status;
    if (auto status = stream.readArray(mPreset, &CameraAimAssistPresetDefinition::read); !status) return status;
    return stream.readEnum(mOperation, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944
