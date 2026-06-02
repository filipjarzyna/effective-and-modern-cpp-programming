#include <iostream>
#include <filesystem>
#include <regex>

using namespace std;
namespace fs = std::filesystem;

struct FileInfo {
    string name;
    size_t size;
    char type;

    friend ostream& operator<<(std::ostream& os, const FileInfo& f) {
        os << '[' << f.type << ']' << " " << f.size << " " << f.name;
        return os;
    }
};

char getFileType(fs::path path) {
    if(fs::is_symlink(path))
        return 'L';
     
    if(fs::is_directory(path))
        return 'D';
     
    if(fs::is_regular_file(path))
        return 'F';

    return ' ';
}

FileInfo getFileInfo(fs::path path) {
    return FileInfo{fs::path(path).filename(), fs::file_size(path), getFileType(path)};
}
/**
 * Prints content of directory given by path
 * Format
 * [X] file_name file_size
 * where X equals D for directories, F for regular files, L for symlinks and space otherwise.
 * @param path directory path
 */

void printDirectory (std::string_view path) {
    fs::path rootPath = path;

    if(!fs::exists(path) || !fs::is_directory(path)) {
        return;
    }

    for(auto p: fs::directory_iterator(rootPath)) {
        cout << getFileInfo(p.path()) << endl;
    }
}

/**
 * Makes copies of all files matching fileNames regular expression in directory given by path
 * to files in the same directory but with changes extension to newExtension
 * @param path directory path
 * @param fileNames regular expression
 * @param newExtension new extension
 */
void changeExtension(fs::path path, std::string fileNames, std::string_view newExtension) {
    fs::path rootPath = path;

    if(!fs::exists(path) || !fs::is_directory(path)) {
        return;
    }

    for(auto p: fs::directory_iterator(rootPath)) {
        if(!regex_match(p.path().filename().string(), regex(fileNames))) {
            continue;
        }

        fs::path newPath = p.path();
        newPath.replace_filename(p.path().filename().replace_extension(newExtension));
        fs::copy(p.path(), newPath);
    }
}

int main() {
    string testPath = "/home/filip/Desktop/cpp/lab11/test";
    printDirectory(testPath);
    changeExtension(testPath, "first.txt", "newExt");
}
