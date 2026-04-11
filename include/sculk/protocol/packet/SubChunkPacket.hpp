// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/level/chunk/SubChunkPos.hpp"
#include "sculk/protocol/packet/IPacket.hpp"
#include <array>

namespace sculk::protocol::inline abi_v944 {

class SubChunkPacket : public IPacket {
public:
    enum class HeightMapDataType : std::uint8_t {
        NoData     = 0,
        HasData    = 1,
        AllTooHigh = 2,
        AllTooLow  = 3,
        AllCopied  = 4,
    };

    enum class SubChunkRequestResult : std::uint8_t {
        Undefined             = 0,
        Success               = 1,
        LevelChunkDoesntExist = 2,
        WrongDimension        = 3,
        PlayerDoesntExist     = 4,
        IndexOutOfBounds      = 5,
        SuccessAllAir         = 6,
    };

    struct SubChunkPosOffset {
        std::int8_t mX{};
        std::int8_t mY{};
        std::int8_t mZ{};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

    struct HeightmapData {
        HeightMapDataType                           mHeightMapType{};
        std::array<std::array<std::int8_t, 16>, 16> mSubchunkHeightMap{};
        HeightMapDataType                           mRenderHeightMapType{};
        std::array<std::array<std::int8_t, 16>, 16> mRenderHeightMap{};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

    struct SubChunkPacketData {
        SubChunkPosOffset     mSubChunkPosOffset{};
        std::string           mSerializedSubChunk{};
        SubChunkRequestResult mResult{};
        HeightmapData         mHeightMapData{};
        std::uint64_t         mBlobId{};

        void write(BinaryStream& stream, bool cacheEnabled) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream, bool cacheEnabled);
    };

public:
    bool                            mCacheEnabled{false};
    std::int32_t                    mDimensionType{};
    std::vector<SubChunkPacketData> mSubChunkData{};
    SubChunkPos                     mCenterPos{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
