#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
using namespace std;

class FileEntry {
private:
    string name;

public:
    FileEntry(string _name) {
        name = _name;
    }

    virtual bool isFolder() = 0;

    virtual map<string, FileEntry*> getFiles() = 0;
};

class File : public FileEntry {

public:
    File(string _name) : FileEntry(_name) {

    }

    bool isFolder() {
        return false;
    }

    map<string, FileEntry*> getFiles() {
        return map<string, FileEntry*>();
    }
};

class Folder: public FileEntry {

private:
    map<string, FileEntry*> files;

public:
    Folder(string _name, map<string, FileEntry*> _files) : FileEntry(_name) {
        files = _files;
    }

    bool isFolder() {
        return true;
    }

    map<string, FileEntry*> getFiles() {
        return files;
    }
};

map<string, string> flattenDictionary(FileEntry* root) {

}

int main() {
    freopen("flattenDictionary.in", "r", stdin);


    return 0;
}