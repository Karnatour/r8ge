#ifndef R8GE_PROGRAM_H
#define R8GE_PROGRAM_H

#include <string>

#include "../buffers/VertexBufferLayout.h"


namespace r8ge {
    namespace video {
        class Program {
        public:
            explicit Program(std::string_view source);

            [[nodiscard]] bool isValid() const;

            void setValid();

            [[nodiscard]] VertexBufferLayout getLayout() const;

            // TODO: Layout should be read from shader
            void setLayout(const VertexBufferLayout &layout);

            [[nodiscard]] size_t getId() const;

            [[nodiscard]] std::string getVertexShader() const;

            [[nodiscard]] std::string getFragmentShader() const;

        private:
            static unsigned long m_nextID;
            unsigned long m_id;
            std::string m_source;
            VertexBufferLayout m_layout;
            bool m_valid;
        };
    }
}

#endif//!R8GE_PROGRAM_H
