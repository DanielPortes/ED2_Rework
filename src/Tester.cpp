//
// Created by Daniel on 05/05/2023.
//

#include <iostream>
#include <random>

#include "Tester.h"
#include "CsvFile.h"
#include "BinFile.h"
#include "Review.h"

// auto Tester::getInput() -> unsigned long
//{
//     unsigned long input;
//     while (!(std::cin >> input))
//     {
//         std::cout << "Invalid input. Try again: ";
//         std::cin.clear();
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     }
//     return input;
// }

template <typename T>
T Tester::getInput(std::string message)
{
    T input;
    std::string inputString;
    while (true)
    {
        std::cout << message;
        std::getline(std::cin, inputString);

        std::stringstream ss(inputString);
        if (ss >> input && ss.eof())
        {
            break;
        }
        std::cout << "Invalid input. Try again.\n";
    }
    return input;
}

// Part I
auto Tester::accessReview() -> void
{
    //    access any review in the file
    auto userInput = this->getInput<long>("Enter the review number: ");
    auto review = this->binFile->getReview(userInput);
    std::cout << review << std::endl;
}

auto Tester::accessNRandomReviews() -> void
{
    // ask the user for console output or txt output
    std::string messageWelcome = "Do you want to print the output in the console or in a txt file?\n"
                                 "1 - Console\n"
                                 "2 - Txt file\n"
                                 "Your choice: ";
    auto mainChoice = this->getInput<int>(messageWelcome);

    std::string messageChoice = "How many reviews do you want to import?\n"
                                "Your choice: ";
    auto reviewsCount = this->getInput<unsigned long>(messageChoice);

    std::cout << "\nImporting...\n";

    //  get N random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, this->binFile->getReviewsCount() - 1);

    auto randomNumbers = std::make_unique<std::vector<long>>(reviewsCount);
    for (int i = 0; i < reviewsCount; ++i)
    {
        (*randomNumbers)[i] = dis(gen);
    }

    auto randomReviews = std::make_unique<std::vector<Review>>(reviewsCount);
    for (int i = 0; i < reviewsCount; ++i)
    {
        (*randomReviews)[i] = this->binFile->getReview((*randomNumbers)[i]);
    }

    for (const auto &review : *randomReviews)
    {
        std::cout << review << std::endl;
    }
}

Tester::Tester(int argc, char **argv)
{
    if (argc != 3)
    {
        throw std::invalid_argument("Error program arguments");
    }
    this->csvFile = std::make_unique<CsvFile>(argv[1]);
    this->binFile = std::make_unique<BinFile>(argv[1], argv[2]);
}

template <typename T>
auto Tester::exportToFileOrConsole(std::unique_ptr<std::vector<T>> &reviews,
                                   const File &file) -> void
{
    for (auto &review : *reviews)
    {
        file << review;
    }
}