#include "GLSkyBox.h"
#include "GLConvertor.h"
#include "../textures/Texture2D.h"
#include <GL/glew.h>

namespace r8ge
{
    namespace video
    {
        GLSkyBox::GLSkyBox() = default;

        GLSkyBox::GLSkyBox(const std::vector<std::string>& paths)
        {
            auto getInternalFormat = [](int channels)
            {
                switch (channels)
                {
                    case 3:
                        return GLConvertor::convertImageFormatToGLInternalFormat(ImageFormat::RGB8);
                    case 4:
                        return GLConvertor::convertImageFormatToGLInternalFormat(ImageFormat::RGBA8);
                }
            };

            auto getFormat = [](int channels)
            {
                switch (channels)
                {
                    case 3:
                        return GLConvertor::convertImageFormatToGLFormat(Format::RGB);
                    case 4:
                        return GLConvertor::convertImageFormatToGLFormat(Format::RGBA);
                }
            };

            glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_skybox);

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            for (const auto& i : paths)
            {
                Texture2D temp(i,false);
                glTextureStorage2D(m_skybox, 1, getInternalFormat(temp.getChannelsCount()), temp.getWidth(),
                                   temp.getHeight());
                glTextureSubImage2D(m_skybox, 0, 0, 0, temp.getWidth(), temp.getHeight(),
                                    getFormat(temp.getChannelsCount()),
                                    GL_UNSIGNED_BYTE, temp.getImageData());
                R8GE_LOG("Created TextureSubImage2D for skybox with ID:{}", m_skybox);
                //TODO:FIX
                //stbi_image_free(temp.m_imageData);
            }
        }

    } // r8ge
} // video