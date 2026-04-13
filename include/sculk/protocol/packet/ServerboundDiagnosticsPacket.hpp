// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/packet/IPacket.hpp"
#include <vector>

namespace sculk::protocol::inline abi_v944 {

class ServerboundDiagnosticsPacket : public IPacket {
public:
public:
    enum class MemoryCategory : std::uint8_t {
        Unknown                               = 0,
        InvalidSizeUnknown                    = 1,
        Actor                                 = 2,
        ActorAnimation                        = 3,
        ActorRendering                        = 4,
        BlockTickingQueues                    = 5,
        BiomeStorage                          = 6,
        Cereal                                = 7,
        CircuitSystem                         = 8,
        Client                                = 9,
        Commands                              = 10,
        DBStorage                             = 11,
        Debug                                 = 12,
        Documentation                         = 13,
        ECSSystems                            = 14,
        Fmod                                  = 15,
        Fonts                                 = 16,
        ImGui                                 = 17,
        Input                                 = 18,
        JsonUI                                = 19,
        JsonUIControlFactoryJson              = 20,
        JsonUIControlTree                     = 21,
        JsonUIControlTreeControlElement       = 22,
        JsonUIControlTreePopulateDataBinding  = 23,
        JsonUIControlTreePopulateFocus        = 24,
        JsonUIControlTreePopulateLayout       = 25,
        JsonUIControlTreePopulateOther        = 26,
        JsonUIControlTreePopulateSprite       = 27,
        JsonUIControlTreePopulateText         = 28,
        JsonUIControlTreePopulateTTS          = 29,
        JsonUIControlTreeVisibility           = 30,
        JsonUICreateUI                        = 31,
        JsonUIDefs                            = 32,
        JsonUILayoutManager                   = 33,
        JsonUILayoutManagerRemoveDependencies = 34,
        JsonUILayoutManagerInitVariable       = 35,
        Languages                             = 36,
        Level                                 = 37,
        LevelStructures                       = 38,
        LevelChunk                            = 39,
        LevelChunkGen                         = 40,
        LevelChunkGenThreadLocal              = 41,
        LightVolumeManager                    = 42,
        Network                               = 43,
        Marketplace                           = 44,
        MaterialDragonCompiledDefinition      = 45,
        MaterialDragonMaterial                = 46,
        MaterialDragonResource                = 47,
        MaterialDragonUniformMap              = 48,
        MaterialRenderMaterial                = 49,
        MaterialRenderMaterialGroup           = 50,
        MaterialVariationManager              = 51,
        Molang                                = 52,
        OreUI                                 = 53,
        Persona                               = 54,
        Player                                = 55,
        RenderChunk                           = 56,
        RenderChunkIndexBuffer                = 57,
        RenderChunkVertexBuffer               = 58,
        Rendering                             = 59,
        RenderingLibrary                      = 60,
        RequestLog                            = 61,
        ResourcePacks                         = 62,
        Sound                                 = 63,
        SubChunkBiomeData                     = 64,
        SubChunkBlockData                     = 65,
        SubChunkLightData                     = 66,
        Textures                              = 67,
        Vr                                    = 68,
        WeatherRenderer                       = 69,
        WorldGenerator                        = 70,
        Tasks                                 = 71,
        Test                                  = 72,
        Scripting                             = 73,
        ScriptingRuntime                      = 74,
        ScriptingContext                      = 75,
        ScriptingContextBindingsMc            = 76,
        ScriptingContextBindingsGt            = 77,
        ScriptingContextRun                   = 78,
        DataDrivenUI                          = 79,
        DataDrivenUIDefs                      = 80,
        Gameface                              = 81,
        GamefaceSystem                        = 82,
        GamefaceDom                           = 83,
        GamefaceCss                           = 84,
        GamefaceDisplay                       = 85,
        GamefaceTempAllocator                 = 86,
        GamefacePoolAllocator                 = 87,
        GamefaceDump                          = 88,
        GamefaceMedia                         = 89,
        GamefaceJson                          = 90,
        GamefaceScriptEngine                  = 91
    };

    struct MemoryCategoryCounter {
        MemoryCategory mType{};
        std::uint64_t  mCurrentBytes{};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

public:
    float                              mAvgFps{};
    float                              mAvgServerSimTickTimeMS{};
    float                              mAvgClientSimTickTimeMS{};
    float                              mAvgBeginFrameTimeMS{};
    float                              mAvgInputTimeMS{};
    float                              mAvgRenderTimeMS{};
    float                              mAvgEndFrameTimeMS{};
    float                              mAvgRemainderTimePercent{};
    float                              mAvgUnaccountedTimePercent{};
    std::vector<MemoryCategoryCounter> mMemoryCategoryValues{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
