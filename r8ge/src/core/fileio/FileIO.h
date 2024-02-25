#ifndef R8GE_FILEIO_H
#define R8GE_FILEIO_H

#include <unordered_map>
#include <string>
#include <mutex>
#include <vector>

#include "FileType.h"

namespace r8ge {
    using byte = unsigned char;

    class FileIO final {
    public:
        explicit FileIO(size_t filelimit);
        ~FileIO();

        void add(std::string_view path, FileType ft);
        void save(std::string_view path);
        void load(std::string_view path);
        void remove(std::string_view path);

        void clear(std::string_view path);

        void writeStderr(std::string_view data);
        void writeStdout(std::string_view data);
        [[nodiscard]] std::string readStdin();
        [[nodiscard]] std::vector<std::string> readStdinVec();

        [[nodiscard]] size_t getFileCount();
        [[nodiscard]] size_t getFileLimit();
        [[nodiscard]] bool isFilePresent(std::string_view path, bool log = 1);
        [[nodiscard]] size_t getFileSize(std::string_view path);
        [[nodiscard]] size_t getTotalSize();

        [[nodiscard]] std::string getTextData(std::string_view path);
        [[nodiscard]] std::vector<byte> getBinaryData(std::string_view path);

        void setTextData(std::string_view path, std::string_view data);
        void setBinaryData(std::string_view path, const std::vector<byte>& data);

        void appendTextData(std::string_view path, std::string_view data);
        void appendBinaryData(std::string_view path, const std::vector<byte>& data);

        [[nodiscard]] bool isModified(std::string_view path);

        [[nodiscard]] bool isBinary(std::string_view path);
        [[nodiscard]] bool isText(std::string_view path);

        [[nodiscard]] std::vector<std::string> getTxtFiles();
        [[nodiscard]] std::vector<std::string> getBinFiles();

        void copy(std::string_view path, std::string_view newPath);
    private:

        std::unordered_map<std::string, std::string> m_txtFileMap;
        std::unordered_map<std::string, std::vector<byte>> m_binFileMap;
        std::unordered_map<std::string, FileType> m_fileTypeMap;
        std::unordered_map<std::string, bool> m_modifiedMap;

        const size_t m_fileLimit;
        size_t m_fileCount;
        std::mutex m_mutex;
        std::mutex m_stdinMutex;
        std::mutex m_stdoutMutex;
    };

    namespace global{
        extern FileIO* fileIO;
    }
}

#endif//!R8GE_FILEIO_H
