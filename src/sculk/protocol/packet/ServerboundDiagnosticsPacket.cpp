// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/ServerboundDiagnosticsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

void ServerboundDiagnosticsPacket::MemoryCategoryCounter::write(BinaryStream& stream) const {
    stream.writeEnum(mType, &BinaryStream::writeByte);
    stream.writeUnsignedInt64(mCurrentBytes);
}

Result<> ServerboundDiagnosticsPacket::MemoryCategoryCounter::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mType, &ReadOnlyBinaryStream::readByte); !status) return status;
    return stream.readUnsignedInt64(mCurrentBytes);
}

MinecraftPacketIds ServerboundDiagnosticsPacket::getId() const noexcept {
    return MinecraftPacketIds::ServerboundDiagnostics;
}
std::string_view ServerboundDiagnosticsPacket::getName() const noexcept { return "ServerboundDiagnosticsPacket"; }

void ServerboundDiagnosticsPacket::write(BinaryStream& stream) const {
    stream.writeFloat(mAvgFps);
    stream.writeFloat(mAvgServerSimTickTimeMS);
    stream.writeFloat(mAvgClientSimTickTimeMS);
    stream.writeFloat(mAvgBeginFrameTimeMS);
    stream.writeFloat(mAvgInputTimeMS);
    stream.writeFloat(mAvgRenderTimeMS);
    stream.writeFloat(mAvgEndFrameTimeMS);
    stream.writeFloat(mAvgRemainderTimePercent);
    stream.writeFloat(mAvgUnaccountedTimePercent);
    stream.writeArray(mMemoryCategoryValues, &MemoryCategoryCounter::write);
}

Result<> ServerboundDiagnosticsPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mAvgFps); !status) return status;
    if (auto status = stream.readFloat(mAvgServerSimTickTimeMS); !status) return status;
    if (auto status = stream.readFloat(mAvgClientSimTickTimeMS); !status) return status;
    if (auto status = stream.readFloat(mAvgBeginFrameTimeMS); !status) return status;
    if (auto status = stream.readFloat(mAvgInputTimeMS); !status) return status;
    if (auto status = stream.readFloat(mAvgRenderTimeMS); !status) return status;
    if (auto status = stream.readFloat(mAvgEndFrameTimeMS); !status) return status;
    if (auto status = stream.readFloat(mAvgRemainderTimePercent); !status) return status;
    if (auto status = stream.readFloat(mAvgUnaccountedTimePercent); !status) return status;
    return stream.readArray(mMemoryCategoryValues, &MemoryCategoryCounter::read);
}

} // namespace sculk::protocol::inline abi_v944
