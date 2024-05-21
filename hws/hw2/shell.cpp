#include "shell.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>

using namespace std;

namespace GFile{

void Shell::parseInput(vector<string>& input){
    string temp;
    do{
        cin>>temp;
        input.push_back(std::move(temp));
    }while(getchar()!='\n'); // cin does not offer the functionality getchar provides
}


string Shell::parsePath(const std::string& file_path) {
    
    stringstream sstream(file_path);
    vector<std::string> folders;
    string part;

    while (getline(sstream, part, '/')) { //seperate every piece till "/"
        folders.push_back(part);
    }
    string file_name = folders.back(); // last one is our file_name
    return file_name;
}

void Shell::ls(vector<string>& params) const {
    
    if(params.size()==1){ 
        assert(current_folder != nullptr);
        //if(current_folder == nullptr){ throw "terminate: nullptr"; }
        if(current_folder != &root_folder) cout << left << setw(55) <<".."<<"\t"<<current_folder->getTimeStr()<<endl;  
        current_folder->printContent();
    }
    else if(params.size() == 2 && params.at(1) == "-R"){
        lsRecursive(*current_folder);
    }

    else throw invalid_argument("usage: ls\nusage: ls -R\n");
}


void Shell::lsRecursive(const Folder& folder, int depth) const {
    //did not want to write const_iterator, using vectors' iterator directly
    for (auto file : folder.getFiles()) {
        for (int i = 0; i < depth; i++) {
            cout << "  ";
        }

        file->print();
        
        const Folder* subfolder = dynamic_cast<const Folder*>(file);
        if (subfolder != nullptr && !subfolder->getFiles().empty()) { // if subfolder is found and is not empty:
            cout<<endl;
            lsRecursive(*subfolder, depth + 1); // print subfolder recursively
        }
        else cout<<endl;
    }
}


void Shell::cd(const string& newDir) {
    File* found = find(newDir);
    if(found == nullptr) throw invalid_argument ("Directory not found!\n");
    
    if(newDir == ".." && current_folder->getPrevious() != nullptr){
        current_folder = current_folder->getPrevious();
    }
    else if (found->getType() == Type::FOLDER_FILE) {
        current_folder = dynamic_cast<Folder*>(found);
    } else if(found->getType() == Type::LINKED_FILE){
        current_folder = dynamic_cast<Folder*> (dynamic_cast<Linked*>(found)->getLink());
    }
    
    else if(newDir == "."); //if in the root, do nothing as unix does
}

void Shell::cp(vector<string>& params) {
    if(!params.size() == 3) throw invalid_argument("usage: cp src_file dest_file\n");
    if(params.at(2) == params.at(1)) throw invalid_argument("src and dest file names can not be same in the same folder.\n");
    
    ifstream os_file;
    
    if(params.at(1).find("/") != string::npos){ // if it contains "/"
        os_file.open(params.at(1));
        if(!os_file) throw invalid_argument("No such file, failed to open.\n");

        DataFile* dest_file;

        if(params.at(2) == ".") dest_file = new DataFile(parsePath(params.at(1))); // cp path .
        else dest_file = new DataFile(params.at(2)); // cp path file_name

        char c;
        while(os_file.get(c)){
            dest_file->getData().push_back(c);
        }
        current_folder->add(dest_file);
    } else {
        
        File* found = find(params.at(1));
        if (found == nullptr) throw invalid_argument("No such file or folder.\n");

        cpRecursive(found, params.at(2), current_folder);
    }
}

void Shell::cpRecursive(File* src, const string& dest_name, Folder* dest_folder) {
    if (src->getType() == Type::DATA_FILE) {

        DataFile* new_file = new DataFile(dest_name); // create a datafile
        new_file->getData() = dynamic_cast<DataFile*>(src)->getData(); // use vectors assignment operator
        dest_folder->add(new_file); // add to filelist

    } else if (src->getType() == Type::LINKED_FILE) {

        Linked* new_file = new Linked(dest_name); 
        new_file->setPath(dynamic_cast<Linked*>(src)->getPath()); // linked files has the same path
        dest_folder->add(new_file);

    } else if (src->getType() == Type::FOLDER_FILE) {
        
        Folder* src_folder = dynamic_cast<Folder*>(src); //identify as a folder 
        Folder* new_folder = new Folder(dest_name, dest_folder); // create with new name
        dest_folder->add(new_folder);

        for (auto file : *src_folder) {
            cpRecursive(file, file->getName(), new_folder); // call cp for other Files inside the Folder
        }
    }
}


void Shell::mkdir(vector<string>& params) {
    if(params.size() != 2) throw invalid_argument("usage: mkdir dirname\n");

    if(find(params.at(1))!=nullptr) throw invalid_argument("Already exists within the folder!\n");
    current_folder->newFolder(params.at(1));
}

void Shell::rmdir(vector<string>& params) {
    if(params.size() != 2) throw invalid_argument("usage: mkdir dirname\n");
    Folder* found = dynamic_cast<Folder*>(find(params.at(1)));
    if(found == nullptr) throw invalid_argument("No such folder!\n");
    if(found->getFiles().empty() == false) throw invalid_argument("Folder is not empty, use rm -R\n");

    current_folder->erase(found);
    delete found;
}


void Shell::rm(vector<string>& params) {
    if(!(params.size() != 2 || params.size() != 3)) throw invalid_argument("usage: rm filename\nusage: rm -R dirname\n");
    File* found;

    bool isRec = false;

    if(params.at(1) == "-R") {
        found = find(params.at(2));
        isRec = true;
    } else found = find(params.at(1));

    if(found == nullptr) throw invalid_argument("No such file!\n");
    if(dynamic_cast<Folder*> (found) != nullptr && isRec == false) throw invalid_argument("Is a directory: use rm -R\n");


    current_folder->erase(found);

    delete found;
}

void Shell::cat(const string& name) const {
    File* found_file = find(name);

    if(found_file == nullptr) throw invalid_argument("No such file!\n");

    if(found_file->getType() == Type::LINKED_FILE){
        found_file = dynamic_cast<Linked*>(found_file)->getLink();
    }

   
    if(found_file->getType() == Type::FOLDER_FILE) throw invalid_argument("Is a folder.\n");
    else found_file->printContent();
}

File* Shell::find(const string& name) const {
    for(auto file: *current_folder){
        if(file->getName() == name){
            return file;
        }
    } return nullptr;
}



void Shell::save_filesystem(){
    ofstream filesystem;
    filesystem.open("filesystem.txt", std::ios::out);
    filesystem << root_folder.getTime()<< " " <<root_folder.getFiles().size() << endl;
    if (!filesystem.is_open()) {
        cout << "Error opening filesystem.txt for writing." << endl;
        return;
    }
    save_recursive(filesystem, &root_folder);
}

void Shell::save_recursive(ofstream& filesystem, Folder* folder, int depth) {

    if (folder->getFiles().empty()) {
        return;
    }

    for (auto v : *folder) {
        switch (v->getType()) {
            case Type::FOLDER_FILE: {
                Folder* ffile = dynamic_cast<Folder*>(v);
                filesystem << "F " << v->getName()<< " " <<v->getTime() << " " <<ffile->getFiles().size() << endl;
                save_recursive(filesystem, ffile, depth + 1);
                break;
            }
            case Type::DATA_FILE: {
                DataFile* dfile = dynamic_cast<DataFile*>(v);
                filesystem << "D " << v->getName() << " " << v->getTime() << " " << dfile->getData().size() << endl;
                for (auto d : *dfile) {
                    filesystem << d;
                }
                filesystem << endl;
                break;
            }
            case Type::LINKED_FILE:{
                Linked* lfile = dynamic_cast<Linked*>(v);
                filesystem << "L " << v->getName() << " " << v->getTime() << " " << lfile->getPath() << endl;
                
                break;
            }
        }
    } return;
}

void Shell::load_filesystem() {
    ifstream filesystem;
    filesystem.open("filesystem.txt");

    if (!filesystem.is_open()) {
        cout << "filesystem.txt not found, creating clean file." << endl; 
        return;  
    }
    try{
    //take the root info here
    time_t r_time;
    int count;
    filesystem>> r_time >> count;

    root_folder.setTime(r_time);
    for (int i = 0; i < count; i++) {
        load_recursive(filesystem, &root_folder);
    }

    filesystem.close();
    }
    catch(const runtime_error& e){
        cout<<e.what();
        return;
    }
}

void Shell::load_recursive(ifstream& filesystem, Folder* folder) {
    
    char type;
    string filename;
    time_t timestamp;
    filesystem >> type >> filename >> timestamp; // same input for all
    switch (type) {
        case 'D': {
            int file_size; 
            filesystem >> file_size; // data_file takes filesize
            filesystem.get();//newline consumer

            DataFile* new_datafile = new DataFile(filename, timestamp);

            char c;
            for (int i = 0; i < file_size; i++) { // take file_size characters into data for new_datafile
                filesystem.get(c);
                new_datafile->getData().push_back(c);
            }

            folder->add(new_datafile); // add to folders list
            
        }break;
        case 'F': {
            int count; 
            filesystem >> count; // how many Files in the folder
           
            Folder* new_folder = new Folder(filename, timestamp, folder);

            folder->add(new_folder);

            for (int i = 0; i < count; i++) {
                load_recursive(filesystem, new_folder);
            }
            
        }break;

        case 'L': {
            string path;

            filesystem >> path;
           
            Linked* new_linked = new Linked(filename, timestamp);
            folder->add(new_linked);
            new_linked->setPath(path);
  
        }break;
        default: throw runtime_error("improper filesystem!\n");
    }
}

void Shell::link(vector<string>& params){
    if(params.size() != 3) throw invalid_argument("usage: link path_to_src link_file\n");
    if(find(params.at(2))!=nullptr) throw invalid_argument("link_file exists!\n");

    Linked* linked = new Linked(params.at(2));
    File* found = linked->pathToPointer(&root_folder, params.at(1));
    if(found == nullptr) throw invalid_argument("File not found!\n");

    linked->setPath(params.at(1));
    current_folder->add(linked);
}

void Shell::main_shell(){
    bool exit_flag = false;
    vector<string> input_line;

    load_filesystem();
    Folder::root = &root_folder;

    while(!exit_flag){
        vector<string> input_line;
        cout<<"> ";

        parseInput(input_line);
        string& command(input_line.at(0));
        
        try{
            if(command == "exit"){
                save_filesystem();
                return;
            } 
            
            else if(command == "cd"){
                cd(input_line.at(1));
            }
            
            else if(command == "ls"){
                ls(input_line);
            }

            else if(command == "cp"){
                cp(input_line);
            }

            else if(command == "cat"){
                cat(input_line.at(1));
            }

            else if(command == "rm"){
                rm(input_line);
            }

            else if (command == "mkdir") {
               
                mkdir(input_line);
            }

            else if (command == "rmdir"){
                rmdir(input_line);
            }

            else if (command == "pwd"){
                string input;
                current_folder->tracePath(current_folder, input);
                cout<<input<<endl;

            }
            else if(command == "link"){
                link(input_line);
            }

            else if(command == "help"){

                cout<<"\n------------------------HELP------------------------"<<endl;
                cout<<"cd [directory_to_change_to - \".\" - \"..\"]\n";
                cout<<"mkdir folder_name_to_create\n";
                cout<<"ls [-R]\n";
                cout<<"cp [-R] source_[path - file] [destination - \".\"]\n";
                cout<<"rm [-R] file_to_delete\n";
                cout<<"rmdir empty_folder_to_delete\n";
                cout<<"pwd \n";
                cout<<"cat file_name_to_show_content\n";
                cout<<"link path_to_src_file link_name\n";
                cout<<"exit \n\n";
            }
            else{
                cout<<"Command not found, type \"help\" for a list of commands."<<endl;
            }
        }
        catch(invalid_argument& e){
            cout<<e.what();
        }
    }
}
}