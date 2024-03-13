//
// Created by portes on 17/11/2023.
//

#include "Hash.h"

#include <iostream>

Hash::Hash(size_t size) : size(size) {
    table = std::make_unique<std::vector<std::pair<std::string, size_t>>>(size, std::make_pair("", 0));
}

void Hash::print() const {
    for (const auto & [key, repetitions] : *table) {
        std::cout << key << " " << repetitions << std::endl;
    }
}

int Hash::hash(const std::string &key) const {
    return static_cast<int>(murmurHash(key) % size);
}

size_t Hash::murmurHash(const std::string &key) const {
    const uint64_t seed = 0; // Valor de semente pode ser ajustado
    const uint64_t m = 0xc6a4a7935bd1e995ULL;
    const int r = 47;

    uint64_t h = seed ^ (key.size() * m);

    const uint64_t* data = reinterpret_cast<const uint64_t*>(key.c_str());
    const uint64_t* end = data + (key.size() / 8);

    while (data != end) {
        uint64_t k = *data++;
        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char* data2 = reinterpret_cast<const unsigned char*>(data);

    switch (key.size() & 7) {
        case 7: h ^= static_cast<uint64_t>(data2[6]) << 48;
        case 6: h ^= static_cast<uint64_t>(data2[5]) << 40;
        case 5: h ^= static_cast<uint64_t>(data2[4]) << 32;
        case 4: h ^= static_cast<uint64_t>(data2[3]) << 24;
        case 3: h ^= static_cast<uint64_t>(data2[2]) << 16;
        case 2: h ^= static_cast<uint64_t>(data2[1]) << 8;
        case 1: h ^= static_cast<uint64_t>(data2[0]);
        h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return static_cast<size_t>(h);
}


