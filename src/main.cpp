#include <iostream>
#include "CsvFile.h"
#include "BinFile.h"
#include "Review.h"
#include "Tester.h"

/* run: ./exec <input_file> <output_file>
 csvFile file expected: tiktok_app_reviews.csv
 get in https://www.kaggle.com/datasets/shivamb/35-million-tiktok-mobile-app-reviews
 */
int main(int argc, char *argv[])
{

//    read the csv file and return a vector of reviews
    CsvFile csvFile(argc, argv);
    auto reviews = csvFile.read();

//    write the vector of reviews in a binary file
    BinFile binFile( argc, argv);
    binFile.write(std::move(reviews));
    reviews.reset();

//    read the binary file and return a vector of reviews
//    auto result = binFile.read();
//    result.reset();

    Tester tester(argc, argv);
    tester.accessReview();
    tester.accessNRandomReviews();


}