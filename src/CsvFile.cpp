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
    dataseet = argv[1];
    binFile = argv[2];
}

// read the csv file and return a vector of reviews
auto CsvFile::read() -> std::unique_ptr<std::vector<Review>>
{
    /*if (exists(binFile) && is_regular_file(binFile))
    {
        std::cout << "File already exists.\n";
        return nullptr;
    }*/
    // se o arquivo existir nao ha necessidade de reescreve-lo
    auto file = bufferingFile();
    // file to stringstream
    std::stringstream stream(reinterpret_cast<char*>(file->data()));
    auto reviews = std::make_unique<std::vector<Review>>();
    // skip first line from file
    std::string temp;
    std::getline(stream, temp);

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
            // remove every /n from text
            // review.text.erase(std::remove(review.text.begin(), review.text.end(), '/n'), review.text.end());
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