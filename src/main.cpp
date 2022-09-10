#include <iostream>
#include "CsvFile.h"
#include "BinFile.h"
#include "Review.h"

int main(int argc, char *argv[])
{
    // run: ./exec <input_file> <output_file>
    CsvFile csvFile(argc, argv);
    auto reviews = csvFile.read();

    BinFile binFile(argc, argv);
    binFile.write(std::move(reviews));
    reviews.reset();

    auto result = binFile.read();
    result.reset();

    auto review = binFile.getReview(3'000'000);
    std::cout << review;
}