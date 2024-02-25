#include "GLService.h"
#include "../buffers/VertexBuffer.h"

#include "GLConvertor.h"

#define R8GE_GL_ERROR_MSG_LENGTH 1024

namespace r8ge {
    namespace video {
        static void
        debugMsg(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                 const void *userParam) {
            R8GE_LOG_ERROR("GL debug message: {}", std::string_view(message, length));
        }

        std::unordered_map<size_t, GLuint> GLService::m_programs;

        GLService::GLService() : m_indexCount(0), m_indexBuffer(-1), m_vertexArrayObject(-1), m_vertexBuffer(-1) {
            R8GE_LOG("GL Service created ID: {}",id);
            id++;
        }

        GLService::~GLService() {
            R8GE_LOG("GL Service created ID: {}",id);
            id--;
        }

        void GLService::init() {
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

            glDebugMessageCallback(debugMsg, nullptr);

            auto version = std::string_view(reinterpret_cast<const char *>(glGetString(GL_VERSION)));
            R8GE_LOG_INFOR("GL Running version: {}", version);
        }

        void GLService::exit() {
            for (auto &[r8geid, glid]: m_programs) {
                glDeleteProgram(glid);
                R8GE_LOG("GL Program [r8ge:{},gl:{}] deleted", r8geid, glid);
            }
        }

        void GLService::clear() const {
            glClearColor(
                    static_cast<float>(m_clearColor.r) / 0xFF,
                    static_cast<float>(m_clearColor.g) / 0xFF,
                    static_cast<float>(m_clearColor.b) / 0xFF,
                    static_cast<float>(m_clearColor.a) / 0xFF);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void GLService::setIndexBuffer(const IndexBuffer &ib) {
            m_indexCount = ib.getIndeciesCount();

            auto a = ib.getData();

            glCreateBuffers(1, &m_indexBuffer);
            glNamedBufferData(m_indexBuffer, static_cast<GLsizei>(ib.getSize()), &ib.getRawData()[0], GL_STATIC_DRAW);
        }

        void GLService::setVertexBuffer(const VertexBuffer &vb) {
            glCreateVertexArrays(1, &m_vertexArrayObject);

            glCreateBuffers(1, &m_vertexBuffer);
            glNamedBufferData(m_vertexBuffer, static_cast<GLsizeiptr>(vb.getSize()), &vb.getRawData()[0],
                              GL_STATIC_DRAW);

            m_layout = vb.getLayout();
        }

        void GLService::setDataLayout() const {
            size_t index = 0;
            GLfloat offset = 0;
            for (auto &element: m_layout.getLayout()) {
                glEnableVertexArrayAttrib(m_vertexArrayObject, index);
                glVertexArrayAttribBinding(m_vertexArrayObject, index, 0);
                glVertexArrayAttribFormat(m_vertexArrayObject,
                                          index,
                                          VertexBufferLayout::EntryTypeComponents(element),
                                          GLConvertor::convertToGLType(
                                                  VertexBufferLayout::EntryTypeToDataType(element)),
                                          VertexBufferLayout::EntryTypeShouldBeNormalized(element),
                                          offset
                );
                index++;
                offset += VertexBufferLayout::EntryTypeSize(element);
            }
        }

        void GLService::preRender() const {
            setDataLayout();

            glVertexArrayVertexBuffer(m_vertexArrayObject, 0, m_vertexBuffer, 0,
                                      static_cast<GLsizei>(m_layout.getStride()));
            glVertexArrayElementBuffer(m_vertexArrayObject, m_indexBuffer);

        }

        void GLService::render() const {
            if (m_indexCount == 0)
                R8GE_LOG_ERROR("Invalid index count: {}", m_indexCount);
            if (m_indexCount % 3 != 0)
                R8GE_LOG_WARNI("Index count is not divisible by 3: {}", m_indexCount);
            if (m_indexBuffer == -1)
                R8GE_LOG_ERROR("Invalid index buffer - index buffer is not bound");
            if (m_vertexArrayObject == -1)
                R8GE_LOG_ERROR("Invalid vertex array object - vertex array object is not bound");

            glBindVertexArray(m_vertexArrayObject);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexCount), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
            glActiveTexture(GL_TEXTURE0);
        }

        void GLService::render(unsigned int count) const {
            if (m_indexCount == 0)
                R8GE_LOG_ERROR("Invalid index count: {}", m_indexCount);
            if (m_indexCount % 3 != 0)
                R8GE_LOG_WARNI("Index count is not divisible by 3: {}", m_indexCount);
            if (m_indexBuffer == -1)
                R8GE_LOG_ERROR("Invalid index buffer - index buffer is not bound");
            if (m_vertexArrayObject == -1)
                R8GE_LOG_ERROR("Invalid vertex array object - vertex array object is not bound");

            glBindVertexArray(m_vertexArrayObject);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
            glActiveTexture(GL_TEXTURE0);

        }

        void GLService::setProgram(const Program &program) {
            glUseProgram(m_programs[program.getId()]);
        }

