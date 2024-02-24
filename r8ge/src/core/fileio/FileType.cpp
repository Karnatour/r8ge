#include "FileType.h"

namespace r8ge {
    std::string FileType::to_string() const {
        switch (m_type) {
            case JSON:
                return "JSON";
            case TEXT:
                return "TEXT";
            case BINARY:
                return "BINARY";
            case WAVE:
                return "WAVE";
            case GLSL:
                return "GLSL";
            case GLTF:
                return "GLTF";
        }
        return "UNKNOWN";
    }

    FileType::FileType() : m_type(TEXT) {}

    FileType::FileType(FileType::_type ft) : m_type(ft) {}

    FileType::_type FileType::operator()() const {
        return m_type;
    }
}