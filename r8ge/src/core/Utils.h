//
// Created by Vojta on 05.04.2024.
//

#pragma once

#include "../video/types/SceneHelper.h"

namespace r8ge {
    std::string getExecutablePath();

    std::string getExecutableDirectory();

    void DecomposeMaterialToComponents(const Material *material, float *ambient, float *diffuse, float *specular, float *shine);

    void RecomposeMaterialFromComponents(const float *ambient, const float *diffuse, const float *specular, const float *shine, Material *material);
} // r8ge