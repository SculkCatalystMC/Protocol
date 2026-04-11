// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/level/ServerTelemetryData.hpp"

namespace sculk::protocol::inline abi_v944 {

void ServerTelemetryData::write(BinaryStream& stream) const {
    stream.writeString(mServerId);
    stream.writeString(mScenarioId);
    stream.writeString(mWorldId);
    stream.writeString(mOwnerId);
}

Result<> ServerTelemetryData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mServerId); !status) return status;
    if (auto status = stream.readString(mScenarioId); !status) return status;
    if (auto status = stream.readString(mWorldId); !status) return status;
    return stream.readString(mOwnerId);
}

} // namespace sculk::protocol::inline abi_v944
