// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/camera/CameraAimAssist.hpp"

namespace sculk::protocol::inline abi_v944 {

namespace {

inline void writePriorityMap(BinaryStream& stream, const std::map<std::string, std::int32_t>& values) {
    stream.writeUnsignedVarInt(static_cast<std::uint32_t>(values.size()));
    for (const auto& [name, priority] : values) {
        stream.writeString(name);
        stream.writeSignedInt(priority);
    }
}

inline Result<> readPriorityMap(ReadOnlyBinaryStream& stream, std::map<std::string, std::int32_t>& values) {
    values.clear();
    std::uint32_t size{};
    if (auto status = stream.readUnsignedVarInt(size); !status) return status;
    for (std::uint32_t i = 0; i < size; ++i) {
        std::string  name{};
        std::int32_t priority{};
        if (auto status = stream.readString(name); !status) return status;
        if (auto status = stream.readSignedInt(priority); !status) return status;
        values.emplace(std::move(name), priority);
    }
    return {};
}

inline void writeStringMap(BinaryStream& stream, const std::map<std::string, std::string>& values) {
    stream.writeUnsignedVarInt(static_cast<std::uint32_t>(values.size()));
    for (const auto& [name, category] : values) {
        stream.writeString(name);
        stream.writeString(category);
    }
}

inline Result<> readStringMap(ReadOnlyBinaryStream& stream, std::map<std::string, std::string>& values) {
    values.clear();
    std::uint32_t size{};
    if (auto status = stream.readUnsignedVarInt(size); !status) return status;
    for (std::uint32_t i = 0; i < size; ++i) {
        std::string name{};
        std::string category{};
        if (auto status = stream.readString(name); !status) return status;
        if (auto status = stream.readString(category); !status) return status;
        values.emplace(std::move(name), std::move(category));
    }
    return {};
}

} // namespace

void CameraAimAssistCategoryPriorities::write(BinaryStream& stream) const {
    writePriorityMap(stream, mEntities);
    writePriorityMap(stream, mBlocks);
    writePriorityMap(stream, mBlockTags);
    writePriorityMap(stream, mEntityTypeFamilies);
    stream.writeOptional(mEntityDefault, &BinaryStream::writeSignedInt);
    stream.writeOptional(mBlockDefault, &BinaryStream::writeSignedInt);
}

Result<> CameraAimAssistCategoryPriorities::read(ReadOnlyBinaryStream& stream) {
    if (auto status = readPriorityMap(stream, mEntities); !status) return status;
    if (auto status = readPriorityMap(stream, mBlocks); !status) return status;
    if (auto status = readPriorityMap(stream, mBlockTags); !status) return status;
    if (auto status = readPriorityMap(stream, mEntityTypeFamilies); !status) return status;
    if (auto status = stream.readOptional(mEntityDefault, &ReadOnlyBinaryStream::readSignedInt); !status) return status;
    return stream.readOptional(mBlockDefault, &ReadOnlyBinaryStream::readSignedInt);
}

void CameraAimAssistCategoryDefinition::write(BinaryStream& stream) const {
    stream.writeString(mName);
    mPriorities.write(stream);
}

Result<> CameraAimAssistCategoryDefinition::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    return mPriorities.read(stream);
}

void CameraAimAssistCategoriesDefinition::write(BinaryStream& stream) const {
    stream.writeString(mIdentifier);
    stream.writeArray(mCategory, &CameraAimAssistCategoryDefinition::write);
}

Result<> CameraAimAssistCategoriesDefinition::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mIdentifier); !status) return status;
    return stream.readArray(mCategory, &CameraAimAssistCategoryDefinition::read);
}

void CameraAimAssistPresetDefinition::write(BinaryStream& stream) const {
    stream.writeString(mIdentifier);
    stream.writeArray(mBlockExclusionList, &BinaryStream::writeString);
    stream.writeArray(mEntityExclusionList, &BinaryStream::writeString);
    stream.writeArray(mBlockTagExclusionList, &BinaryStream::writeString);
    stream.writeArray(mEntityTypeFamilyExclusionList, &BinaryStream::writeString);
    stream.writeArray(mLiquidTargetingList, &BinaryStream::writeString);
    writeStringMap(stream, mItemSettings);
    stream.writeOptional(mDefaultItemSettings, &BinaryStream::writeString);
    stream.writeOptional(mHandSettings, &BinaryStream::writeString);
}

Result<> CameraAimAssistPresetDefinition::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mIdentifier); !status) return status;
    if (auto status = stream.readArray(mBlockExclusionList, &ReadOnlyBinaryStream::readString); !status) return status;
    if (auto status = stream.readArray(mEntityExclusionList, &ReadOnlyBinaryStream::readString); !status) return status;
    if (auto status = stream.readArray(mBlockTagExclusionList, &ReadOnlyBinaryStream::readString); !status)
        return status;
    if (auto status = stream.readArray(mEntityTypeFamilyExclusionList, &ReadOnlyBinaryStream::readString); !status)
        return status;
    if (auto status = stream.readArray(mLiquidTargetingList, &ReadOnlyBinaryStream::readString); !status) return status;
    if (auto status = readStringMap(stream, mItemSettings); !status) return status;
    if (auto status = stream.readOptional(mDefaultItemSettings, &ReadOnlyBinaryStream::readString); !status)
        return status;
    return stream.readOptional(mHandSettings, &ReadOnlyBinaryStream::readString);
}

void CameraPresetAimAssistDefinition::write(BinaryStream& stream) const {
    stream.writeOptional(mPresetId, &BinaryStream::writeString);
    stream.writeOptional(mTargetMode, &BinaryStream::writeSignedInt);
    stream.writeOptional(mViewAngle, &Vec2::write);
    stream.writeOptional(mDistance, &BinaryStream::writeFloat);
}

Result<> CameraPresetAimAssistDefinition::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readOptional(mPresetId, &ReadOnlyBinaryStream::readString); !status) return status;
    if (auto status = stream.readOptional(mTargetMode, &ReadOnlyBinaryStream::readSignedInt); !status) return status;
    if (auto status = stream.readOptional(mViewAngle, &Vec2::read); !status) return status;
    return stream.readOptional(mDistance, &ReadOnlyBinaryStream::readFloat);
}

} // namespace sculk::protocol::inline abi_v944
