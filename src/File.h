//
// Created by Daniel on 29/08/2022.
//

#ifndef ED2_REWORK_FILE_H
#define ED2_REWORK_FILE_H

#include <filesystem>
#include <vector>

class File
{
protected:
    std::filesystem::path path;

    unsigned long getFileSize();

    auto bufferingFile() -> std::unique_ptr<std::vector<unsigned char>>;

    static auto checkExistence(const std::filesystem::path &) -> bool;

public:
    explicit File(const std::string &path);

    File() = default;

    auto getCaminho() -> std::filesystem::path
    { return path; }

    template<class T>
    friend File &operator<<(File &file, const std::vector<T> &vec);
};


#endif //ED2_REWORK_FILE_H
