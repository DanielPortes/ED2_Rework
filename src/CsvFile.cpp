//
// Created by Daniel on 28/08/2022.
//

#include "CsvFile.h"
#include "Review.h"

#include <fstream>
#include <iostream>

CsvFile::CsvFile(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Error program arguments";
        exit(10);
    }
    inFile = argv[1];
    outFile = argv[2];
}

auto CsvFile::read() -> std::unique_ptr<std::vector<Review>>
{
    if (exists(outFile) && is_regular_file(outFile))
    {
        std::cout << "File already exists.\n";
        return nullptr;
    }
    // se o arquivo existir nao ha necessidade de reescreve-lo
    auto file = bufferingFile();
    // file to stringstream
    std::stringstream stream(reinterpret_cast<char*>(file->data()));
    auto reviews = std::make_unique<std::vector<Review>>();
    // skip first file from file
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int counterReviews{0};
    Review review;
    std::string line;
    while (stream.good() && stream.tellg() != file->size()) // second condition is because is reading more than the real file, why?
    {
        getline(stream, line, ',');
        review.id = line;

        if (stream.get() == '"') // if text is in quotes
        {
            while (true) // read text until last quote
            {
                std::getline(stream, line, '"');
                review.text += line;
                if (stream.get() != '"') // last quote already read
                { break; }
            }
        }
        else
        {
            stream.seekg(-1, std::ios::cur); // skip comma
            getline(stream, line, ',');
            review.text = line;
        }
        line = "0"; // empty line crashes with stoi()
        getline(stream, line, ',');
        review.upvotes = std::stoi(line);

        getline(stream, line, ',');
        review.app_version = line;

        getline(stream, line, '\n');
        review.posted_date = line;

        reviews->push_back(review);
        counterReviews++;
    }
    return reviews;
}

unsigned long CsvFile::getFileSize()
{
    return std::filesystem::file_size(this->inFile);
}

auto CsvFile::bufferingFile() -> std::unique_ptr<std::vector<unsigned char>>
{
    auto fileSize = getFileSize();
    std::ifstream file(this->inFile);
    auto input = std::make_unique<std::vector<unsigned char>>();
    input->resize(fileSize);
    file.read(reinterpret_cast<char *>(input->data()), static_cast<long>(fileSize));
    if (!file.fail() && fileSize == file.gcount())
    {
        return input;
    }
    else
    {
        throw std::runtime_error("Error reading file");
    }
}
