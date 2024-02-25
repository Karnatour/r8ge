#ifndef R8GE_FILETYPE_H
#define R8GE_FILETYPE_H

#include <string>
#include <memory>

namespace r8ge {
    class FileType final {
    public:
        enum _type {
            JSON,
            TEXT,
            BINARY,
            WAVE,
            GLSL,
            GLTF
        };

        FileType();
        FileType(FileType::_type ft);

        _type operator()() const;

        [[nodiscard]] std::string to_string() const;
    private:
        _type m_type;
    };
}

#endif//!R8GE_FILETYPE_H
