// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/packet/IPacket.hpp"
#include "sculk/protocol/utility/math/Vec3.hpp"
#include <map>

namespace sculk::protocol::inline abi_v944 {

class GraphicsParameterOverridePacket : public IPacket {
public:
    enum class Type : std::uint8_t {
        SkyZenithColor          = 0,
        SkyHorizonColor         = 1,
        HorizonBlendMin         = 2,
        HorizonBlendMax         = 3,
        HorizonBlendStart       = 4,
        HorizonBlendMieStart    = 5,
        RayleighStrength        = 6,
        SunMieStrength          = 7,
        MoonMieStrength         = 8,
        SunGlareShape           = 9,
        Chlorophyll             = 10,
        CDOM                    = 11,
        SuspendedSediment       = 12,
        WavesDepth              = 13,
        WavesFrequency          = 14,
        WavesFrequencyScaling   = 15,
        WavesSpeed              = 16,
        WavesSpeedScaling       = 17,
        WavesShape              = 18,
        WavesOctaves            = 19,
        WavesMix                = 20,
        WavesPull               = 21,
        WavesDirectionIncrement = 22,
        MidtonesContrast        = 23,
        HighlightsContrast      = 24,
        ShadowsContrast         = 25,
        HighlightsGain          = 26,
        HighlightsGamma         = 27,
        HighlightsOffset        = 28,
        HighlightsSaturation    = 29,
        MidtonesGain            = 30,
        MidtonesGamma           = 31,
        MidtonesOffset          = 32,
        MidtonesSaturation      = 33,
        ShadowsGain             = 34,
        ShadowsGamma            = 35,
        ShadowsOffset           = 36,
        ShadowsSaturation       = 37,
        HighlightsMin           = 38,
        ShadowsMax              = 39,
        Temperature             = 40,
        SunColor                = 41,
        SunIlluminance          = 42,
        MoonColor               = 43,
        MoonIlluminance         = 44,
        FlashColor              = 45,
        FlashIlluminance        = 46,
        AmbientColor            = 47,
        AmbientIlluminance      = 48,
    };

public:
    std::map<float, Vec3> mParameterKeyFrameValues{};
    std::string           mBiomeIdentifier{};
    Type                  mParameterType{};
    bool                  mResetParameter{};
    float                 mFloatValue{};
    Vec3                  mVec3Value{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
