//
// Created by karnatour on 18.1.24.
//

#ifndef R8GE_GLFRAMEBUFFER_H
#define R8GE_GLFRAMEBUFFER_H

#include <r8ge/r8ge.h>

namespace r8ge {
    namespace video {

        class GLFrameBuffer {
        public:
            GLFrameBuffer(float width, float height);

            ~GLFrameBuffer();

            uint32_t getFrameTexture();

            void rescaleFrameBuffer(float width, float height);

            void bind() const;

            void unbind() const;
        private:
            uint32_t m_fbo;
            uint32_t m_texture;
            uint32_t m_rbo;
            uint16_t m_count;
        };

    } // r8ge
} // video

#endif //R8GE_GLFRAMEBUFFER_H
