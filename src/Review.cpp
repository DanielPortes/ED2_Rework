//
// Created by Daniel on 28/08/2022.
//

#include "Review.h"
#include <fstream>

std::ostream &operator<<(std::ostream &outFile, Review const &review)
{
    // write id
    auto sizeId = static_cast<int>(review.id.size());
    outFile.write(reinterpret_cast<char *>(&sizeId), sizeof(sizeId));
    outFile.write(review.id.data(), sizeId);

    // write text
    int sizeText = static_cast<int>(review.text.size());
    outFile.write(reinterpret_cast<char *>(&sizeText), sizeof(sizeText));
    outFile.write(review.text.data(), sizeText);

    // write upvotes
    outFile.write(reinterpret_cast<const char *>(&review.upvotes), sizeof(review.upvotes));

    // write app_version
    int sizeAppVersion = static_cast<int>(review.app_version.size());
    outFile.write(reinterpret_cast<char *>(&sizeAppVersion), sizeof(sizeAppVersion));
    outFile.write(review.app_version.data(), sizeAppVersion);

    // write posted_date
    int sizePostedDate = static_cast<int>(review.posted_date.size());
    outFile.write(reinterpret_cast<char *>(&sizePostedDate), sizeof(sizePostedDate));
    outFile.write(review.posted_date.data(), sizePostedDate);

    return outFile;
}

std::istream &operator>>(std::istream &inFile, Review &review)
{
    // read id
    int sizeId{0};
    inFile.read(reinterpret_cast<char *>(&sizeId), sizeof(sizeId));
    if (sizeId > 0)
    {
        review.id.resize(sizeId);
        inFile.read(reinterpret_cast<char *>(&review.id.front()), sizeId);
    }

    // read text
    int sizeText{0};
    inFile.read(reinterpret_cast<char *>(&sizeText), sizeof(sizeText));
    if (sizeText > 0)
    {
        review.text.resize(sizeText);
        inFile.read(reinterpret_cast<char *>(&review.text.front()), sizeText);
    }

    // read upvotes
    inFile.read(reinterpret_cast<char *>(&review.upvotes), sizeof(review.upvotes));

    // read app_version
    int sizeAppVersion{0};
    inFile.read(reinterpret_cast<char *>(&sizeAppVersion), sizeof(sizeAppVersion));
    if (sizeAppVersion > 0)
    {
        review.app_version.resize(sizeAppVersion);
        inFile.read(reinterpret_cast<char *>(&review.app_version.front()), sizeAppVersion);
    }

    // read posted_date
    int sizePostedDate{0};
    inFile.read(reinterpret_cast<char *>(&sizePostedDate), sizeof(sizePostedDate));
    if (sizePostedDate > 0)
    {
        review.posted_date.resize(sizePostedDate);
        inFile.read(reinterpret_cast<char *>(&review.posted_date.front()), sizePostedDate);
    }
    return inFile;
}

bool Review::operator<(const Review &rhs) const
{
    return upvotes < rhs.upvotes;
}

bool Review::operator>(const Review &rhs) const
{
    return upvotes > rhs.upvotes;
}

std::string Review::getId() const {
    return id;

}

std::string Review::getText() const {
    return text;
}

