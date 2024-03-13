//
// Created by portes on 17/11/2023.
//

#ifndef HASH_H
#define HASH_H
#include <memory>
#include <string>
#include <vector>


class Hash {
private:
    std::unique_ptr<std::vector<std::pair<std::string, size_t>>> table;
    size_t size;
    size_t colisions = 0;
    size_t insertionsFailed = 0;
    size_t insertionsSucceeded = 0;
public:
    Hash(size_t size);

    void print() const;

    int hash(const std::string&key) const;

    size_t murmurHash(const std::string&key) const;

    void insert(const std::string &key);

    // return the element's index if found, otherwise return -1
    int search(const std::string &key) const;

    // return all elements in the table
    auto getTable() const -> const std::unique_ptr<std::vector<std::pair<std::string, size_t>>> &;


};


#endif //HASH_H
