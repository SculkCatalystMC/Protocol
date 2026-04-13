// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"
#include "sculk/protocol/utility/math/Vec2.hpp"
#include <map>
#include <optional>

namespace sculk::protocol::inline abi_v944 {

struct CameraAimAssistCategoryPriorities {
    std::map<std::string, std::int32_t> mEntities{};
    std::map<std::string, std::int32_t> mBlocks{};
    std::optional<std::int32_t>         mEntityDefault{};
    std::optional<std::int32_t>         mBlockDefault{};
    std::map<std::string, std::int32_t> mBlockTags{};
    std::map<std::string, std::int32_t> mEntityTypeFamilies{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct CameraAimAssistCategoryDefinition {
    std::string                       mName{};
    CameraAimAssistCategoryPriorities mPriorities{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct CameraAimAssistCategoriesDefinition {
    std::string                                    mIdentifier{};
    std::vector<CameraAimAssistCategoryDefinition> mCategory{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct CameraAimAssistPresetDefinition {
    std::string                        mIdentifier{};
    std::string                        mCategories{};
    std::vector<std::string>           mExclusionList{};
    std::vector<std::string>           mLiquidTargetingList{};
    std::map<std::string, std::string> mItemSettings{};
    std::optional<std::string>         mDefaultItemSettings{};
    std::optional<std::string>         mHandSettings{};
    std::vector<std::string>           mBlockExclusionList{};
    std::vector<std::string>           mBlockTagExclusionList{};
    std::vector<std::string>           mEntityExclusionList{};
    std::vector<std::string>           mEntityTypeFamilyExclusionList{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

class CameraPresetAimAssistDefinition {
public:
    enum class TargetMode : std::uint8_t {
        Angle    = 0,
        Distance = 1,
    };

public:
    std::optional<std::string> mPresetId{};
    std::optional<TargetMode>  mTargetMode{};
    std::optional<Vec2>        mViewAngle{};
    std::optional<float>       mDistance{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
