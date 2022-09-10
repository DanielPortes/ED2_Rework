//
// Created by Daniel on 29/08/2022.
//

#ifndef ED2_REWORK_FILE_H
#define ED2_REWORK_FILE_H

#include <filesystem>
#include <vector>

class File
{
private:
    std::filesystem::path inFile;
    std::filesystem::path outFile;

    unsigned long getFileSize();

    auto bufferingFile() -> std::unique_ptr<std::vector<unsigned char>>;

};


#endif //ED2_REWORK_FILE_H
