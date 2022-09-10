//
// Created by Daniel on 28/08/2022.
//

#ifndef ED2_REWORK_CSVFILE_H
#define ED2_REWORK_CSVFILE_H

#include <filesystem>
#include <vector>

class Review;
class CsvFile
{
private:
    std::filesystem::path inFile;
    std::filesystem::path outFile;

    unsigned long getFileSize();

    auto bufferingFile() -> std::unique_ptr<std::vector<unsigned char>>;

public:
    CsvFile(int argc, char *argv[]);
    auto read() -> std::unique_ptr<std::vector<Review>>;
};


#endif //ED2_REWORK_CSVFILE_H
