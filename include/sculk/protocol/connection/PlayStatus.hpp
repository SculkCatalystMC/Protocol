// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <cstdint>

namespace sculk::protocol::inline abi_v944 {

enum class PlayStatus : std::int32_t {
    LoginSuccess                             = 0,
    LoginFailedClientOld                     = 1,
    LoginFailedServerOld                     = 2,
    PlayerSpawn                              = 3,
    LoginFailedInvalidTenant                 = 4,
    LoginFailedEditionMismatchEduToVanilla   = 5,
    LoginFailedEditionMismatchVanillaToEdu   = 6,
    LoginFailedServerFullSubClient           = 7,
    LoginFailedEditorMismatchEditorToVanilla = 8,
    LoginFailedEditorMismatchVanillaToEditor = 9
};

} // namespace sculk::protocol::inline abi_v944
