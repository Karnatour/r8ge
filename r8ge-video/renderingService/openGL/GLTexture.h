#ifndef R8GE_GLTEXTURE_H
#define R8GE_GLTEXTURE_H

#include <r8ge/r8ge.h>
#include "../textures/Texture2D.h"

namespace r8ge {
    namespace video {
        class GLTexture : public Texture2D {
        public:
            GLTexture();

            GLTexture(const std::string &pathToFile,
                      bool flipTexture);

            ~GLTexture();

            void setData(const Texture2D &texture2D);

            void updateData(void *data);

            void bindTexture(unsigned int unit) const;

        private:
            uint32_t m_texture{};
        };
    }
} // r8ge

#endif //R8GE_GLTEXTURE_H
