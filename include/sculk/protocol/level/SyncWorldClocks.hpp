// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"
#include <string>
#include <variant>
#include <vector>

namespace sculk::protocol::inline abi_v944 {

struct TimeMarkerData {
    std::uint64_t mId{};
    std::string   mName{};
    std::int32_t  mTime{};
    std::int32_t  mPeriod{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct SyncWorldClockStateData {
    std::uint64_t mClockId{};
    std::int32_t  mTime{};
    bool          mIsPaused{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct WorldClockData {
    std::uint64_t               mId{};
    std::string                 mName{};
    std::int32_t                mTime{};
    bool                        mIsPaused{};
    std::vector<TimeMarkerData> mTimeMarkers{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct SyncStateData {
    std::vector<SyncWorldClockStateData> mClockData{};
};

struct InitializeRegistryData {
    std::vector<WorldClockData> mClockData{};
};

struct AddTimeMarkerData {
    std::uint64_t               mClockId{};
    std::vector<TimeMarkerData> mTimeMarkers{};
};

struct RemoveTimeMarkerData {
    std::uint64_t              mClockId{};
    std::vector<std::uint64_t> mTimeMarkerIds{};
};

using SyncWorldClocksData =
    std::variant<SyncStateData, InitializeRegistryData, AddTimeMarkerData, RemoveTimeMarkerData>;

} // namespace sculk::protocol::inline abi_v944
