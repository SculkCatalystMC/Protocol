// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/command/CommandData.hpp"
#include "../utility/EnumName.hpp"

namespace sculk::protocol::inline abi_v944 {

void CommandData::write(BinaryStream& stream) const {
    stream.writeString(mName);
    stream.writeString(mDescription);
    stream.writeUnsignedShort(mFlags);
    utils::writeEnumName(stream, mCommandPermissionLevel);
    stream.writeSignedInt(mAliasEnum);
    stream.writeArray(mChainedSubcommandIndexes, &BinaryStream::writeUnsignedInt);
    stream.writeArray(mOverloads, &CommandOverloadData::write);
}

Result<> CommandData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    if (auto status = stream.readString(mDescription); !status) return status;
    if (auto status = stream.readUnsignedShort(mFlags); !status) return status;
    if (auto status = utils::readEnumName(stream, mCommandPermissionLevel); !status) return status;
    if (auto status = stream.readSignedInt(mAliasEnum); !status) return status;
    if (auto status = stream.readArray(mChainedSubcommandIndexes, &ReadOnlyBinaryStream::readUnsignedInt); !status) {
        return status;
    }
    return stream.readArray(mOverloads, &CommandOverloadData::read);
}

} // namespace sculk::protocol::inline abi_v944
