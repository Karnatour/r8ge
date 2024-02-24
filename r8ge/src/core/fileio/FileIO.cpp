#include "FileIO.h"


#include "../Logger.h"
#include "../Core.h"

#include <fstream>
#include <iostream>
#include <istream>

namespace r8ge {
    namespace global {
        FileIO* fileIO = nullptr;
    }

    FileIO::FileIO(size_t filelimit) : m_fileCount(0), m_fileLimit(filelimit) {

    }

    FileIO::~FileIO() {
        if(m_fileCount)
        {
            R8GE_LOG_WARNI("FileIO is being destroyed, {} files were not removed", m_fileCount);
        }

        for(auto& path : getTxtFiles())
            remove(path);

        for(auto& path : getBinFiles())
            remove(path);

    }

    void FileIO::add(std::string_view path, FileType ft) {
        std::lock_guard<std::mutex> lock(m_mutex);

        if(
                m_txtFileMap.find(path.data()) != m_txtFileMap.end() ||
                m_binFileMap.find(path.data()) != m_binFileMap.end()) {
            R8GE_LOG_WARNI("file {} is already present in FileIO", path);
            return;
        }


        if(ft()!=FileType::TEXT && ft()!=FileType::BINARY) {
            R8GE_LOG_ERROR("Trying to add file {} with invalid FileType {}", path, ft.to_string());
            return;
        }

        if(m_fileCount >= m_fileLimit) {
            R8GE_LOG_ERROR("File limit reached, cannot add file {}", path);
            return;
        }

        if(ft()==FileType::TEXT)
            m_txtFileMap[path.data()] = "";
        if(ft()==FileType::BINARY)
            m_binFileMap[path.data()] = std::vector<byte>();
        m_fileCount++;
        m_modifiedMap[path.data()] = false;
        m_fileTypeMap[path.data()] = ft;
    }

    void FileIO::save(std::string_view path) {
        if(!isFilePresent(path)) return;
        auto isbin = isBinary(path);

        m_mutex.lock();
        if(isbin) {
            std::ofstream file(path.data(), std::ios::binary);
            file.write((char*)m_binFileMap[path.data()].data(), m_binFileMap[path.data()].size());
            file.close();
        } else {
            std::ofstream file(path.data());
            file << m_txtFileMap[path.data()] << '\n';
            file.close();
        }

        m_modifiedMap[path.data()] = false;
        m_mutex.unlock();
    }

    void FileIO::load(std::string_view path) {
        if(!isFilePresent(path)) return;
        auto isbin = isBinary(path);

        m_mutex.lock();
        if(isbin) {
            std::ifstream file(path.data(), std::ios::binary);
            std::vector<byte> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            m_binFileMap[path.data()] = data;
            file.close();
        } else {
            std::ifstream file(path.data());
            std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            m_txtFileMap[path.data()] = data;
            file.close();
        }
        m_modifiedMap[path.data()] = false;
        m_mutex.unlock();
    }

    void FileIO::remove(std::string_view path) {
        if(!isFilePresent(path)) return;
        auto isbin = isBinary(path);

        m_mutex.lock();
        m_fileCount--;
        if(isbin)
            m_binFileMap.erase(path.data());
        else
            m_txtFileMap.erase(path.data());

        if(m_modifiedMap[path.data()])
            R8GE_LOG_WARNI("File {} was not saved", path);

        m_mutex.unlock();
    }

    size_t FileIO::getFileCount() {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_fileCount;
    }

    size_t FileIO::getFileLimit() {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_fileLimit;
    }

    bool FileIO::isFilePresent(std::string_view path, bool log) {
        std::lock_guard<std::mutex> lock(m_mutex);

        if(m_txtFileMap.find(path.data()) != m_txtFileMap.end()) return true;
        if(m_binFileMap.find(path.data()) != m_binFileMap.end()) return true;

        if(log)
            R8GE_LOG_WARNI("file {} is not present in FileIO", path);

        return false;
    }

    size_t FileIO::getFileSize(std::string_view path){
        if(!isFilePresent(path)) return 0;

        if(isText(path)) {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_txtFileMap[path.data()].size();
        }

        if(isBinary(path)) {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_binFileMap[path.data()].size();
        }

        return 0;
    }

    size_t FileIO::getTotalSize(){
        size_t totalSize = 0;

        m_mutex.lock();
        for(auto& [path, data] : m_txtFileMap)
            totalSize += data.size();
        for(auto& [path, data] : m_binFileMap)
            totalSize += data.size();
        m_mutex.unlock();

        return totalSize;
    }

    bool FileIO::isBinary(std::string_view path) {
        if(!isFilePresent(path)) return false;
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_fileTypeMap[path.data()]() == FileType::BINARY;
    }

    std::string FileIO::getTextData(std::string_view path) {
        if(!isFilePresent(path)) return "";
        if(!isText(path))
        {
            R8GE_LOG_ERROR("Trying to get text data from a binary file: {}", path);
            return "";
        }

        std::lock_guard<std::mutex> lock(m_mutex);
        return m_txtFileMap[path.data()];
    }

