#ifndef R8GE_INDEXBUFFER_H
#define R8GE_INDEXBUFFER_H

#include "Buffer.h"

namespace r8ge {
    namespace video {
        // Index buffer class, used for storing indecies of vertices
        // one of the most important buffers together with vertex buffer.
        // Index buffer is used for drawing triangles, quads, lines etc.
        // Has to be bound before every draw call.
        class IndexBuffer final : public Buffer
        {
        public:
            IndexBuffer(const std::vector<unsigned int>& data);
            IndexBuffer();
            ~IndexBuffer() override;

            // Sets data to index buffer, it is very important to set data
            // before binding index buffer and setting it as !unsigned int!
            // [count] is number of indecies, not size in bytes!
            void setData(const std::vector<unsigned int>& data);


            [[nodiscard]] uint32_t getIndeciesCount() const;
            [[nodiscard]] std::vector<unsigned int> getData() const;
        };
    }
}

#endif//!R8GE_INDEXBUFFER_H
