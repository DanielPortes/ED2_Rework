//
// Created by Daniel on 28/08/2022.
//

#ifndef ED2_REWORK_REVIEW_H
#define ED2_REWORK_REVIEW_H


#include <string>

class CsvFile;

struct Review
{
private:
    std::string id;
    std::string text;
    int upvotes{0};
    std::string app_version;
    std::string posted_date;

    friend CsvFile;
public:
    friend std::ostream &operator<<(std::ostream &outFile, Review const &review);

    friend std::istream &operator>>(std::istream &inFile, Review &review);
};


#endif //ED2_REWORK_REVIEW_H
