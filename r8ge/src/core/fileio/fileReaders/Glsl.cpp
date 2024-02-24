#include "Glsl.h"

namespace r8ge {
    namespace reader {

        FileType Glsl::getType() {
            return FileType::GLSL;
        }

        Glsl::Glsl(std::string_view path) : Text(path) {}

        Glsl::~Glsl() = default;

        void Glsl::load_glsl() {
            load();
            std::vector<std::string> lines = readLines();
            enum {
                NONE = 0, VERTEX = 1, FRAGMENT = 2
            } shaderType = NONE;

            for(auto& line : lines) {
                if(line.find("@r8ge vertex") != std::string::npos)  { shaderType = VERTEX;  continue; }
                if(line.find("@r8ge fragment") != std::string::npos){ shaderType = FRAGMENT; continue; }

                if(shaderType == VERTEX)   m_vertexShader+=line+"\n";
                if(shaderType == FRAGMENT) m_fragmentShader+=line+"\n";
            }

            clear();
        }

        std::string Glsl::getVertexShader() {
            return m_vertexShader;
        }

        std::string Glsl::getFragmentShader() {
            return m_fragmentShader;
        }
    }
}