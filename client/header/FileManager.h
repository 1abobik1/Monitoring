#pragma once
#include <string>

class FileManager {
public:
    static std::string readFileToBinary(const std::string& filePath);
};