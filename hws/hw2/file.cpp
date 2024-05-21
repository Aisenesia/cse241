#include "file.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>


namespace GFile{

//File base class

File::File(const string &name) : filename(name) {
    time(&creation_time); 
}

File::File(const string &name, time_t t) : filename(name), creation_time(t) {}

void File::print() const {
    cout<<left<<setw(55)<<filename<<"\t"<<getTimeStr();
}

const string File::getTimeStr() const {
    struct tm *timeinfo = localtime(&creation_time);
    char time_char[50];
    strftime(time_char, 50, "%Y-%m-%d %H:%M:%S", timeinfo);
    string time_str(time_char);
    return time_str;
}

//dataFile

DataFile::DataFile(const string &name) : File(name) {}
DataFile::DataFile(const string &name, time_t t) : File(name, t) {}

void DataFile::print() const {
    File::print();
    cout<<"\t\t"<<data.size();
}

void DataFile::printContent() const {
    for(auto c:  data){
        cout<<c;
    } cout<<endl;
}   

DataFile::~DataFile(){
    data.clear();
}


//Folder

Folder::Folder(const string& name, time_t t, Folder* pre): File(name, t), previous(pre) {}
Folder::Folder(const string &name, Folder* pre): File(name), previous(pre) {}


const Type Folder::getType() const {
    return Type::FOLDER_FILE; 
}

void Folder::newFolder(const string& name){    
    File* created_folder = new Folder(name, this); // create
    files.push_back(created_folder); // bind
}

const string& Folder::tracePath(Folder* pre, string& input) {   
    if (pre == nullptr) {
        return input;
    }
    input = pre->getName() + "/" + input;
    pre = pre->previous;

    return tracePath(pre, input);
}

File* Folder::findInFolder(const string& name) const {
    for(auto a: getFiles()){
        if(a->getName() == name){
            return a;
        }
    }
    return nullptr;
}

void Folder::printContent() const {
    for(auto file:  files){
        file->print();
        cout<<endl;
    } 
}

void Folder::add(File* file){

    if(findInFolder(file->getName())!=nullptr) throw invalid_argument("Already exists!\n");
    
    files.push_back(file); 
}


void Folder::erase(File* file){
    for (auto it = files.begin(); it != files.end(); ++it) {
        if (*it == file) {
            files.erase(it);
            break; //iterator invalidation prevention
        }
    }

}

Folder::~Folder() {
    for (auto file : files) {
        if (file != nullptr) {
            delete file; // delete the file object
            file = nullptr;
        }
    }
    files.clear();
}


//Folder iterator
Folder::iterator& Folder::iterator::operator++() {
    ++current;
    return *this;
}

Folder::iterator Folder::begin() {
    return iterator(files.begin());
}

Folder::iterator Folder::end() {
    return iterator(files.end());
}

//Data iterator
DataFile::iterator& DataFile::iterator::operator++() {
    ++current;
    return *this;
}

DataFile::iterator DataFile::begin() {
    return iterator(data.begin());
}

DataFile::iterator DataFile::end() {
    return iterator(data.end());
}


//linkedFile

void Linked::printContent() const {
    pathToPointer(Folder::root, filepath)->printContent();
}

File* Linked::pathToPointer(File* root, const string& path) const {
    if (path.empty()) return nullptr;

    vector<string> folders;
    stringstream ss(path);
    string folder;

    while (getline(ss, folder, '/')) {
        folders.push_back(folder);
    }

    File* ptr = root;
    for (auto it = folders.begin(); (it != (folders.end() - 1)); ++it) { //iterates except the last element
        ptr = dynamic_cast<Folder*>(ptr)->findInFolder(*it);
        if(ptr == nullptr) return nullptr;
    }
    
    File* result = dynamic_cast<Folder*>(ptr)->findInFolder(*(folders.end() - 1));
    return result;
}

File* Linked::getLink() {
    File* ptp = pathToPointer(Folder::root, filepath);
    Linked* ln = dynamic_cast<Linked*>(ptp);
    if(ln != nullptr){
        return ln->getLink();
    }
    return ptp;
}

File* Linked::getLink() const {
    File* ptp = pathToPointer(Folder::root, filepath);
    Linked* ln = dynamic_cast<Linked*>(ptp);
    if(ln != nullptr){
        return ln->getLink();
    }
    return ptp;
}


void Linked::print() const{
    File::print();
    cout<<"\t\t"<<"linked";
    File* link = getLink();

    if(link==nullptr) cout<<"-hanging"; // not linked
    else if(link->getType() == Type::FOLDER_FILE) cout<<"-folder";
    else if(link->getType() == Type::DATA_FILE) cout<<"-data";

}

Folder* Folder::root;
}