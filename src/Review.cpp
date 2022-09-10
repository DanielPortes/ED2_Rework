//
// Created by Daniel on 28/08/2022.
//

#include "Review.h"
#include <fstream>

std::ostream &operator<<(std::ostream &outFile, const Review &review)
{
    // write id
    auto sizeId = review.id.size();
    outFile.write(reinterpret_cast<const char *>(&sizeId), sizeof(sizeId));
    outFile.write(review.id.c_str(), sizeId);
    // write text
    auto sizeText = review.text.size();
    outFile.write(reinterpret_cast<const char *>(&sizeText), sizeof(sizeText));
    outFile.write(review.text.c_str(), sizeText);
    // write upvotes
    outFile.write(reinterpret_cast<const char *>(&review.upvotes), sizeof(review.upvotes));
    // write app_version
    auto sizeAppVersion = review.app_version.size();
    outFile.write(reinterpret_cast<const char *>(&sizeAppVersion), sizeof(sizeAppVersion));
    outFile.write(review.app_version.c_str(), sizeAppVersion);
    // write posted_date
    auto sizePostedDate = review.posted_date.size();
    outFile.write(reinterpret_cast<const char *>(&sizePostedDate), sizeof(sizePostedDate));
    outFile.write(reinterpret_cast<const char *>(review.id.c_str()), sizePostedDate);

    return outFile;
}

std::istream &operator>>(std::istream &inFile, Review &review)
{
    // read id
    int sizeId{0};
    inFile.read(reinterpret_cast<char *>(&sizeId), sizeof(sizeId));
    review.id.resize(sizeId);
    inFile.read(reinterpret_cast<char *>(&review.id.front()), sizeId);

    // read text
    int sizeText{0};
    inFile.read(reinterpret_cast<char *>(&sizeText), sizeof(sizeText));
    review.text.resize(sizeText);
    inFile.read(reinterpret_cast<char *>(&review.text.front()), sizeText);

    // read upvotes
    inFile.read(reinterpret_cast<char *>(&review.upvotes), sizeof(review.upvotes));

    // read app_version
    int sizeAppVersion{0};
    inFile.read(reinterpret_cast<char *>(&sizeAppVersion), sizeof(sizeAppVersion));
    review.app_version.resize(sizeAppVersion);
    inFile.read(reinterpret_cast<char *>(&review.app_version.front()), sizeAppVersion);

    // read posted_date
    int sizePostedDate{0};
    inFile.read(reinterpret_cast<char *>(&sizePostedDate), sizeof(sizePostedDate));
    review.posted_date.resize(sizePostedDate);
    inFile.read(reinterpret_cast<char *>(&review.posted_date.front()), sizePostedDate);

    return inFile;
}
