// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/packet/IPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

class NpcDialoguePacket : public IPacket {
public:
    enum class ActionType : std::int32_t {
        Open  = 0,
        Close = 1,
    };

public:
    std::uint64_t mNpcId{};
    ActionType    mActionType{};
    std::string   mDialogue{};
    std::string   mSceneName{};
    std::string   mNpcName{};
    std::string   mActionJSON{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
