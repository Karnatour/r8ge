#ifndef R8GE_VERTEXBUFFER_H
#define R8GE_VERTEXBUFFER_H

#include "Buffer.h"
#include <vector>
#include <ranges>

#include "VertexBufferLayout.h"

template<typename T>
concept CanGetRawData = requires(T t) {
    {t.getRawData()} -> std::convertible_to<std::vector<uint8_t>>;
    {t.getSize()} -> std::convertible_to<size_t>;
};

namespace r8ge {
    namespace video {
        // Vertex buffer is a buffer that stores vertex data
        // It is used to store data that is used to draw objects
        // data is transferred to GPU memory. Very important thing
        // is that vertex buffer holds layout of data that is stored
        // in it. Layout is used to tell GPU (shaders) how to interpret data
        // that is stored in vertex buffer.
        class VertexBuffer final : public Buffer
        {
        public:
            VertexBuffer();

            template<CanGetRawData T>
            VertexBuffer(const std::vector<T>& data, const VertexBufferLayout& layout)
            {
                size_t vertex_size = data[0].getSize();
                std::vector<uint8_t> rawData(data.size()*vertex_size);
                std::vector<uint8_t> rawDataPart0 = data[0].getRawData();

                for(size_t i = 0; i < data.size(); ++i) {
                    auto rawDataPart = data[i].getRawData();

                    for(size_t j = 0; j < rawDataPart.size(); ++j)
                        rawData[i*vertex_size + j] = rawDataPart[j];
                }

                m_data = std::move(rawData);
                m_layout = layout;
            }

            VertexBuffer(const std::vector<uint8_t>& data, const VertexBufferLayout& layout);
            ~VertexBuffer() override;

            // Sets data to vertex buffer
            void setData(const std::vector<uint8_t>& data);

            // Sets layout of data that is stored in vertex buffer
            // very important thing is that layout must be set
            void setLayout(const VertexBufferLayout &layout);

            // Returns layout of data that is stored in vertex buffer
            [[nodiscard]] const VertexBufferLayout& getLayout() const;

            template<typename T>
            [[nodiscard]] std::vector<T> getData() {
                std::vector<T> data;

                for(size_t i = 0; i < m_data.size()/sizeof(T); ++i)
                    data.push_back(*reinterpret_cast<T*>(&m_data[i*sizeof(T)]));

                return data;
            }

        protected:
            VertexBufferLayout m_layout;
        };
    }
}

#endif//!R8GE_VERTEXBUFFER_H
