#include "Buffer.h"


namespace r8ge {
    namespace video {
        void Buffer::setDrawUsage(Buffer::Usage usage) {
            m_usage = usage;
        }

        Buffer::Usage Buffer::getDrawUsage() const {
            return m_usage;
        }

        Buffer::Buffer() : m_usage(Usage::STATIC), m_data({}) {}

        std::vector<uint8_t> Buffer::getRawData() const {
            if(!m_data.empty())
                return m_data;
            R8GE_LOG_WARNI("Vertex buffer data is null");
            return{};
        }

        size_t Buffer::getSize() const {
            if(!m_data.empty())
                return m_data.size();
            R8GE_LOG_WARNI("Vertex buffer size is 0");
            return 0;
        }

        void Buffer::clear() {
            m_data.clear();
        }

        Buffer::~Buffer() = default;
    }
}
