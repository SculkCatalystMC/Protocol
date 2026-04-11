// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/level/ServerConfiguration.hpp"

namespace sculk::protocol::inline abi_v944 {

void GatheringsConfigurationJoinInfo::write(BinaryStream& stream) const {
    mExperienceId.write(stream);
    stream.writeString(mExperienceName);
    mExperienceWorldId.write(stream);
    stream.writeString(mExperienceWorldName);
    stream.writeString(mCreatorId);
    mTargetId.write(stream);
    stream.writeString(mScenarioId);
    stream.writeString(mServerId);
}

Result<> GatheringsConfigurationJoinInfo::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mExperienceId.read(stream); !status) return status;
    if (auto status = stream.readString(mExperienceName); !status) return status;
    if (auto status = mExperienceWorldId.read(stream); !status) return status;
    if (auto status = stream.readString(mExperienceWorldName); !status) return status;
    if (auto status = stream.readString(mCreatorId); !status) return status;
    if (auto status = mTargetId.read(stream); !status) return status;
    if (auto status = stream.readString(mScenarioId); !status) return status;
    return stream.readString(mServerId);
}

void GatheringsConfigurationClientStoreEntryPointInfo::write(BinaryStream& stream) const {
    stream.writeString(mStoreId);
    stream.writeString(mStoreName);
}

Result<> GatheringsConfigurationClientStoreEntryPointInfo::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mStoreId); !status) return status;
    return stream.readString(mStoreName);
}

void GatheringsConfigurationPresenceInfo::write(BinaryStream& stream) const {
    stream.writeString(mExperienceName);
    stream.writeString(mWorldName);
}

Result<> GatheringsConfigurationPresenceInfo::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mExperienceName); !status) return status;
    return stream.readString(mWorldName);
}

void ServerConfigurationJoinInfo::write(BinaryStream& stream) const {
    stream.writeOptional(mGatheringsConfiguration, &GatheringsConfigurationJoinInfo::write);
    stream.writeOptional(mStoreEntryPointInfo, &GatheringsConfigurationClientStoreEntryPointInfo::write);
    stream.writeOptional(mPresenceInfo, &GatheringsConfigurationPresenceInfo::write);
}

Result<> ServerConfigurationJoinInfo::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readOptional(mGatheringsConfiguration, &GatheringsConfigurationJoinInfo::read); !status) {
        return status;
    }
    if (auto status =
            stream.readOptional(mStoreEntryPointInfo, &GatheringsConfigurationClientStoreEntryPointInfo::read);
        !status) {
        return status;
    }
    return stream.readOptional(mPresenceInfo, &GatheringsConfigurationPresenceInfo::read);
}

} // namespace sculk::protocol::inline abi_v944
