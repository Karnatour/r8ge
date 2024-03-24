//
// Created by Vojta on 24.03.2024.
//

#include "ShaderLibrary.h"
#include "../r8ge/src/video/Video.h"

namespace r8ge::video {
    void ShaderLibrary::addShader(const std::string &path) {
#ifdef R8GE_WINDOWS
        std::string name = path.substr(path.find_last_of('\\') + 1);
#else
        std::string name = path.substr(path.find_last_of('/') + 1);
#endif
        m_shaderLibrary[name] = Program(path);
    }

    void ShaderLibrary::deleteShader(const std::string &name) {
        m_shaderLibrary.erase(name);
    }

    void ShaderLibrary::deleteShader(size_t id) {
        for (auto &pair : m_shaderLibrary) {
            if (pair.second.getId() == id) {
                m_shaderLibrary.erase(pair.first);
                return;
            }
        }
    }

    void ShaderLibrary::compileAllShaders() {
        for (auto &pair : m_shaderLibrary) {
            Video::getRenderingService()->compileProgram(pair.second);
        }
    }

    void ShaderLibrary::useShader(const std::string &name) {
        auto it = m_shaderLibrary.find(name);
        if (it != m_shaderLibrary.end()) {
            Video::getRenderingService()->setProgram(it->second);
        } else {
            R8GE_LOG_ERROR("ShaderLibrary: Unable to use shader with name {} not found", name);
        }
    }

    void ShaderLibrary::useShader(const size_t id) {
        for (auto &pair : m_shaderLibrary) {
            if (pair.second.getId() == id) {
                Video::getRenderingService()->setProgram(pair.second);
                return;
            }
        }
    }

    Program &ShaderLibrary::getShader(const std::string &name) {
        auto it = m_shaderLibrary.find(name);
        if (it != m_shaderLibrary.end()) {
            return it->second;
        } else {
            R8GE_LOG_FATAL("ShaderLibrary: Unable to get shader with name {} not found", name);}
    }

} // r8ge::video
