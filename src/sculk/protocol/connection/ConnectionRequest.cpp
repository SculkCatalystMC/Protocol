// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/connection/ConnectionRequest.hpp"
#include "../utility/Reflection.hpp"

namespace sculk::protocol::inline abi_v944 {

void ConnectionRequest::write(BinaryStream& stream) const {
    std::vector<std::byte> payload{};
    BinaryStream           payloadStream(payload);
    payloadStream.writeLongString(utils::serialize_json(mLoginInfo));
    payloadStream.writeLongString(mClientProperties);
    stream.writeUnsignedVarInt(static_cast<std::uint32_t>(payload.size()));
    stream.writeBytes(payload.data(), payload.size());
}

Result<> ConnectionRequest::read(ReadOnlyBinaryStream& stream) {
    std::string payload{};
    if (auto status = stream.readString(payload); !status) return status;
    ReadOnlyBinaryStream payloadStream(std::span(reinterpret_cast<std::byte*>(payload.data()), payload.size()));
    std::string          authJson{};
    if (auto status = payloadStream.readLongString(authJson); !status) return status;
    if (auto status = utils::deserialize_json(mLoginInfo, authJson); !status) return status;
    return payloadStream.readLongString(mClientProperties);
}

} // namespace sculk::protocol::inline abi_v944
