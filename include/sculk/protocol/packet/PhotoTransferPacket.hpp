// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/packet/IPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

class PhotoTransferPacket : public IPacket {
public:
    enum class PhotoType : std::uint8_t {
        Portfolio = 0,
        PhotoItem = 1,
        Book      = 2,
    };

public:
    std::string  mPhotoName{};
    std::string  mPhotoData{};
    std::string  mBookId{};
    PhotoType    mType{};
    PhotoType    mSourceType{};
    std::int64_t mOwnerId{};
    std::string  mNewPhotoName{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
