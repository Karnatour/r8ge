//
// Created by Vojta on 05.04.2024.
//

#include "Texture.h"

namespace r8ge {
    const char *textureTypesStrings[] = {"Diffuse", "Normal", "Specular", "Height"};

    std::string convertTexTsToMeshTexTs(const std::string &textureTypeString) {
        if (textureTypeString == "Diffuse") {
            return "texture_diffuse";
        } else if (textureTypeString == "Normal") {
            return "texture_specular";
        } else if (textureTypeString == "Specular") {
            return "texture_normal";
        } else if (textureTypeString == "Height") {
            return "texture_height";
        } else {
            R8GE_LOG_ERROR("TexTs conversion error: case not found");
            return "NOT FOUND";
        }
    }
}