        bool GLService::compileProgram(Program &program) {
            //TODO Check if shader was already compiled
            GLuint vs = glCreateShader(GL_VERTEX_SHADER);
            GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

            std::string vertexShaderSourceStr = program.getVertexShader();
            const char *vertexShaderSource = vertexShaderSourceStr.c_str();

            std::string fragmentShaderSourceStr = program.getFragmentShader();
            const char *fragmentShaderSource = fragmentShaderSourceStr.c_str();

            if (!compileShader(vs, vertexShaderSource, "vertex shader"))
                return false;
            if (!compileShader(fs, fragmentShaderSource, "fragment shader"))
                return false;

            GLuint p = glCreateProgram();

            glAttachShader(p, vs);
            glAttachShader(p, fs);

            glLinkProgram(p);

            int result;
            glGetProgramiv(p, GL_LINK_STATUS, &result);
            if (result != GL_TRUE) {
                GLsizei log_length = 0;
                char message[R8GE_GL_ERROR_MSG_LENGTH];
                glGetProgramInfoLog(p, R8GE_GL_ERROR_MSG_LENGTH, &log_length, message);
                R8GE_LOG_ERROR("GL program failed to link: {}", std::string_view(message, R8GE_GL_ERROR_MSG_LENGTH));
                return false;
            }

            glDeleteShader(vs);
            glDeleteShader(fs);

            m_programs[program.getId()] = p;
            program.setValid();

            R8GE_LOG("GL Program [r8ge:{},gl:{}] compiled and created", program.getId(), p);

            return true;
        }

        bool GLService::compileShader(GLuint shader, std::string_view source, std::string_view type) {
            const std::string shaderSource = std::string(source);
            char *ptr = const_cast<char *>(shaderSource.c_str());
            glShaderSource(shader, 1, &ptr, nullptr);
            glCompileShader(shader);
            int result;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
            if (result != GL_TRUE) {
                GLsizei log_length = 0;
                char message[R8GE_GL_ERROR_MSG_LENGTH];
                glGetShaderInfoLog(shader, R8GE_GL_ERROR_MSG_LENGTH, &log_length, message);
                R8GE_LOG_ERROR("Failed to compile [{}] :\n\n {}", type, std::string(message));
                return false;
            }
            return true;
        }

        void GLService::setUniformBool(Program &program, const std::string &name, bool value) {
            glUniform1i(glGetUniformLocation(m_programs[program.getId()], name.c_str()), (int) value);
        }

        void GLService::setUniformInt(Program &program, const std::string &name, int value) {
            glUniform1i(glGetUniformLocation(m_programs[program.getId()], name.c_str()), value);
        }

        void GLService::setUniformFloat(Program &program, const std::string &name, float value) {
            glUniform1f(glGetUniformLocation(m_programs[program.getId()], name.c_str()), value);
        }

        void GLService::setUniformVec2(Program &program, const std::string &name, const glm::vec2 &value) {
            glUniform2fv(glGetUniformLocation(m_programs[program.getId()], name.c_str()), 1, &value[0]);
        }

        void GLService::setUniformVec2(Program &program, const std::string &name, float x, float y) {
            glUniform2f(glGetUniformLocation(m_programs[program.getId()], name.c_str()), x, y);
        }

        void GLService::setUniformVec3(Program &program, const std::string &name, const glm::vec3 &value) {
            glUniform3fv(glGetUniformLocation(m_programs[program.getId()], name.c_str()), 1, &value[0]);
        }

        void GLService::setUniformVec3(Program &program, const std::string &name, float x, float y, float z) {

            glUniform3f(glGetUniformLocation(m_programs[program.getId()], name.c_str()), x, y, z);
        }

        void GLService::setUniformVec4(Program &program, const std::string &name, const glm::vec4 &value) {
            glUniform4fv(glGetUniformLocation(m_programs[program.getId()], name.c_str()), 1, &value[0]);
        }

        void GLService::setUniformVec4(Program &program, const std::string &name, float x, float y, float z, float w) {
            glUniform4f(glGetUniformLocation(m_programs[program.getId()], name.c_str()), x, y, z, w);
        }

        void GLService::setUniformMat2(Program &program, const std::string &name, const glm::mat2 &mat) {
            glUniformMatrix2fv(glGetUniformLocation(m_programs[program.getId()], name.c_str()), 1, GL_FALSE,
                               &mat[0][0]);
        }

        void GLService::setUniformMat3(Program &program, const std::string &name, const glm::mat3 &mat) {
            glUniformMatrix3fv(glGetUniformLocation(m_programs[program.getId()], name.c_str()), 1, GL_FALSE,
                               &mat[0][0]);
        }

        void GLService::setUniformMat4(Program &program, const std::string &name, const glm::mat4 &mat) {
            glUniformMatrix4fv(glGetUniformLocation(m_programs[program.getId()], name.c_str()), 1, GL_FALSE,
                               &mat[0][0]);
        }

        unsigned int GLService::getUniformLocation(Program &program, const std::string &name) {
            return glGetUniformLocation(m_programs[program.getId()], name.c_str());
        }

    }
}