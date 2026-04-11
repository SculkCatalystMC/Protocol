// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/actor/player/UUID.hpp"

namespace sculk::protocol::inline abi_v944 {

struct GatheringsConfigurationJoinInfo {
    UUID        mExperienceId{};
    std::string mExperienceName{};
    UUID        mExperienceWorldId{};
    std::string mExperienceWorldName{};
    std::string mCreatorId{};
    UUID        mTargetId{};
    std::string mScenarioId{};
    std::string mServerId{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct GatheringsConfigurationClientStoreEntryPointInfo {
    std::string mStoreId{};
    std::string mStoreName{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct GatheringsConfigurationPresenceInfo {
    std::string mExperienceName{};
    std::string mWorldName{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct ServerConfigurationJoinInfo {
    std::optional<GatheringsConfigurationJoinInfo>                  mGatheringsConfiguration{};
    std::optional<GatheringsConfigurationClientStoreEntryPointInfo> mStoreEntryPointInfo{};
    std::optional<GatheringsConfigurationPresenceInfo>              mPresenceInfo{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
