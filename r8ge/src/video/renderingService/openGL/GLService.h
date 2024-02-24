#ifndef R8GE_GLSERVICE_H
#define R8GE_GLSERVICE_H

#include "../RenderingService.h"
#include "../buffers/IndexBuffer.h"


#include <vector>

#include <GL/glew.h>


namespace r8ge {
    namespace video {
        class GLService : public RenderingService {
        public:
            GLService();

            ~GLService() override;

            void init() override;

            void exit() override;

            void clear() const override;

            void preRender() const override;

            void render() const override;

            void render(unsigned int count) const override;

            void setIndexBuffer(const IndexBuffer &ib) override;

            void setVertexBuffer(const VertexBuffer &vb) override;

            void setDataLayout() const;

            void setProgram(const Program &program) override;

            bool compileProgram(Program &program) override;

            bool compileShader(GLuint shader, std::string_view source, std::string_view type);

            void setUniformBool(Program &program, const std::string &name, bool value) override;

            void setUniformInt(Program &program, const std::string &name, int value) override;

            void setUniformFloat(Program &program, const std::string &name, float value) override;

            void setUniformVec2(Program &program, const std::string &name, const glm::vec2 &value) override;

            void setUniformVec2(Program &program, const std::string &name, float x, float y) override;

            void setUniformVec3(Program &program, const std::string &name, const glm::vec3 &value) override;

            void setUniformVec3(Program &program, const std::string &name, float x, float y, float z) override;

            void setUniformVec4(Program &program, const std::string &name, const glm::vec4 &value) override;

            void setUniformVec4(Program &program, const std::string &name, float x, float y, float z, float w) override;

            void setUniformMat2(Program &program, const std::string &name, const glm::mat2 &mat) override;

            void setUniformMat3(Program &program, const std::string &name, const glm::mat3 &mat) override;

            void setUniformMat4(Program &program, const std::string &name, const glm::mat4 &mat) override;

            unsigned int getUniformLocation(Program &program, const std::string &name) override;

        private:
            //r8ge program id -> gl program id
            GLuint m_indexBuffer, m_vertexArrayObject, m_vertexBuffer;
            size_t m_indexCount;
            VertexBufferLayout m_layout;
        public:
            static std::unordered_map<size_t, GLuint> m_programs;
        };
    }
}

#endif//!R8GE_GLSERVICE_H
