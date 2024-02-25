#ifndef R8GE_BUFFER_H
#define R8GE_BUFFER_H

#include <cstdint>
#include <vector>

namespace r8ge {
    namespace video {
        // Base class for all buffers.
        // Each buffer has its own usage, data and size.
        // Buffer is implemented by RenderingAPI, because each API has its own way
        // how to bind the buffer into GPUs memory.
        //
        // Specifies the type of the buffer.
        // Each RenderingAPI has its own implementation
        // how to bind the buffer into GPUs memory.
        //
        // NOTE: Buffer does not have any data, it only stores the data pointer and its size.
        //       The data is stored in RAM and is not copied into the buffer. So the data mustn't
        //       be deleted until the buffer is deleted or cleared.
        class Buffer
        {
        public:
            Buffer();
            virtual ~Buffer();

            // Specifies how often the data is changed and how often it is used.
            // This is used to optimize the buffer.
            enum class Usage : unsigned char {
                STATIC,  // Data is set only once and used by the GPU few times.
                DYNAMIC, // Data is changed a lot and used many times.
                VOLATILE // Data is changed every frame and used many times.
            };

            // Sets the specified usage of the usage.
            void setDrawUsage(Usage usage);

            // Resets the buffer to its default state. (nullptr, and 0 size)
            void clear();

            // Get the usage of the buffer
            [[nodiscard]] Usage getDrawUsage() const;

            // address of the data in RAM
            [[nodiscard]] std::vector<uint8_t> getRawData() const;

            // size of the data in bytes stored in RAM
            [[nodiscard]] size_t getSize() const;

        protected:
            Usage m_usage;
            std::vector<uint8_t> m_data;
        };
    }
}

#endif//!R8GE_BUFFER_H
