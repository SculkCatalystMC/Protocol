// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/CameraShakePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds CameraShakePacket::getId() const noexcept { return MinecraftPacketIds::CameraShake; }

std::string_view CameraShakePacket::getName() const noexcept { return "CameraShakePacket"; }

void CameraShakePacket::write(BinaryStream& stream) const {
    stream.writeFloat(mIntensity);
    stream.writeFloat(mSeconds);
    stream.writeEnum(mType, &BinaryStream::writeByte);
    stream.writeEnum(mAction, &BinaryStream::writeByte);
}

Result<> CameraShakePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mIntensity); !status) return status;
    if (auto status = stream.readFloat(mSeconds); !status) return status;
    if (auto status = stream.readEnum(mType, &ReadOnlyBinaryStream::readByte); !status) return status;
    return stream.readEnum(mAction, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944
