//
// Created by Daniel on 05/05/2023.
//

#ifndef ED2_REWORK_TESTER_H
#define ED2_REWORK_TESTER_H


#include "File.h"
#include "BinFile.h"
#include "CsvFile.h"


template<typename T>
T getUserInputFromConsole(std::string message = "");

void writeTo(std::ostream &output, std::unique_ptr<std::vector<Review>> reviews);


/*
 * This class represents the actions from the teacher to test the students' code.
 * */
class Tester {
private:
    std::unique_ptr<CsvFile> csvFile;
    std::shared_ptr<BinFile> binFile;


public:
    Tester(int argc, char *argv[]);

    ~Tester() = default;

//    auto testAll(int part) -> void;


//    Part I
    auto accessReview() -> void;

    auto accessNRandomReviews() -> void;

//    Part II

//    Part III




};


#endif //ED2_REWORK_TESTER_H
