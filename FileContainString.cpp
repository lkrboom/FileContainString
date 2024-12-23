//
// Created by hyzh on 2024/12/23.
//
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

bool fileContainsString(const fs::path& filePath, const std::string& searchString) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find(searchString) != std::string::npos) {
            return true;
        }
    }
    return false;
}

// 判断路径是否为绝对路径
bool isAbsolutePath(const fs::path& path) {
    return path.is_absolute();  // 如果无法调用 is_absolute，可以根据系统特性自己判断
}

void findFilesContainingString(const fs::path& directory, const std::string& searchString) {
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        std::cerr << "Invalid directory: " << directory << std::endl;
        return;
    }

    // 使用 recursive_directory_iterator 遍历所有子文件夹和文件
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (fs::is_regular_file(entry.status())) {
            const fs::path& filePath = entry.path();
//            std::cout << "Checking file: " << filePath << std::endl;  // Debugging line to show file path
            if (fileContainsString(filePath, searchString)) {
                std::cout << "Found in: " << filePath << std::endl;
            }
        }
    }
}

int main() {
    std::string folderPath, searchString;

    std::cout << "Enter the folder path: ";
    std::getline(std::cin, folderPath);

    std::cout << "Enter the string to search for: ";
    std::getline(std::cin, searchString);

    fs::path folder(folderPath);

    // 使用手动判断是否为绝对路径
    if (!isAbsolutePath(folder)) {
        folder = fs::absolute(folder);  // 如果不是绝对路径，则转换为绝对路径
    }

    std::cout << "Searching in folder: " << folder << std::endl;  // Debugging line

    findFilesContainingString(folder, searchString);

    return 0;
}
