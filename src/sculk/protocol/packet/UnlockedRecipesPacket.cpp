// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/UnlockedRecipesPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds UnlockedRecipesPacket::getId() const noexcept { return MinecraftPacketIds::UnlockedRecipes; }

std::string_view UnlockedRecipesPacket::getName() const noexcept { return "UnlockedRecipesPacket"; }

void UnlockedRecipesPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mPacketType, &BinaryStream::writeUnsignedInt);
    stream.writeArray(mUnlockedRecipesList, &BinaryStream::writeString);
}

Result<> UnlockedRecipesPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mPacketType, &ReadOnlyBinaryStream::readUnsignedInt); !status) return status;
    return stream.readArray(mUnlockedRecipesList, &ReadOnlyBinaryStream::readString);
}

} // namespace sculk::protocol::inline abi_v944
