// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/packet/IPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

class ResourcePackDataInfoPacket : public IPacket {
public:
    enum class PackType : std::uint8_t {
        Invalid       = 0,
        Addon         = 1,
        Cached        = 2,
        CopyProtected = 3,
        Behavior      = 4,
        PersonaPiece  = 5,
        Resources     = 6,
        Skins         = 7,
        WorldTemplate = 8,
    };

public:
    std::string   mResourceName{};
    std::uint32_t mChunkSize{};
    std::uint32_t mChunkIndex{};
    std::uint64_t mFileSize{};
    std::string   mFileHash{};
    bool          mIsPremiumPack{};
    PackType      mPackType{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
