#ifndef R8GE_RENDERINGSERVICE_H
#define R8GE_RENDERINGSERVICE_H

#include <memory>
#include <vector>

#include "buffers/VertexBuffer.h"
#include "buffers/IndexBuffer.h"
#include "../types/Color.h"
#include "../types/Vertex.h"

#include "programManager/Program.h"
#include <glm/glm.hpp>

namespace r8ge {
    namespace video {
        class RenderingService {
        public:
            enum class API {
                OpenGL
            };

            RenderingService();

            virtual ~RenderingService();

            virtual void init() = 0;

            virtual void exit() = 0;

            virtual void clear() const = 0;

            virtual void preRender() const = 0;

            virtual void render() const = 0;

            virtual void render(unsigned int count) const = 0;

            void setClearColor(ColorRGBA c);

            virtual void setIndexBuffer(const IndexBuffer &ib) = 0;

            virtual void setVertexBuffer(const VertexBuffer &vb) = 0;

            //Shaders
            virtual void setProgram(const Program &program) = 0;

            virtual bool compileProgram(Program &program) = 0;

            //Uniforms
            virtual void setUniformBool(Program &program, const std::string &name, bool value) = 0;

            virtual void setUniformInt(Program &program, const std::string &name, int value) = 0;

            virtual void setUniformFloat(Program &program, const std::string &name, float value) = 0;

            virtual void setUniformVec2(Program &program, const std::string &name, const glm::vec2 &value) = 0;

            virtual void setUniformVec2(Program &program, const std::string &name, float x, float y) = 0;

            virtual void setUniformVec3(Program &program, const std::string &name, const glm::vec3 &value) = 0;

            virtual void setUniformVec3(Program &program, const std::string &name, float x, float y, float z) = 0;

            virtual void setUniformVec4(Program &program, const std::string &name, const glm::vec4 &value) = 0;

            virtual void
            setUniformVec4(Program &program, const std::string &name, float x, float y, float z, float w) = 0;

            virtual void setUniformMat2(Program &program, const std::string &name, const glm::mat2 &mat) = 0;

            virtual void setUniformMat3(Program &program, const std::string &name, const glm::mat3 &mat) = 0;

            virtual void setUniformMat4(Program &program, const std::string &name, const glm::mat4 &mat) = 0;

            virtual unsigned int getUniformLocation(Program &program, const std::string &name) = 0;


        public:
            static std::shared_ptr<RenderingService> create(API api);
            static unsigned int id;

        protected:
            ColorRGBA m_clearColor;
        };
    }
}

#endif//!R8GE_RENDERINGSERVICE_H
