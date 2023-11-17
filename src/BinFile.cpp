//
// Created by Daniel on 29/08/2022.
//

#include <iostream>
#include <fstream>
#include "BinFile.h"
#include "Review.h"

BinFile::BinFile(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Error program arguments";
        exit(10);
    }
    this->path = argv[2];
}

BinFile::BinFile(File *output) {
    this->path = output->getCaminho();
}

void BinFile::write(std::unique_ptr<std::vector<Review>> reviews) {
    auto binFileExists = BinFile::checkExistence(this->path);
    if (binFileExists) {
        return;
    }
    try {
        std::filesystem::create_directories(std::filesystem::path(this->path).parent_path());
    }
    catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Error creating directory: " << std::filesystem::path(this->path).parent_path()
                  << e.what()
                  << "\n";
    }

    std::cout << "Writing binary file...\n";
    std::ofstream file(this->path, std::ios::binary);

    if (!file) {
        std::cerr << "Error opening file\n";
        exit(10);
    }

    // first write the amount of comments in the binary file
    this->reviewsCount = reviews->size();
    file.write(reinterpret_cast<const char *>(&reviewsCount), sizeof(reviewsCount));
    //   then write the reviews
    for (auto &review: *reviews) {
        file << review;
    }

    if (!file.good()) {
        std::cerr << "Error writing file\n";
        exit(10);
    }
    file.close();
}

// read the binary file and return a vector of reviews
auto BinFile::read() -> std::unique_ptr<std::vector<Review>> {
    if (!exists(this->path) || !is_regular_file(this->path)) {
        std::cout << "File does not exist.\n";
        return nullptr;
    }
    std::ifstream file(this->path, std::ios::binary);
    if (!file.good()) {
        std::cerr << "Error reading file\n";
        exit(10);
    }
    auto reviews = std::make_unique<std::vector<Review>>();

    //    first read the amount of reviews in the file
    file.read(reinterpret_cast<char *>(&reviewsCount), sizeof(reviewsCount));

    //    then read the reviews
    Review review;
    while (file.good()) {
        file >> review;
        reviews->push_back(review);
    }
    return reviews;
}

auto BinFile::getReview(long index) -> Review {
    // Validate the index
    if (index >= this->getReviewsCount()) {
        throw std::out_of_range("Index out of range");
    }

    // access any review in the file
    std::ifstream file(this->getBinPath(), std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        exit(10);
    }
    //    first ignore the amount of reviews in the file
    file.ignore(sizeof(reviewsCount));

    Review review;
    for (long i = 0; i < index; i++) {
        file >> review;
    }

    file.close();
    return review;
}

const std::filesystem::path &BinFile::getBinPath() const {
    return binPath;
}

BinFile::BinFile(std::unique_ptr<File> output) {
    this->path = output->getCaminho();
}

BinFile::BinFile(const std::string &path, const std::string &binPath) {
    this->path = path;
    this->binPath = binPath;
}

auto BinFile::getReviewsCount() -> const unsigned long {
    //    read the first line from binFile that contains the amount of reviews
    if (this->reviewsCount != 0) {
        return this->reviewsCount;
    }

    std::ifstream file(this->getBinPath(), std::ios::binary);
    if (!file.good()) {
        std::cerr << "Error reading file\n";
        exit(10);
    }
    file.read(reinterpret_cast<char *>(&reviewsCount), sizeof(reviewsCount));
    file.close();
//    std:: cout << "\nReviews count: " << reviewsCount << std::endl;
    return reviewsCount;
}

const std::filesystem::path &BinFile::getBinpath() const {
    return binPath;
}
