//
// Created by Daniel on 05/05/2023.
//

#include <iostream>
#include <random>
#include <fstream>
#include <numeric>

#include "Sort.h"
#include "Tester.h"

#include <algorithm>

#include "CsvFile.h"
#include "BinFile.h"
#include "Review.h"

// helper function to get input from the user
template<typename T>
T getUserInputFromConsole(const std::string&message) {
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
auto Tester::accessReview() const -> void {
    //    access any review in the file
    const auto userInput = getUserInputFromConsole<long>("Enter the review number: ");
    const auto review = this->binFile->getReview(userInput);
    std::cout << review << std::endl;
}

enum class OutputType {
    Console = 1,
    File
};

auto returnVectorWithRandomNumbers(auto totalNReviews, const std::shared_ptr<BinFile>&binFile) {
    //  get N random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dis(0, static_cast<int>(binFile->getReviewsCount()) - 1);

    //    populate the vector with N random numbers
    auto randomNumbers = std::make_unique<std::vector<long>>(totalNReviews);
    for (int i = 0; i < totalNReviews; ++i) {
        (*randomNumbers)[i] = dis(gen);
    }
    return randomNumbers;
}

auto Tester::accessNRandomReviews() const -> void {
    std::cout << "Do you want to print the output in the console or in a txt file?\n"
            "1 - Console\n"
            "2 - File\n"
            "Your choice: ";

    const auto mainChoice = getUserInputFromConsole<int>();

    std::cout << "How many reviews do you want to import?\n"
            "Your choice: ";

    auto nReviews = getUserInputFromConsole<unsigned long>();

    std::cout << "\nImporting...\n";

    const auto randomNumbers = returnVectorWithRandomNumbers(nReviews, binFile);

    const auto randomVector = std::make_unique<std::vector<Review>>(nReviews);
    for (int i = 0; i < nReviews; ++i) {
        (*randomVector)[i] = this->binFile->getReview((*randomNumbers)[i]);
    }

    writeToOutput(mainChoice, randomVector);
}

void writeToOutput(int mainChoice, const std::unique_ptr<std::vector<Review>>&randomVector) {
    if (mainChoice == static_cast<int>(OutputType::File)) {
        std::ofstream file("../output.txt");
        writeTo(file, randomVector);
    }
    else {
        writeTo(std::cout, randomVector);
    }
}

void writeTo(std::ostream&output, const std::unique_ptr<std::vector<Review>>&randomVector) {
    // Write logic here, for example:
    for (const auto&review: *randomVector) {
        output << review << '\n';
    }
}

Tester::Tester(const int argc, char** argv) {
    if (argc != 3) {
        throw std::invalid_argument("Error program arguments");
    }
    this->csvFile = std::make_unique<CsvFile>(argv[1]);
    this->binFile = std::make_shared<BinFile>(argv[1], argv[2]);
}

auto Tester::sortReviews() const -> void {
    std::cout << "How many reviews do you want to import?\n"
            "Your choice: ";

    // Get the number of reviews to import
    auto nReviews = getUserInputFromConsole<unsigned long>();

    std::cout << "How many times do you want to run the sorting algorithm?\n"
            "Your choice: ";

    // Get the number of times to run the sorting algorithm
    const auto numSortingRuns = getUserInputFromConsole<unsigned long>();

    std::cout << "\nImporting...\n";

    // RandomNumbers is a vector with N random numbers
    const auto randomNumbers = returnVectorWithRandomNumbers(nReviews, binFile);

    // RandomVector is a vector with N random reviews using the randomNumbers values as index
    auto randomVector = std::make_shared<std::vector<Review>>(nReviews);
    for (int i = 0; i < nReviews; ++i) {
        (*randomVector)[i] = this->binFile->getReview((*randomNumbers)[i]);
    }

    std::vector totalComparisons(numSortingRuns, 0);
    std::vector totalMovements(numSortingRuns, 0);

    std::cout << "Which sorting algorithm do you want to use?\n"
            "1 - Quick Sort\n"
            "2 - Heap Sort\n"
            "3 - Comb Sort\n"
            "Your choice: ";
    auto const sortChoice = getUserInputFromConsole<int>();

    std::cout << "Do you want to print the output in the console or in a txt file?\n"
    "1 - Console\n"
    "2 - File\n"
    "Your choice: ";

    const auto outputChoice = getUserInputFromConsole<int>();

    for (int i = 0; i < numSortingRuns; ++i) {
        switch (sortChoice) {
            case 1: {
                Sort<Review>::quickSort(*randomVector);
                break;
            }
            case 2: {
                Sort<Review>::heapSort(randomVector);
                break;
            }
            case 3: {
                Sort<Review>::combSort(randomVector);
                break;
            }
            default: {
                std::cout << "Invalid input. Try again.\n";
                break;
            }
        }

        // Accumulate statistics
        totalComparisons[i] = Sort<Review>::getComparisons();
        totalMovements[i] = Sort<Review>::getMovements();
    }

    // Calculate averages
    const double averageComparisons = static_cast<double>(std::accumulate(
                                          totalComparisons.begin(), totalComparisons.end(), 0)) / numSortingRuns;
    const double averageMovements = static_cast<double>(
                                        std::accumulate(totalMovements.begin(), totalMovements.end(), 0)) /
                                    numSortingRuns;

    auto uniquePtr = std::make_unique<std::vector<Review>>(*randomVector);
    writeToOutput(outputChoice, std::move(uniquePtr));

    // Print averages
    std::cout << "Average Comparisons: " << averageComparisons << std::endl;
    std::cout << "Average Movements: " << averageMovements << std::endl;

}
