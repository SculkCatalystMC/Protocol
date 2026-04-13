// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/LessonProgressPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds LessonProgressPacket::getId() const noexcept { return MinecraftPacketIds::LessonProgress; }

std::string_view LessonProgressPacket::getName() const noexcept { return "LessonProgressPacket"; }

void LessonProgressPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mAction, &BinaryStream::writeVarInt);
    stream.writeVarInt(mScore);
    stream.writeString(mActivityId);
}

Result<> LessonProgressPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mAction, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readVarInt(mScore); !status) return status;
    return stream.readString(mActivityId);
}

} // namespace sculk::protocol::inline abi_v944
