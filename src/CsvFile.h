//
// Created by Daniel on 28/08/2022.
//

#ifndef ED2_REWORK_CSVFILE_H
#define ED2_REWORK_CSVFILE_H

#include <filesystem>
#include <vector>
#include "File.h"

class Review;

class CsvFile : public File
{
private:
    unsigned long reviewsCount{0};
    std::filesystem::path binPath;

public:
    CsvFile(int argc, char *argv[]);

    CsvFile(const std::string &path);

    auto read() -> std::unique_ptr<std::vector<Review>>;

    auto getReviewsCount() -> unsigned long
    { return reviewsCount; }
};


#endif //ED2_REWORK_CSVFILE_H
