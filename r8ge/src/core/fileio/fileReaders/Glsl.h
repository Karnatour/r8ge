#ifndef R8GE_GLSL_H
#define R8GE_GLSL_H

#include "Text.h"

#include <vector>

namespace r8ge {
    namespace reader {

        /*
         * GLSL file reader
         *
         * This class is used to read GLSL files. Uses modified .glsl file format:
         *
         *             /------------------------------------------------|
         *             |  @r8ge fragment
         *             |
         *             |   // Fragment Shader code
         *             |
         *             |
         *             |  @r8ge vertex
         *             |
         *             |  // Vertex Shader code
         *             |
         *             \------------------------------------------------|
         */
        class Glsl : protected Text {
        public:
            Glsl(std::string_view path);
            ~Glsl() override;

            void load_glsl();

            [[nodiscard]] std::string getVertexShader();

            [[nodiscard]] std::string getFragmentShader();

            static FileType getType();

        private:
            std::string m_vertexShader;
            std::string m_fragmentShader;
        };
    }
}

#endif//!R8GE_GLSL_H
