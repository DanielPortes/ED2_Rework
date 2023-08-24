//
// Created by Daniel on 29/08/2022.
//

#ifndef ED2_REWORK_BINFILE_H
#define ED2_REWORK_BINFILE_H

#include <filesystem>
#include <vector>
#include "File.h"

class Review;

/*
 * @class BinFile
 * @brief Class represents binary file
 *
 * Write and read the binary
 * */
class BinFile : public File {
private:
//    TODO:  rename superclass path to csvPath

// a problem witg BinFile is that it has two paths, one for the csv file and another for the binary file
    std::filesystem::path Path;

    std::filesystem::path binPath;

    unsigned long reviewsCount{0};


public:
    BinFile(int argc, char *argv[]);

    BinFile(const std::string &path, const std::string &binPath);

    explicit BinFile(File *output);

    explicit BinFile(std::unique_ptr<File> output);

    // acess any review in the file
    auto getReview(long index) -> Review;

    [[nodiscard]] const std::filesystem::path &getBinPath() const;

    void write(std::unique_ptr<std::vector<Review>> reviews);

    auto read() -> std::unique_ptr<std::vector<Review>>;

    auto getReviewsCount() -> const unsigned long;

    [[nodiscard]] const std::filesystem::path &getBinpath() const;


};


#endif //ED2_REWORK_BINFILE_H
