#ifndef R8GE_FILE_H
#define R8GE_FILE_H

#include <string>
#include <fstream>
#include <mutex>
#include <memory>
#include <variant>

#include "FileReader.h"
#include "FileType.h"
#include "../Logger.h"

#include "fileReaders/Text.h"

#include <concepts>

namespace r8ge {
    class _File {
    public:
        _File(std::string_view path, FileType ft = {});
        virtual ~_File();
        [[nodiscard]] std::string getPath() const;
        [[nodiscard]] FileType getFileType() const;

        void copy(std::string_view path);
    private:
        std::string m_path;
        FileType m_fileType;
    };

    template<isFileReader T>
    class File final : public _File {
    public:
        explicit File(std::string_view path):
        _File(path, T::getType()()), m_file(std::make_unique<T>(path))
        {}

        [[nodiscard]] T& get() {
            return *m_file;
        }

        [[nodiscard]] T* operator->() {
            return m_file.get();
        }

        [[nodiscard]] T& operator*() {
            return *m_file;
        }
    private:
        std::unique_ptr<T> m_file;
    };
}

#endif//!R8GE_FILE_H
