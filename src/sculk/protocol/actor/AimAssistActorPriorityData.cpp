// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/actor/AimAssistActorPriorityData.hpp"

namespace sculk::protocol::inline abi_v944 {

void AimAssistActorPriorityData::write(BinaryStream& stream) const {
    stream.writeSignedInt(mPresetIndex);
    stream.writeSignedInt(mCategoryIndex);
    stream.writeSignedInt(mActorIndex);
    stream.writeSignedInt(mPriorityValue);
}

Result<> AimAssistActorPriorityData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readSignedInt(mPresetIndex); !status) return status;
    if (auto status = stream.readSignedInt(mCategoryIndex); !status) return status;
    if (auto status = stream.readSignedInt(mActorIndex); !status) return status;
    return stream.readSignedInt(mPriorityValue);
}

} // namespace sculk::protocol::inline abi_v944
