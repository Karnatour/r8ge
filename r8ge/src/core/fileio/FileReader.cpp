#include "FileReader.h"

#include "../Core.h"

#include "fileReaders/Text.h"
#include "fileReaders/Glsl.h"
#include "FileIO.h"

namespace r8ge {
    FileReader::FileReader(std::string_view  path) : m_path(path) {}
    FileReader::~FileReader() = default;

    void FileReader::save() const {
        global::fileIO->save(m_path);
    }

    void FileReader::load() const {
        global::fileIO->load(m_path);
    }

    size_t FileReader::size() const {
        return global::fileIO->getFileSize(m_path);
    }

    void FileReader::clear() const {
        global::fileIO->clear(m_path);
    }
}