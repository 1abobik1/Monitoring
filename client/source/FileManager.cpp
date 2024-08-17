#include "../header/FileManager.h"

#include <iostream>
#include <sstream>
#include "fstream"

std::string FileManager::readFileToBinary(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
