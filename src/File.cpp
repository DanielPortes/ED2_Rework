//
// Created by Daniel on 29/08/2022.
//
#include <fstream>
#include "File.h"

unsigned long File::getFileSize()
{ return std::filesystem::file_size(this->inFile); }

auto File::bufferingFile() -> std::unique_ptr<std::vector<unsigned char>>
{
    auto fileSize = getFileSize();
    std::ifstream file(this->inFile);
    auto input = std::make_unique<std::vector<unsigned char>>();
    input->resize(fileSize);
    file.read(reinterpret_cast<char *>(input->data()), static_cast<long>(fileSize));
    if (!file.fail() && fileSize == file.gcount())
    {
        return input;
    }
    else
    {
        throw std::runtime_error("Error reading file");
    }
}