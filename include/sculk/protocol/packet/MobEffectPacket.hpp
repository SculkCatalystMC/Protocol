// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/packet/IPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

class MobEffectPacket : public IPacket {
public:
    enum class Event : std::uint8_t {
        Invalid = 0,
        Add     = 1,
        Update  = 2,
        Remove  = 3,
    };

public:
    std::uint64_t mActorRuntimeId{};
    Event         mEventId{};
    std::int32_t  mEffectId{};
    std::int32_t  mEffectAmplifier{};
    bool          mShowParticles{};
    std::int32_t  mEffectDurationTicks{};
    std::uint64_t mTick{};
    bool          mAmbient{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
