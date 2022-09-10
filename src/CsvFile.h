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

public:
    CsvFile(int argc, char *argv[]);

    auto read() -> std::unique_ptr<std::vector<Review>>;
};


#endif //ED2_REWORK_CSVFILE_H
