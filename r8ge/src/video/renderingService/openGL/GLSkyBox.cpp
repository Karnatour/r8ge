#include "GLSkyBox.h"
#include "GLConvertor.h"
#include "../textures/Texture2D.h"
#include <GL/glew.h>

namespace r8ge
{
    namespace video
    {
        GLSkyBox::GLSkyBox() = default;

        GLSkyBox::GLSkyBox(const std::vector<std::string> &paths) {
            glGenTextures(1, &m_skybox);
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_skybox);

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            for (auto i = 0; i < paths.size(); i++)
            {
                Texture2D temp(paths[i], false);
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, temp.getWidth(),
                             temp.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, temp.getImageData());
            }

            R8GE_LOG("Created TextureImage2D for skybox with ID:{}", m_skybox);
        }

        unsigned int GLSkyBox::getSkybox() {
            return m_skybox;
        }

        void GLSkyBox::bindSkybox() {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_skybox);
        }
    } // r8ge
} // video