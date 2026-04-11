// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/actor/player/UUID.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"
#include <optional>

namespace sculk::protocol::inline abi_v944 {

enum class LocatorBarAction : std::uint8_t {
    None   = 0,
    Add    = 1,
    Remove = 2,
    Update = 3,
};

struct LocatorBarWorldPosition {
    Vec3         mPosition{};
    std::int32_t mDimensionType{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct LocatorBarWaypointHandle {
    UUID mUUID{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct LocatorBarServerWaypointPayload {
    std::uint32_t                          mUpdateFlag{};
    std::optional<bool>                    mIsVisible{};
    std::optional<LocatorBarWorldPosition> mWorldPosition{};
    std::optional<std::uint32_t>           mTextureId{};
    std::optional<std::int32_t>            mColor{};
    std::optional<bool>                    mClientPositionAuthority{};
    std::optional<std::int64_t>            mActorUniqueId{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct LocatorBarWaypointPayload {
    LocatorBarWaypointHandle        mGroupHandle{};
    LocatorBarServerWaypointPayload mServerWaypointPayload{};
    LocatorBarAction                mActionFlag{LocatorBarAction::None};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
