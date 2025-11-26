#include "FileHandler.h"
#include <iostream>
#include <fstream>

using namespace std;

FileHandler::FileHandler() : filepath("") {}

FileHandler::FileHandler(const string& path) : filepath(path) {}

FileHandler::~FileHandler() {
    cout << "[ІНФО] Менеджер файлів для '" << filepath << "' знищено." << endl;
}

string FileHandler::getPath() const {
    return filepath;
}

void FileHandler::setPath(const string& newPath) {
    filepath = newPath;
}

bool FileHandler::fileExists() const {
    ifstream file(filepath);
    return file.good();
}

int FileHandler::countOfElements() const {
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "[ПОМИЛКА] Неможливо відкрити файл для підрахування рядків.\n";
        return -1;
    }

    int count = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) count++;
    }

    file.close();
    return count;
}

bool FileHandler::validateFileFormat(const string& expectedExtension) const {
    size_t dotPos = filepath.find_last_of('.');
    if (dotPos == string::npos) return false;
    string ext = filepath.substr(dotPos + 1);
    return ext == expectedExtension;
}
