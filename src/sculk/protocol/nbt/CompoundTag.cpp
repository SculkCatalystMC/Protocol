// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/nbt/TagVariant.hpp"

namespace sculk::protocol::inline abi_v944 {

void CompoundTag::serialize(BinaryStream& stream) const {
    for (const auto& [key, value] : mValue) {
        TagType type = value.getType();
        if (type != TagType::End) {
            stream.writeEnum(type, &BinaryStream::writeByte);
            stream.writeString(key);
            value.serialize(stream);
        }
    }
    stream.writeByte(0); // End tag
}

Result<> CompoundTag::deserialize(ReadOnlyBinaryStream& stream) {
    while (true) {
        TagType tagType{};
        if (auto status = stream.readEnum(tagType, &ReadOnlyBinaryStream::readByte); !status) return status;
        if (tagType == TagType::End) {
            break;
        }
        std::string key{};
        if (auto status = stream.readString(key); !status) return status;
        TagVariant value{};
        value.emplace(tagType);
        if (auto status = value.deserialize(stream); !status) return status;
        mValue.emplace(std::move(key), std::move(value));
    }
    return {};
}

void CompoundTag::write(BinaryStream& stream) const {
    stream.writeEnum(TagType::Compound, &BinaryStream::writeByte);
    stream.writeByte(0); // Root name (empty string)
    serialize(stream);
}

[[nodiscard]] Result<> CompoundTag::read(ReadOnlyBinaryStream& stream) {
    TagType rootType{};
    if (auto status = stream.readEnum(rootType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (rootType != TagType::Compound) {
        return error_utils::makeError("CompoundTag::read invalid root tag type");
    }
    if (auto status = stream.ignoreBytes(1); !status) return status; // Ignore root name (empty string)
    return deserialize(stream);
}

} // namespace sculk::protocol::inline abi_v944
