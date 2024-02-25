#ifndef R8GE_TEXT_H
#define R8GE_TEXT_H

#include "../FileReader.h"

#include <vector>

namespace r8ge {
    namespace reader {
        class Text : public FileReader {
        public:
            Text(std::string_view path);
            virtual ~Text() override;

            [[nodiscard]] std::string readFile() const;
            [[nodiscard]] std::vector<std::string> readLines() const;
            [[nodiscard]] size_t lineNumber() const;

            void write(std::string_view buffer);
            void write(const std::vector<std::string_view>& buffer);

            void append(std::string_view  buffer);
            void append(const std::vector<std::string_view>& buffer);
            void append(char c);

            void appendNewLine();

            void appendNewLine(std::string_view  buffer);
            void appendNewLine(const std::vector<std::string_view>& buffer);
            void appendNewLine(char c);

            static FileType getType();
        };
    }
}

#endif//!R8GE_TEXT_H
