//
// Created by Daniel on 05/05/2023.
//

#include <iostream>
#include <random>
#include <fstream>

#include "Tester.h"
#include "CsvFile.h"
#include "BinFile.h"
#include "Review.h"

// helper function to get input from the user
template<typename T>
T getUserInputFromConsole(std::string message) {
    T input;
    std::string inputString;
    while (true) {
        std::cout << message;
        std::getline(std::cin, inputString);

        std::stringstream ss(inputString);
        if (ss >> input && ss.eof()) {
            break;
        }
        std::cout << "Invalid input. Try again.\n";
    }
    return input;
}

// Part I
auto Tester::accessReview() -> void {
    //    access any review in the file
    auto userInput = getUserInputFromConsole<long>("Enter the review number: ");
    auto review = this->binFile->getReview(userInput);
    std::cout << review << std::endl;
}

enum class OutputType {
    Console = 1,
    File
};

auto returnVectorWithRandomNumbers(auto totalNReviews, std::shared_ptr<BinFile> binFile) {


    //  get N random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, static_cast<int>(binFile->getReviewsCount()) - 1);

    //    populate the vector with N random numbers
    auto randomNumbers = std::make_unique<std::vector<long>>(totalNReviews);
    for (int i = 0; i < totalNReviews; ++i) {
        (*randomNumbers)[i] = dis(gen);
    }
    return randomNumbers;
}

auto Tester::accessNRandomReviews() -> void {
    // ask the user for console output or txt output
    std::cout << "Do you want to print the output in the console or in a txt file?\n"
                 "1 - Console\n"
                 "2 - File\n"
                 "Your choice: ";

    //    get the user choice to export to console or file
    auto mainChoice = getUserInputFromConsole<int>();

    std::cout << "How many reviews do you want to import?\n"
                 "Your choice: ";

    //    get the number of reviews to import
    auto nReviews = getUserInputFromConsole<unsigned long>();

    std::cout << "\nImporting...\n";

    //    randomNumbers is a vector with N random numbers
    auto randomNumbers = returnVectorWithRandomNumbers(nReviews, binFile);

    //   randomVector is a vector with N random reviews
    auto randomVector = std::make_unique<std::vector<Review>>(nReviews);
    for (int i = 0; i < nReviews; ++i) {
        (*randomVector)[i] = this->binFile->getReview((*randomNumbers)[i]);
    }

//    open binFile
    std::ofstream file;
    if (mainChoice == static_cast<int>(OutputType::File)) {
        file.open("../output.txt");
    }
    std::ostream &output = (mainChoice == static_cast<int>(OutputType::File)) ? file : std::cout;

    writeTo(output, std::move(randomVector));
}

// make a function that work with std::cout and std::ofstream as input, wich write the reviews in the output
void writeTo(std::ostream &output, std::unique_ptr<std::vector<Review>> reviews) {
    for (const auto &review: *reviews) {
        output << review << "\n\n";
    }
}

Tester::Tester(int argc, char **argv) {
    if (argc != 3) {
        throw std::invalid_argument("Error program arguments");
    }
    this->csvFile = std::make_unique<CsvFile>(argv[1]);
    this->binFile = std::make_shared<BinFile>(argv[1], argv[2]);

}


