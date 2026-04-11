// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/level/DataStore.hpp"

namespace sculk::protocol::inline abi_v944 {

void DataStoreUpdate::write(BinaryStream& stream) const {
    stream.writeString(mName);
    stream.writeString(mProperty);
    stream.writeString(mPath);
    stream.writeVariantIndex<std::uint32_t>(mData, &BinaryStream::writeUnsignedVarInt);
    std::visit(
        Overload{
            [&](double value) { stream.writeDouble(value); },
            [&](bool value) { stream.writeBool(value); },
            [&](const std::string& value) { stream.writeString(value); },
        },
        mData
    );
    stream.writeUnsignedInt(mPropertyUpdateCount);
}

Result<> DataStoreUpdate::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    if (auto status = stream.readString(mProperty); !status) return status;
    if (auto status = stream.readString(mPath); !status) return status;
    if (auto status = stream.readVariantIndex<std::uint32_t>(mData, &ReadOnlyBinaryStream::readUnsignedVarInt); !status)
        return status;
    if (auto status = std::visit(
            Overload{
                [&](double& value) { return stream.readDouble(value); },
                [&](bool& value) { return stream.readBool(value); },
                [&](std::string& value) { return stream.readString(value); },
            },
            mData
        );
        !status) {
        return status;
    }
    return stream.readUnsignedInt(mPropertyUpdateCount);
}

void DataStoreChange::write(BinaryStream& stream) const {
    stream.writeString(mName);
    stream.writeString(mProperty);
    stream.writeVariantIndex<std::uint32_t>(mData, &BinaryStream::writeUnsignedVarInt);
    std::visit(
        Overload{
            [&](double value) { stream.writeDouble(value); },
            [&](bool value) { stream.writeBool(value); },
            [&](const std::string& value) { stream.writeString(value); },
        },
        mData
    );
    stream.writeUnsignedInt(mUpdateCount);
}

Result<> DataStoreChange::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    if (auto status = stream.readString(mProperty); !status) return status;
    if (auto status = stream.readVariantIndex<std::uint32_t>(mData, &ReadOnlyBinaryStream::readUnsignedVarInt); !status)
        return status;
    if (auto status = std::visit(
            Overload{
                [&](double& value) { return stream.readDouble(value); },
                [&](bool& value) { return stream.readBool(value); },
                [&](std::string& value) { return stream.readString(value); },
            },
            mData
        );
        !status) {
        return status;
    }
    return stream.readUnsignedInt(mUpdateCount);
}

void DataStoreRemoval::write(BinaryStream& stream) const { stream.writeString(mName); }

Result<> DataStoreRemoval::read(ReadOnlyBinaryStream& stream) { return stream.readString(mName); }

} // namespace sculk::protocol::inline abi_v944
