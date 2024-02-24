#ifndef R8GE_TEXTURE2D_H
#define R8GE_TEXTURE2D_H

namespace r8ge {
    namespace video {
        class Texture2D {
        public:
            Texture2D();

            Texture2D(const std::string &pathToFile, bool flipTexture);

            ~Texture2D();

            [[nodiscard]] uint16_t getWidth() const;

            [[nodiscard]] uint16_t getHeight() const;

            [[nodiscard]] uint16_t getChannelsCount() const;

            [[nodiscard]] void *getImageData() const;

            [[nodiscard]] bool getFlipState() const;

            [[nodiscard]] std::string getType() const;

            void setType(const std::string &type);

            void loadTextureFromFile(const std::string &pathToFile, bool flipTexture);

        protected:
            int32_t m_width{}, m_height{}, m_channelsCount{};
            void *m_imageData{};
            bool m_isFlipped = false;
            std::string m_type{};
        };
    }
} // r8ge

#endif //R8GE_TEXTURE2D_H
