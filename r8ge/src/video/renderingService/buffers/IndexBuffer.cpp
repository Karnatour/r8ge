#include "IndexBuffer.h"

namespace r8ge {
    namespace video {
        void IndexBuffer::setData(const std::vector<unsigned int>& data) {
           for(auto& ui : data) {
               for(int i = 0; i < sizeof(unsigned int)*8; i+=8)
                   m_data.push_back((ui >> i) & 0xFF);
           }
        }

        uint32_t IndexBuffer::getIndeciesCount() const {
            return m_data.size() / sizeof(unsigned int);
        }

        IndexBuffer::IndexBuffer(const std::vector<unsigned int>& data) {
            setData(data);
        }

        std::vector<unsigned int> IndexBuffer::getData() const {
            std::vector<unsigned int> data;
            for(int i = 0; i < m_data.size() / sizeof(unsigned int); i++)
            {
                unsigned int ui = 0;
                for(int j = 0; j < sizeof(unsigned int); j++) {
                    ui |= m_data[i*sizeof(unsigned int) + j] << (j*8);
                }
                data.push_back(ui);
            }

            return data;
        }

        IndexBuffer::IndexBuffer() = default;

        IndexBuffer::~IndexBuffer() = default;
    }
}