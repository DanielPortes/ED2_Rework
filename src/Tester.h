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

    ~Tester() = default;

//    auto testAll(int part) -> void;


//    Part I
    auto accessReview() const -> void;

    auto accessNRandomReviews() const -> void;

//    Part II

// use Sort to sort the reviews
    auto sortReviews() const -> void;



//    Part III




};


#endif //ED2_REWORK_TESTER_H
