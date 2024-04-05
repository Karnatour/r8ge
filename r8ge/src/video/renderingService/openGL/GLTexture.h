#ifndef R8GE_GLTEXTURE_H
#define R8GE_GLTEXTURE_H

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

            [[nodiscard]] uint32_t getTexture() const;

            void bindTexture(unsigned int unit) const;

            static void unbindTexture();

        private:
            uint32_t m_texture{};
        };
    }
} // r8ge

#endif //R8GE_GLTEXTURE_H
