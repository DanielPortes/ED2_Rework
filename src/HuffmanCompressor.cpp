//
// Created by portes on 13/03/2024.
//

#include "HuffmanCompressor.h"

#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>

HuffmanNode* HuffmanCompressor::buildHuffmanTree(const std::unordered_map<char, int>&frequencyTable) {
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, Compare> pq;

    for (const auto&pair: frequencyTable) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        int sumFreq = left->frequency + right->frequency;
        pq.push(new HuffmanNode('\0', sumFreq, left, right));
    }

    return pq.top();
}

void HuffmanCompressor::generateHuffmanCodes(HuffmanNode* root, std::string code, std::unordered_map<char, std::string>&huffmanCodes) {
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        huffmanCodes[root->character] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

void HuffmanCompressor::writeCompressedData(const std::string&input, const std::unordered_map<char, std::string>&huffmanCodes,
                         const std::string&outputFile) {
    std::ofstream outFile(outputFile, std::ios::binary);
    std::string encodedString;

    for (char c: input) {
        encodedString += huffmanCodes.at(c);
    }

    int paddingSize = 8 - encodedString.size() % 8;
    for (int i = 0; i < paddingSize; ++i) {
        encodedString += "0";
    }

    outFile.write(reinterpret_cast<const char *>(&paddingSize), sizeof(paddingSize));

    int numBytes = encodedString.size() / 8;
    for (int i = 0; i < numBytes; ++i) {
        std::string byteString = encodedString.substr(i * 8, 8);
        char byte = std::stoi(byteString, nullptr, 2);
        outFile.write(&byte, sizeof(byte));
    }

    outFile.close();
}

void HuffmanCompressor::writeHuffmanTree(HuffmanNode* root, std::ofstream&outFile) {
    if (root == nullptr)
        return;

    outFile.write(reinterpret_cast<const char *>(&root->character), sizeof(root->character));
    outFile.write(reinterpret_cast<const char *>(&root->frequency), sizeof(root->frequency));

    writeHuffmanTree(root->left, outFile);
    writeHuffmanTree(root->right, outFile);
}

HuffmanNode* HuffmanCompressor::readHuffmanTree(std::ifstream&inFile) {
    char character;
    int frequency;

    inFile.read(reinterpret_cast<char *>(&character), sizeof(character));
    inFile.read(reinterpret_cast<char *>(&frequency), sizeof(frequency));

    if (inFile.eof())
        return nullptr;

    HuffmanNode* node = new HuffmanNode(character, frequency);
    node->left = readHuffmanTree(inFile);
    node->right = readHuffmanTree(inFile);

    return node;
}

void HuffmanCompressor::compress(const std::string&input, const std::string&outputFile) {
    std::unordered_map<char, int> frequencyTable;
    for (char c: input) {
        frequencyTable[c]++;
    }

    HuffmanNode* root = buildHuffmanTree(frequencyTable);

    std::unordered_map<char, std::string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    std::ofstream outFile(outputFile, std::ios::binary);
    writeHuffmanTree(root, outFile);
    outFile.close();

    writeCompressedData(input, huffmanCodes, outputFile);

    delete root;
}

void HuffmanCompressor::decompress(const std::string&inputFile, const std::string&outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);

    HuffmanNode* root = readHuffmanTree(inFile);

    int paddingSize;
    inFile.read(reinterpret_cast<char *>(&paddingSize), sizeof(paddingSize));

    std::string encodedString;
    char byte;
    while (inFile.read(&byte, sizeof(byte))) {
        std::string byteString = std::bitset<8>(byte).to_string();
        encodedString += byteString;
    }

    encodedString = encodedString.substr(0, encodedString.size() - paddingSize);

    std::ofstream outFile(outputFile);
    HuffmanNode* current = root;
    for (char c: encodedString) {
        if (c == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (!current->left && !current->right) {
            outFile << current->character;
            current = root;
        }
    }

    outFile.close();
    inFile.close();

    delete root;
}
