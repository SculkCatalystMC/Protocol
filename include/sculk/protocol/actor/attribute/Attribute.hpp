// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"

namespace sculk::protocol::inline abi_v944 {

struct Attribute {
    struct Modifier {
        std::string mId{};
        std::string mName{};
        float       mAmount{};
        int         mOperation{};
        int         mOperand{};
        bool        mIsSerializable{};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

    float                 mMinValue{};
    float                 mMaxValue{};
    float                 mCurrentValue{};
    float                 mDefaultMinValue{};
    float                 mDefaultMaxValue{};
    float                 mDefaultValue{};
    std::string           mName{};
    std::vector<Modifier> mModifiers{};
    std::uint64_t         mTick{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
