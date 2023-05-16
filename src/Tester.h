//
// Created by Daniel on 05/05/2023.
//

#ifndef ED2_REWORK_TESTER_H
#define ED2_REWORK_TESTER_H


#include "File.h"
#include "BinFile.h"
#include "CsvFile.h"

/*
 * This class represents the actions from the teacher to test the students' code.
 * */
class Tester
{
private:
    std::unique_ptr<CsvFile> csvFile;
    std::unique_ptr<BinFile> binFile;

    template<typename T>
    T getInput(std::string message);

public:
    Tester(int argc, char *argv[]);
    ~Tester() = default;

//    auto testAll(int part) -> void;


//    Part I
    auto accessReview() -> void;

    auto accessNRandomReviews() -> void;

//    Part II

//    Part III

    template<class T>
    void exportToFileOrConsole(std::unique_ptr<std::vector<T>> &reviews, const File &file);

};


#endif //ED2_REWORK_TESTER_H
