//
// Created by portes on 13/03/2024.
//

#ifndef HUFFMANCOMPRESSOR_H
#define HUFFMANCOMPRESSOR_H
#include <string>
#include <unordered_map>


struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f, HuffmanNode* l = nullptr, HuffmanNode* r = nullptr)
        : character(c), frequency(f), left(l), right(r) {
    }

    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->frequency > r->frequency;
    }
};

class HuffmanCompressor {
private:
    void writeCompressedData(const std::string&input, const std::unordered_map<char, std::string>&huffmanCodes,
                             const std::string&outputFile);

    void writeHuffmanTree(HuffmanNode* root, std::ofstream&outFile);

    HuffmanNode* readHuffmanTree(std::ifstream&inFile);


    HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>&frequencyTable);

    void generateHuffmanCodes(HuffmanNode* root, std::string code, std::unordered_map<char, std::string>&huffmanCodes);

public:
    void compress(const std::string&input, const std::string&outputFile);

    void decompress(const std::string&inputFile, const std::string&outputFile);
};


#endif //HUFFMANCOMPRESSOR_H
