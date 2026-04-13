// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/CameraAimAssistPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds CameraAimAssistPacket::getId() const noexcept { return MinecraftPacketIds::CameraAimAssist; }

std::string_view CameraAimAssistPacket::getName() const noexcept { return "CameraAimAssistPacket"; }

void CameraAimAssistPacket::write(BinaryStream& stream) const {
    stream.writeString(mPresetId);
    mViewAngle.write(stream);
    stream.writeFloat(mDistance);
    stream.writeEnum(mTargetMode, &BinaryStream::writeByte);
    stream.writeEnum(mAction, &BinaryStream::writeByte);
    stream.writeBool(mShowDebugRender);
}

Result<> CameraAimAssistPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mPresetId); !status) return status;
    if (auto status = mViewAngle.read(stream); !status) return status;
    if (auto status = stream.readFloat(mDistance); !status) return status;
    if (auto status = stream.readEnum(mTargetMode, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readEnum(mAction, &ReadOnlyBinaryStream::readByte); !status) return status;
    return stream.readBool(mShowDebugRender);
}

} // namespace sculk::protocol::inline abi_v944
