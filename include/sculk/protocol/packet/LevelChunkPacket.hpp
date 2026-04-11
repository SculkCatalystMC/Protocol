// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/level/chunk/ChunkPos.hpp"
#include "sculk/protocol/packet/IPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

class LevelChunkPacket : public IPacket {
public:
    ChunkPos                   mPosition{};
    std::int32_t               mDimensionId{};
    bool                       mCacheEnabled{false};
    bool                       mIsChunkInTickRange{false};
    std::string                mSerializedChunk{};
    std::uint32_t              mSubChunksCount{};
    bool                       mIsClientPacket{false};
    bool                       mClientNeedsToRequestSubchunks{false};
    std::int16_t               mClientRequestSubChunkLimit{};
    std::vector<std::uint64_t> mCacheBlobs{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
