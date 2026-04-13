// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/ClientboundDebugRendererPacket.hpp"
#include "../utility/EnumName.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ClientboundDebugRendererPacket::getId() const noexcept {
    return MinecraftPacketIds::ClientboundDebugRenderer;
}

std::string_view ClientboundDebugRendererPacket::getName() const noexcept { return "ClientboundDebugRendererPacket"; }

void ClientboundDebugRendererPacket::write(BinaryStream& stream) const {
    utils::writeEnumName(stream, mType);
    if (mType == Type::AddDebugMarkerCube) {
        stream.writeString(mText);
        mPosition.write(stream);
        stream.writeSignedInt(mColor);
        stream.writeUnsignedInt64(mDurationMilliseconds);
    }
}

Result<> ClientboundDebugRendererPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = utils::readEnumName(stream, mType); !status) return status;
    if (mType == Type::AddDebugMarkerCube) {
        if (auto status = stream.readString(mText); !status) return status;
        if (auto status = mPosition.read(stream); !status) return status;
        if (auto status = stream.readSignedInt(mColor); !status) return status;
        return stream.readUnsignedInt64(mDurationMilliseconds);
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
