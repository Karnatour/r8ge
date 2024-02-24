#ifndef R8GE_FILEREADER_H
#define R8GE_FILEREADER_H

#include "FileType.h"

namespace r8ge {
    class FileReader {
    public:
        FileReader(std::string_view path);

        virtual ~FileReader() = 0;

        void save() const;
        void load() const;

        void clear() const;

        [[nodiscard]] size_t size() const;

    protected:
        std::string m_path;
    };

    template <typename T>
    concept isFileReader = std::is_base_of_v<FileReader, T>;
}

#endif//!R8GE_FILEREADER_H
