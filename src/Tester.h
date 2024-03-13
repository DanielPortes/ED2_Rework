//
// Created by Daniel on 05/05/2023.
//

#ifndef ED2_REWORK_TESTER_H
#define ED2_REWORK_TESTER_H


#include "File.h"
#include "BinFile.h"
#include "CsvFile.h"


template<typename T>
T getUserInputFromConsole(const std::string &message = "");

void writeTo(std::ostream &output, const std::unique_ptr<std::vector<Review>>&reviews);
void writeToOutput(int mainChoice, const std::unique_ptr<std::vector<Review>>&randomVector);

template<typename T>
void quickSort(std::unique_ptr<std::vector<T>>& v);

/*
 * This class represents the actions from the teacher to test the students' code.
 * */
class Tester {
private:
    std::unique_ptr<CsvFile> csvFile;
    std::shared_ptr<BinFile> binFile;


public:
    Tester(int argc, char *argv[]);

    auto importRandomReviews(unsigned long nReviews) const -> std::shared_ptr<std::vector<Review>>;

    ~Tester() = default;

//    auto testAll(int part) -> void;


//    Part I
    auto accessReview() const -> void;

    auto accessNRandomReviews() const -> void;

//    Part II

// use Sort to sort the reviews
    auto sortReviews() const -> void;

    auto countAppVersions() const -> void;

    auto compareDataStructures() const -> void;

    auto compareRedBlackTree(int N, int B, std::ofstream&outputFile) const -> void;

    auto compareBTree(int N, int B, int order, std::ofstream&outputFile) const -> void;


    //    Part III




};


#endif //ED2_REWORK_TESTER_H
