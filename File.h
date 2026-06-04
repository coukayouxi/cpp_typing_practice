#pragma once
#include <vector>
#include <string>
#include <filesystem> // 需要 C++17 支持
#include <fstream>
#include <iostream> // for std::getline

namespace fs = std::filesystem;

/**
 * @brief 获取指定目录下的所有文件路径
 * @param directory_path 目录路径
 * @return 包含文件路径的向量
 */
std::vector<std::string> getFilesInDirectory(const std::string& directory_path) {
    std::vector<std::string> file_list;

    try {
        for (const auto& entry : fs::directory_iterator(directory_path)) {
            if (entry.is_regular_file()) { // 只添加普通文件
                file_list.push_back(entry.path().string());
            }
        }
    }
    catch (const fs::filesystem_error& ex) {
        std::cerr << "访问目录时发生错误: " << ex.what() << std::endl;
    }

    return file_list;
}

std::vector<std::string> readLinesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;

    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return lines; // 返回空的 vector
    }

    std::string line;
    while (std::getline(file, line)) {
        // line 变量现在包含当前行的内容（不包括换行符）
        lines.push_back(line);
    }

    file.close(); // 关闭文件句柄
    return lines;
}