//
// Created by karnatour on 18.1.24.
//

#include <GL/glew.h>
#include "GLFrameBuffer.h"

namespace r8ge {
    namespace video {
        GLFrameBuffer::GLFrameBuffer() = default;


        GLFrameBuffer::~GLFrameBuffer() {
            glDeleteFramebuffers(1, &m_fbo);
            glDeleteTextures(1, &m_texture);
            glDeleteRenderbuffers(1, &m_rbo);
        }

        uint32_t GLFrameBuffer::getFrameTexture() {
            return m_texture;
        }

        void GLFrameBuffer::rescaleFrameBuffer(float width, float height) {
            glBindTexture(GL_TEXTURE_2D, m_texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

            glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
        }

        void GLFrameBuffer::bind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

        }

        void GLFrameBuffer::unbind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void GLFrameBuffer::setBuffer(float width, float height) {
            glGenFramebuffers(1, &m_fbo);
            glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

            glGenTextures(1, &m_texture);
            glBindTexture(GL_TEXTURE_2D, m_texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

            glGenRenderbuffers(1, &m_rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                R8GE_LOG_ERROR("Framebuffer is not complete");
            glBindFramebuffer(GL_FRAMEBUFFER, 0);


        }

    } // r8ge
} // video

/*
//
// Created by karnatour on 18.1.24.
//

#include <GL/glew.h>
#include "GLFrameBuffer.h"

namespace r8ge {
    namespace video {
        GLFrameBuffer::GLFrameBuffer() = default;


        GLFrameBuffer::~GLFrameBuffer() {
            glDeleteFramebuffers(1, &m_fbo);
            glDeleteTextures(1, &m_texture);
            glDeleteRenderbuffers(1, &m_rbo);
        }

        uint32_t GLFrameBuffer::getFrameTexture() {
            return m_texture;
        }

        void GLFrameBuffer::rescaleFrameBuffer(float width, float height) {
            glBindTexture(GL_TEXTURE_2D, m_texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

            glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
        }

        void GLFrameBuffer::bind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

        }

        void GLFrameBuffer::unbind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void GLFrameBuffer::setBuffer(float width, float height) {
            glCreateFramebuffers(1,&m_fbo);

            glCreateTextures(GL_TEXTURE_2D,1,&m_texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTextureStorage2D(m_texture,1,GL_RGB8,width,height);
            glNamedFramebufferTexture(m_fbo,GL_COLOR_ATTACHMENT0,m_texture,0);

            glCreateRenderbuffers(1,&m_rbo);

            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

            auto fboStatus = glCheckNamedFramebufferStatus(m_fbo,GL_FRAMEBUFFER);
            if (fboStatus != GL_FRAMEBUFFER_COMPLETE){
                R8GE_LOG_ERROR("Framebuffer error: ",fboStatus);
            }

            glBindFramebuffer(GL_FRAMEBUFFER, 0);


        }

    } // r8ge
} // video
*/