    std::vector<byte> FileIO::getBinaryData(std::string_view path) {
        if(!isFilePresent(path)) return{};
        if(!isBinary(path))
        {
            R8GE_LOG_ERROR("Trying to get binary data from a text file: {}", path);
            return{};
        }

        std::lock_guard<std::mutex> lock(m_mutex);
        return m_binFileMap[path.data()];
    }

    bool FileIO::isText(std::string_view path) {
        return !isBinary(path);
    }

    std::vector<std::string> FileIO::getTxtFiles() {
        std::vector<std::string> txtFiles;
        std::lock_guard<std::mutex> lock(m_mutex);
        for(auto& [path, _] : m_txtFileMap)
            txtFiles.push_back(path);
        return txtFiles;
    }

    std::vector<std::string> FileIO::getBinFiles() {
        std::vector<std::string> binFiles;
        std::lock_guard<std::mutex> lock(m_mutex);
        for(auto& [path, _] : m_binFileMap)
            binFiles.push_back(path);
        return binFiles;
    }

    void FileIO::setTextData(std::string_view path, std::string_view data) {
        if(!isFilePresent(path)) return;
        if(isBinary(path))
        {
            R8GE_LOG_ERROR("Trying to set text data to a binary file: {}", path);
            return;
        }
        std::lock_guard<std::mutex> lock(m_mutex);
        m_txtFileMap[path.data()] = data;
        m_modifiedMap[path.data()] = true;
    }

    void FileIO::setBinaryData(std::string_view path, const std::vector<byte> &data) {
        if(!isFilePresent(path)) return;
        if(isText(path))
        {
            R8GE_LOG_ERROR("Trying to set binary data to a text file: {}", path);
            return;
        }
        std::lock_guard<std::mutex> lock(m_mutex);
        m_binFileMap[path.data()] = data;
        m_modifiedMap[path.data()] = true;
    }

    void FileIO::appendTextData(std::string_view path, std::string_view data) {
        if(!isFilePresent(path)) return;
        if(isBinary(path))
        {
            R8GE_LOG_ERROR("Trying to append text data to a binary file: {}", path);
            return;
        }

        std::lock_guard<std::mutex> lock(m_mutex);
        m_txtFileMap[path.data()] += data;
        m_modifiedMap[path.data()] = true;
    }

    void FileIO::appendBinaryData(std::string_view path, const std::vector<byte> &data) {
        if(!isFilePresent(path)) return;
        if(isText(path))
        {
            R8GE_LOG_ERROR("Trying to append binary data to a text file: {}", path);
            return;
        }

        std::lock_guard<std::mutex> lock(m_mutex);
        m_binFileMap[path.data()].insert(m_binFileMap[path.data()].end(), data.begin(), data.end());
        m_modifiedMap[path.data()] = true;
    }

    bool FileIO::isModified(std::string_view path) {
        return m_modifiedMap[path.data()];
    }

    void FileIO::copy(std::string_view path, std::string_view newPath) {
        if(!isFilePresent(path)) return;
        if(isFilePresent(newPath, false))
        {
            R8GE_LOG_ERROR("Trying to copy file {} to {} but {} already exists", path, newPath, newPath);
            return;
        }

        auto isbin = isBinary(path);

        if(isbin) {
            add(newPath, FileType::BINARY);
            setBinaryData(newPath, getBinaryData(path));
        }
        else {
            add(newPath, FileType::TEXT);
            setTextData(newPath, getTextData(path));
        }
        save(newPath);
        remove(newPath);
    }

    void FileIO::writeStdout(std::string_view data) {
        m_stdoutMutex.lock();
        std::cout << data;
        m_stdoutMutex.unlock();
    }


    void FileIO::writeStderr(std::string_view data) {
        m_stdoutMutex.lock();
        std::cerr << data;
        m_stdoutMutex.unlock();
    }

    std::string FileIO::readStdin() {
        std::string data;
        m_stdinMutex.lock();
        std::getline(std::cin, data);
        m_stdinMutex.unlock();
        return data;
    }

    std::vector<std::string> FileIO::readStdinVec() {
        auto raw = readStdin();
        std::vector<std::string> data;

        while(raw.size()){
            int index = raw.find(' ');
            if(index!=std::string::npos){
                data.push_back(raw.substr(0,index));
                raw = raw.substr(index+1);
                if(raw.size()==0)data.push_back(raw);
            }else{
                data.push_back(raw);
                raw = "";
            }
        }

        return data;
    }

    void FileIO::clear(std::string_view path) {
        if(!isFilePresent(path)) return;
        auto isbin = isBinary(path);

        m_mutex.lock();
        if(isbin)
            m_binFileMap[path.data()].clear();
        else
            m_txtFileMap[path.data()].clear();
        m_mutex.unlock();
    }
}