// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/SetDisplayObjectivePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds SetDisplayObjectivePacket::getId() const noexcept { return MinecraftPacketIds::SetDisplayObjective; }

std::string_view SetDisplayObjectivePacket::getName() const noexcept { return "SetDisplayObjectivePacket"; }

void SetDisplayObjectivePacket::write(BinaryStream& stream) const {
    stream.writeString(mDisplaySlotName);
    stream.writeString(mObjectiveName);
    stream.writeString(mObjectiveDisplayName);
    stream.writeString(mCriteriaName);
    stream.writeEnum(mSortOrder, &BinaryStream::writeVarInt);
}

Result<> SetDisplayObjectivePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mDisplaySlotName); !status) return status;
    if (auto status = stream.readString(mObjectiveName); !status) return status;
    if (auto status = stream.readString(mObjectiveDisplayName); !status) return status;
    if (auto status = stream.readString(mCriteriaName); !status) return status;
    return stream.readEnum(mSortOrder, &ReadOnlyBinaryStream::readVarInt);
}

} // namespace sculk::protocol::inline abi_v944
