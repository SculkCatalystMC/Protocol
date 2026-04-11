// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/connection/AuthenticationType.hpp"
#include "sculk/protocol/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/utility/deps/ReadOnlyBinaryStream.hpp"
#include <string>

namespace sculk::protocol::inline abi_v944 {

struct ConnectionRequest {
    struct LoginInfo {
        AuthenticationType mAuthenticationType{};
        std::string        mCertificate{};
        std::string        mToken{};
    };

    LoginInfo   mLoginInfo{};
    std::string mClientProperties{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v944
