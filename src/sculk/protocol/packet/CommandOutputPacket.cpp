// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/CommandOutputPacket.hpp"
#include "../utility/EnumName.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds CommandOutputPacket::getId() const noexcept { return MinecraftPacketIds::CommandOutput; }

std::string_view CommandOutputPacket::getName() const noexcept { return "CommandOutputPacket"; }

void CommandOutputPacket::write(BinaryStream& stream) const {
    mOriginData.write(stream);
    utils::writeEnumName(stream, mOutputType);
    stream.writeUnsignedInt(mSuccessCount);
    stream.writeArray(mOutputMessages, [](BinaryStream& output, const OutputMessage& data) {
        output.writeString(data.mMessageId);
        output.writeBool(data.mSuccess);
        output.writeArray(data.mParameters, &BinaryStream::writeString);
    });
    stream.writeString(mDataSet);
}

Result<> CommandOutputPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mOriginData.read(stream); !status) return status;
    if (auto status = utils::readEnumName(stream, mOutputType); !status) return status;
    if (auto status = stream.readUnsignedInt(mSuccessCount); !status) return status;
    if (auto status = stream.readArray(
            mOutputMessages,
            [](ReadOnlyBinaryStream& input, OutputMessage& data) {
                if (auto status = input.readString(data.mMessageId); !status) return status;
                if (auto status = input.readBool(data.mSuccess); !status) return status;
                return input.readArray(data.mParameters, &ReadOnlyBinaryStream::readString);
            }
        );
        !status) {
        return status;
    }
    return stream.readString(mDataSet);
}

} // namespace sculk::protocol::inline abi_v944
