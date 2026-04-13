// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/packet/IPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

class SetTitlePacket : public IPacket {
public:
    enum class TitleType : std::int32_t {
        Clear               = 0,
        Reset               = 1,
        Title               = 2,
        Subtitle            = 3,
        Actionbar           = 4,
        Times               = 5,
        TitleTextObject     = 6,
        SubtitleTextObject  = 7,
        ActionbarTextObject = 8
    };

public:
    TitleType    mTitleType{};
    std::string  mTitleText{};
    std::int32_t mFadeInTime{};
    std::int32_t mStayTime{};
    std::int32_t mFadeOutTime{};
    std::string  mXuid{};
    std::string  mPlatformId{};
    std::string  mFilteredMessage{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
