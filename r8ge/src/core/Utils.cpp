//
// Created by Vojta on 05.04.2024.
//

#include <filesystem>
#include "Utils.h"
#include <Windows.h>

namespace r8ge {
#ifdef R8GE_WINDOWS

    std::string getExecutablePath() {
        WCHAR path[1024] = {0};
        std::filesystem::path fsPath;
        GetModuleFileNameW(nullptr, path, 1024);
        fsPath = std::filesystem::path(path);
        return fsPath.generic_string();
    }
//TODO Test this on Linux
#elif defined R8GE_LINUX
    std::string getExecutablePath(){
        char buffer[1024];
        readlink("/proc/self/exe",buffer,1024);
        return std::string(buffer);
    }

#endif

    std::string getExecutableDirectory() {
        std::filesystem::path path = getExecutablePath();
        return path.parent_path().generic_string();
    }

    void DecomposeMaterialToComponents(const Material *material, float *ambient, float *diffuse, float *specular, float *shine) {
        ambient[0] = material->ambient[0];
        ambient[1] = material->ambient[1];
        ambient[2] = material->ambient[2];

        diffuse[0] = material->diffuse[0];
        diffuse[1] = material->diffuse[1];
        diffuse[2] = material->diffuse[2];

        specular[0] = material->specular[0];
        specular[1] = material->specular[1];
        specular[2] = material->specular[2];

        *shine = material->shine;

    }

    void RecomposeMaterialFromComponents(const float *ambient, const float *diffuse, const float *specular, const float *shine, Material *material) {
        material->ambient[0] = ambient[0];
        material->ambient[1] = ambient[1];
        material->ambient[2] = ambient[2];

        material->diffuse[0] = diffuse[0];
        material->diffuse[1] = diffuse[1];
        material->diffuse[2] = diffuse[2];

        material->specular[0] = specular[0];
        material->specular[1] = specular[1];
        material->specular[2] = specular[2];

        material->shine = *shine;

    }
} // r8ge