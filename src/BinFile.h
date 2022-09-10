//
// Created by Daniel on 29/08/2022.
//

#ifndef ED2_REWORK_BINFILE_H
#define ED2_REWORK_BINFILE_H

#include <filesystem>
#include <vector>
#include "File.h"

class Review;

class BinFile : public File
{
private:

public:
    BinFile(int argc, char *argv[]);

    void write(std::unique_ptr<std::vector<Review>> reviews);

    auto read() -> std::unique_ptr<std::vector<Review>>;

    // acess any review in the file
    auto getReview(unsigned long index) -> Review;
};


#endif //ED2_REWORK_BINFILE_H
