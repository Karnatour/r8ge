//
// Created by karnatour on 9.1.24.
//

#pragma once

namespace r8ge{
    enum ImageFormat{
        RGB8,
        RGBA8
    };

    enum Format{
        RGB,
        RGBA
    };
    extern const char* textureTypesStrings[];
    constexpr int TEXTURE_TYPES_STRINGS_COUNT = 4;
    //TexTs - TextureTypeString
    std::string convertTexTsToMeshTexTs(const std::string& textureTypeString);

}

