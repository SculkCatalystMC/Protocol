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

namespace sculk::protocol::inline abi_v944 {

struct DataStoreUpdate {
    std::string                             mName{};
    std::string                             mProperty{};
    std::string                             mPath{};
    std::variant<double, bool, std::string> mData{};
    std::uint32_t                           mPropertyUpdateCount{};
    std::uint32_t                           mPathUpdateCount{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct DataStoreChange {
    std::string                             mName{};
    std::string                             mProperty{};
    std::uint32_t                           mUpdateCount{};
    std::variant<double, bool, std::string> mData{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

struct DataStoreRemoval {
    std::string mName{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
