// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "MinecraftPacketIds.hpp"
#include "packet/IPacket.hpp"
#include "utility/deps/BinaryStream.hpp"
#include "utility/deps/ReadOnlyBinaryStream.hpp"
#include <memory>

namespace sculk::protocol::inline abi_v944 {

class MinecraftPackets {
public:
    struct PacketHeader {
        MinecraftPacketIds mPacketId{};
        std::uint8_t       mSenderSubClientId{};
        std::uint8_t       mTargetSubClientId{};
    };

public:
    [[nodiscard]] static std::unique_ptr<IPacket> createPacket(MinecraftPacketIds packetId);

    [[nodiscard]] static std::unique_ptr<IPacket> createPacket(const PacketHeader& header);

    [[nodiscard]] static std::unique_ptr<IPacket> readAndCreatePacketFromStream(ReadOnlyBinaryStream& stream);

    [[nodiscard]] static PacketHeader readPacketHeader(ReadOnlyBinaryStream& stream);

    static void writePacketHeader(BinaryStream& stream, const PacketHeader& header);
};

} // namespace sculk::protocol::inline abi_v944
