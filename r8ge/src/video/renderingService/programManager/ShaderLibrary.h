//
// Created by Vojta on 24.03.2024.
//

#pragma once

#include "Program.h"

namespace r8ge::video {
    class ShaderLibrary {
    public:
        void addShader(const std::string &path);

        void deleteShader(const std::string &name);

        void deleteShader(size_t id);

        void compileAllShaders();

        void useShader(const std::string &name);

        void useShader(size_t id);

        Program &getShader(const std::string &name);

    private:
        std::unordered_map<std::string,Program> m_shaderLibrary{};
    };
} // r8ge::video
