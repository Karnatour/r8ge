//
// Created by Vojta on 05.04.2024.
//

#include <filesystem>
#include "Utils.h"
#include <Windows.h>

namespace r8ge
{
#ifdef R8GE_WINDOWS

    std::string getExecutablePath()
    {
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

    std::string getExecutableDirectory()
    {
        std::filesystem::path path = getExecutablePath();
        return path.parent_path().generic_string();
    }
} // r8ge