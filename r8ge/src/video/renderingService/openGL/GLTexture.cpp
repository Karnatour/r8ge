//
// Created by karnatour on 4.1.24.
//

#include "GLTexture.h"
#include "../../renderingService/openGL/GLConvertor.h"
#include <GL/glew.h>


namespace r8ge {
    namespace video {

        GLTexture::GLTexture() = default;


        GLTexture::GLTexture(const std::string &pathToFile, bool flipTexture)
                : Texture2D(pathToFile, flipTexture) {
            glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);

            auto getInternalFormat = [](int channels) {
                switch (channels) {
                    case 3:
                        return GLConvertor::convertImageFormatToGLInternalFormat(ImageFormat::RGB8);
                    case 4:
                        return GLConvertor::convertImageFormatToGLInternalFormat(ImageFormat::RGBA8);
                }
            };

            auto getFormat = [](int channels) {
                switch (channels) {
                    case 3:
                        return GLConvertor::convertImageFormatToGLFormat(Format::RGB);
                    case 4:
                        return GLConvertor::convertImageFormatToGLFormat(Format::RGBA);
                }
            };

            glTextureParameteri(m_texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTextureParameteri(m_texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTextureParameteri(m_texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_texture, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTextureStorage2D(m_texture, 1, getInternalFormat(getChannelsCount()), getWidth(),
                               getHeight());
            glTextureSubImage2D(m_texture, 0, 0, 0, getWidth(), getHeight(),
                                getFormat(getChannelsCount()),
                                GL_UNSIGNED_BYTE, getImageData());
            glGenerateTextureMipmap(m_texture);
            R8GE_LOG("Created TextureSubImage2D for texture with ID:{}", m_texture);
            //TODO:FIX
            //stbi_image_free(m_imageData);
        }

        void GLTexture::updateData(void *data) {

        }

        void GLTexture::setData(const Texture2D &texture2D) {
            glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);

            auto getInternalFormat = [](int channels) {
                switch (channels) {
                    case 3:
                        return GLConvertor::convertImageFormatToGLInternalFormat(ImageFormat::RGB8);
                    case 4:
                        return GLConvertor::convertImageFormatToGLInternalFormat(ImageFormat::RGBA8);
                }
            };

            auto getFormat = [](int channels) {
                switch (channels) {
                    case 3:
                        return GLConvertor::convertImageFormatToGLFormat(Format::RGB);
                    case 4:
                        return GLConvertor::convertImageFormatToGLFormat(Format::RGBA);
                }
            };

            glTextureParameteri(m_texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTextureParameteri(m_texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTextureParameteri(m_texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_texture, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTextureStorage2D(m_texture, 1, getInternalFormat(texture2D.getChannelsCount()), texture2D.getWidth(),
                               texture2D.getHeight());
            glTextureSubImage2D(m_texture, 0, 0, 0, texture2D.getWidth(), texture2D.getHeight(),
                                getFormat(texture2D.getChannelsCount()),
                                GL_UNSIGNED_BYTE, texture2D.getImageData());
            glGenerateTextureMipmap(m_texture);
            R8GE_LOG("Created TextureSubImage2D for texture with ID:{}", m_texture);
            //TODO:FIX
            //stbi_image_free(m_imageData);
        }

        void GLTexture::bindTexture(unsigned int unit) const {
            glBindTextureUnit(unit, m_texture);
        }



        uint32_t GLTexture::getTexture() const {
            return m_texture;
        }

        void GLTexture::unbindTexture() {
            glBindTextureUnit(0, 0);
        }

        GLTexture::~GLTexture() = default;
    }
} // r8ge