//
// Created by Daniel on 29/08/2022.
//

#include <iostream>
#include <fstream>
#include "BinFile.h"
#include "Review.h"

BinFile::BinFile(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Error program arguments";
        exit(10);
    }
    this->dataseet = argv[1];
    this->binFile = argv[2];
}

void BinFile::write(std::unique_ptr<std::vector<Review>> reviews)
{
/*
 * if (exists(this->binFile) && is_regular_file(this->binFile))
    {
        std::cout << "File already exists.\n";
        return;
    }
    */
    std::ofstream file(this->binFile, std::ios::binary | std::ios::trunc);
    for (auto &review: *reviews)
    {
        file << review;
    }

    if (!file.good())
    {
        std::cerr << "Error writing file\n";
        exit(10);
    }
}

// read the binary file and return a vector of reviews
auto BinFile::read() -> std::unique_ptr<std::vector<Review>>
{
    if (!exists(this->dataseet) || !is_regular_file(this->dataseet))
    {
        std::cout << "File does not exist.\n";
        return nullptr;
    }
    std::ifstream file(this->dataseet, std::ios::binary);
    auto reviews = std::make_unique<std::vector<Review>>();
    Review review;
    while (file.good())
    {
        file >> review;
        reviews->push_back(review);
    }
    return reviews;
}

auto BinFile::getReview(unsigned long index) -> Review
{
    // access any review in the file
    std::ifstream file(this->binFile, std::ios::binary);
    if (!file.good())
    {
        std::cerr << "Error reading file\n";
        exit(10);
    }
    Review review;
    for (unsigned long i = 0; i < index; i++)
    {
        file >> review;
    }
    return review;
}
