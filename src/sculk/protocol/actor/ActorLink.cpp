// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/actor/ActorLink.hpp"

namespace sculk::protocol::inline abi_v944 {

void ActorLink::write(BinaryStream& stream) const {
    stream.writeVarInt64(mTargetAUniqueId);
    stream.writeVarInt64(mTargetBUniqueId);
    stream.writeEnum(mType, &BinaryStream::writeByte);
    stream.writeBool(mImmediate);
    stream.writeBool(mPassengerInitiated);
    stream.writeFloat(mVehicleAngularVelocity);
}

Result<> ActorLink::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt64(mTargetAUniqueId); !status) return status;
    if (auto status = stream.readVarInt64(mTargetBUniqueId); !status) return status;
    if (auto status = stream.readEnum(mType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readBool(mImmediate); !status) return status;
    if (auto status = stream.readBool(mPassengerInitiated); !status) return status;
    return stream.readFloat(mVehicleAngularVelocity);
}

} // namespace sculk::protocol::inline abi_v944
