//
// Created by Daniel on 29/08/2022.
//
#include <fstream>
#include <iostream>
#include "File.h"

File::File(const std::string &path)
{
    this->path;
}


unsigned long File::getFileSize()
{ return std::filesystem::file_size(this->path); }

auto File::bufferingFile() -> std::unique_ptr<std::vector<unsigned char>>
{
    std::ifstream file(this->path, std::ios::binary);

    if (!file)
    {
        throw std::runtime_error("Failed to open file");
    }

    auto fileSize = getFileSize();
    auto buffer = std::make_unique<std::vector<unsigned char>>(fileSize);

    if (!file.read(reinterpret_cast<char *>(buffer->data()), fileSize))
    {
        throw std::runtime_error("Failed to read file");
    }

    return buffer;
}

auto File::checkExistence(const std::filesystem::path &myFile) -> bool
{
    if (std::filesystem::exists(myFile) && std::filesystem::file_size(myFile) > 0)
    {
        std::cout << "Binary file already exists.\n";
        return true;
    }
    return false;
}

template<class T>
File &operator<<(File &file, const std::vector<T> &var)
{
    std::ofstream out(file.getCaminho(), std::ios::app);
    if (!out)
    {
        std::cerr << "Error opening file\n" << file.getCaminho() << "\n";
        return file;
    }
    out << var;
    out.close();
    return file;

}
