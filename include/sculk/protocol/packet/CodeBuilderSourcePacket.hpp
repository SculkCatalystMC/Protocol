// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/packet/IPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

class CodeBuilderSourcePacket : public IPacket {
public:
    enum class Operation : std::uint8_t {
        None  = 0,
        Get   = 1,
        Set   = 2,
        Reset = 3,
    };

    enum class Category : std::uint8_t {
        None          = 0,
        CodeStatus    = 1,
        Instantiation = 2,
    };

    enum class CodeStatus : std::uint8_t {
        None       = 0,
        NotStarted = 1,
        InProgress = 2,
        Paused     = 3,
        Error      = 4,
        Succeeded  = 5,
    };

public:
    Operation  mOperation{};
    Category   mCategory{};
    CodeStatus mCodeStatus{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
