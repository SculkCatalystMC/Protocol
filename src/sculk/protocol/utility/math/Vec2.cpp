// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/utility/math/Vec2.hpp"

namespace sculk::protocol::inline abi_v944 {

void Vec2::write(BinaryStream& stream) const {
    stream.writeFloat(mX);
    stream.writeFloat(mY);
}

Result<> Vec2::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mX); !status) return status;
    return stream.readFloat(mY);
}

} // namespace sculk::protocol::inline abi_v944
