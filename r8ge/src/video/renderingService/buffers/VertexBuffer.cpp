#include "VertexBuffer.h"

namespace r8ge {
    namespace video {
        VertexBuffer::~VertexBuffer() = default;

        void VertexBuffer::setLayout(const VertexBufferLayout &layout) {
            m_layout = layout;
        }

        const VertexBufferLayout &VertexBuffer::getLayout() const {
            return m_layout;
        }

        VertexBuffer::VertexBuffer(const std::vector<uint8_t> &data, const VertexBufferLayout &layout) {
            m_data = data;
            m_layout = layout;
        }

        void VertexBuffer::setData(const std::vector<uint8_t> &data) {
            m_data = data;
        }

        VertexBuffer::VertexBuffer() = default;
    }
}