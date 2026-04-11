// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/MinecraftPacketIds.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"

namespace sculk::protocol::inline abi_v944 {

class IPacket {
public:
    std::uint8_t mSenderSubClientId{};
    std::uint8_t mTargetSubClientId{};

public:
    IPacket() noexcept = default;

public:
    virtual ~IPacket() noexcept = default;

    [[nodiscard]] virtual MinecraftPacketIds getId() const noexcept = 0;

    [[nodiscard]] virtual std::string_view getName() const noexcept = 0;

    virtual void write(BinaryStream& stream) const = 0;

    [[nodiscard]] virtual Result<> read(ReadOnlyBinaryStream& stream) = 0;

    void writeHeader(BinaryStream& stream) const;

    [[nodiscard]] Result<> readHeader(ReadOnlyBinaryStream& stream);

    void writeWithHeader(BinaryStream& stream) const;

    [[nodiscard]] Result<> readNoHeader(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
