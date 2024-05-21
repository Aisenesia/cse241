#ifndef SHELL_H
#define SHELL_H


#include "file.h"

namespace GFile{
class Shell{

    public:
    Shell(): root_folder("root"){ current_folder = &root_folder; }

    void main_shell(); // main shell loop 

    private:

    void parseInput(vector<string>& input); // parses input
    string parsePath(const std::string& file_path); // returns last of a path

    void load_filesystem(); // loads "filesystem.txt", wrapper
    void load_recursive(ifstream& filesystem, Folder* folder); // invoked by load_filesystem(), recursive part

    void save_filesystem();//wrapper for save mechanism, invokes save_recursive()
    void save_recursive(ofstream& filesystem, Folder* folder, int depth = 0); // recursive part

    void ls(vector<string>& params) const; // ls for current_folder only
    void lsRecursive(const Folder& folder, int depth = 0) const; // ls, recursively invoked for every other folder inside current_folder.files

    void cd(const string& newDir); // changes directory to given folder 

    void cp(vector<string>& params); // copies a file, for os to fs "cp path name or '.' " for os to os "cp name name2"
    void cpRecursive(File* src, const string& dest_name, Folder* dest_folder);

    void mkdir(vector<string>& params); // creates a folder
    void rmdir(vector<string>& params); // removes a folder if its empty

    void rm(vector<string>& params); // removes a file, for folders "-R" parameter must be given 

    void cat(const string& fileName) const; // only for printing to the screen, it does not do "concatenation" 

    void link(vector<string>& params); 

    File* find(const string& name) const; // finds and returns file* of that "name"
    
    Folder* getRoot() { return &root_folder; } 

    //data:
    Folder root_folder; // entire filesystem's root node
    Folder* current_folder;  // pointer to the current folder

};

}
//File* pathToPointer(const string&);


#endif