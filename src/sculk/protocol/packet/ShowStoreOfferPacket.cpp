// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/ShowStoreOfferPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ShowStoreOfferPacket::getId() const noexcept { return MinecraftPacketIds::ShowStoreOffer; }

std::string_view ShowStoreOfferPacket::getName() const noexcept { return "ShowStoreOfferPacket"; }

void ShowStoreOfferPacket::write(BinaryStream& stream) const {
    stream.writeString(mProductUuid);
    stream.writeEnum(mRedirectType, &BinaryStream::writeByte);
}

Result<> ShowStoreOfferPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mProductUuid); !status) return status;
    return stream.readEnum(mRedirectType, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944
