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
#include "BTree.h"
#include "HuffmanCompressor.h"
#include "RedBlackTree.h"
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

auto Tester::importRandomReviews(unsigned long nReviews) const -> std::shared_ptr<std::vector<Review>> {
    const auto randomNumbers = returnVectorWithRandomNumbers(nReviews, binFile);
    auto randomVector = std::make_shared<std::vector<Review>>(nReviews);
    for (int i = 0; i < nReviews; ++i) {
        (*randomVector)[i] = this->binFile->getReview((*randomNumbers)[i]);
    }
    return randomVector;
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
    auto randomVector = importRandomReviews(nReviews);


    // std::vector totalComparisons(numSortingRuns, 0);
    // std::vector totalMovements(numSortingRuns, 0);

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

    long totalComparisons = 0;
    long totalMovements = 0;

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
        totalComparisons += Sort<Review>::getComparisons();
        totalMovements += Sort<Review>::getMovements();
    }

    // Calculate averages
    const double averageComparisons = static_cast<double>(totalComparisons) / numSortingRuns;
    const double averageMovements = static_cast<double>(totalMovements) / numSortingRuns;


    auto uniquePtr = std::make_unique<std::vector<Review>>(*randomVector);
    writeToOutput(outputChoice, std::move(uniquePtr));

    // Print averages
    std::cout << "Average Comparisons: " << averageComparisons << std::endl;
    std::cout << "Average Movements: " << averageMovements << std::endl;
}

// Part II
auto Tester::countAppVersions() const -> void {
    // read N random Reviews
    // using your own hash table, count the amount of reviews for each app version
    // print the M most reviewed app versions, where M is a number given by the user
    // the output should be in the console or in a txt file, depending on the user's choice
    // and the output should be in descending order, from the most reviewed app version to the least reviewed


}

// Part III
auto Tester::compareDataStructures() const -> void {
    const int N = 1000000;
    const int B = 100;
    const int M = 3;

    std::ofstream outputFile("saida.txt");

    outputFile << "Comparação de Desempenho das Estruturas de Dados\n\n";

    for (int i = 1; i <= M; ++i) {
        outputFile << "Execução " << i << ":\n";
        compareRedBlackTree(N, B, outputFile);
        compareBTree(N, B, 20, outputFile);
        compareBTree(N, B, 200, outputFile);
        outputFile << "\n";
    }

    outputFile.close();
}

auto Tester::compareRedBlackTree(int N, int B, std::ofstream& outputFile) const -> void {
    auto randomInsertReviews = importRandomReviews(N);
    auto randomSearchReviews = importRandomReviews(B);

    RedBlackTree tree;

    auto startTime = std::chrono::high_resolution_clock::now();
    long long comparisons = 0;

    for (const auto& review : *randomInsertReviews) {
        tree.insert(review, 0);
        comparisons += tree.getComparisons();
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    outputFile << "Árvore Vermelho-Preto - Inserção:\n";
    outputFile << "Comparações: " << comparisons << "\n";
    outputFile << "Tempo: " << duration << " ms\n";

    startTime = std::chrono::high_resolution_clock::now();
    comparisons = 0;

    for (const auto& review : *randomSearchReviews) {
        tree.search(review.getId());
        comparisons += tree.getComparisons();
    }

    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    outputFile << "Árvore Vermelho-Preto - Busca:\n";
    outputFile << "Comparações: " << comparisons << "\n";
    outputFile << "Tempo: " << duration << " ms\n\n";
}

auto Tester::compareBTree(int N, int B, int order, std::ofstream& outputFile) const -> void {
    auto randomInsertReviews = importRandomReviews(N);
    auto randomSearchReviews = importRandomReviews(B);

    BTree tree(order);

    auto startTime = std::chrono::high_resolution_clock::now();
    long long comparisons = 0;

    for (const auto& review : *randomInsertReviews) {
        tree.insert(review, 0);
        comparisons += tree.getComparisons();
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    outputFile << "Árvore B (m = " << order << ") - Inserção:\n";
    outputFile << "Comparações: " << comparisons << "\n";
    outputFile << "Tempo: " << duration << " ms\n";

    startTime = std::chrono::high_resolution_clock::now();
    comparisons = 0;

    for (const auto& review : *randomSearchReviews) {
        tree.search(review.getId());
        comparisons += tree.getComparisons();
    }

    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    outputFile << "Árvore B (m = " << order << ") - Busca:\n";
    outputFile << "Comparações: " << comparisons << "\n";
    outputFile << "Tempo: " << duration << " ms\n\n";
}

auto Tester::compressRandomReviews() const -> void {
    std::cout << "Digite o número de review_texts aleatórios a serem comprimidos: ";
    int N = getUserInputFromConsole<int>("");

    auto randomReviews = importRandomReviews(N);
    std::string concatenatedText;
    for (const auto& review : *randomReviews) {
        concatenatedText += review.getText();
    }

    HuffmanCompressor compressor;
    compressor.compress(concatenatedText, "reviewsComp.bin");

    std::cout << "Compressão concluída. Arquivo reviewsComp.bin gerado.\n";
}

auto Tester::decompressReviews() const -> void {
    HuffmanCompressor compressor;
    compressor.decompress("reviewsComp.bin", "reviewsOrig.bin");

    std::cout << "Descompressão concluída. Arquivo reviewsOrig.bin gerado.\n";
}

auto Tester::runCompressionSequence() const -> void {
    const int M = 3;
    const std::vector<int> N = {10000, 100000, 1000000};

    std::ofstream outputFile("saida.txt");
    outputFile << "Resultados da sequência de compressões:\n\n";

    for (int i = 0; i < M; ++i) {
        outputFile << "Execução " << i + 1 << ":\n";
        for (int n : N) {
            auto randomReviews = importRandomReviews(n);
            std::string concatenatedText;
            for (const auto& review : *randomReviews) {
                concatenatedText += review.getText();
            }

            HuffmanCompressor compressor;
            auto startTime = std::chrono::high_resolution_clock::now();
            compressor.compress(concatenatedText, "temp.bin");
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

            long long originalSize = concatenatedText.size();
            std::ifstream compressedFile("temp.bin", std::ios::binary | std::ios::ate);
            long long compressedSize = compressedFile.tellg();
            compressedFile.close();

            double compressionRatio = static_cast<double>(originalSize) / compressedSize;

            outputFile << "N = " << n << ":\n";
            outputFile << "Tempo de compressão: " << duration << " ms\n";
            outputFile << "Taxa de compressão: " << compressionRatio << "\n\n";
        }
        outputFile << "\n";
    }

    outputFile.close();
    std::cout << "Sequência de compressões concluída. Resultados salvos em saida.txt.\n";
}

