#ifndef FILE_H
#define FILE_H

#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace GFile{
enum class Type
{
    FOLDER_FILE,
    DATA_FILE,
    LINKED_FILE
};

class File {
    
public:
    File(const string &name);
    File(const string &name, time_t t);

    virtual void print() const;
    virtual void printContent() const = 0;

    const string &getName() const { return filename; }
    void setName(const string &name) { filename = name; }

    void setTime(time_t timestamp) { creation_time = timestamp; }
    time_t getTime() const { return creation_time; } // returns time in time format
    const string getTimeStr() const;                 // returns time in formatted, text format

    virtual const Type getType() const = 0; // using when possible to avoid dynamic_casts, i think this is a bit more effective

    virtual ~File(){}; 

protected:
    string filename;
    time_t creation_time;
};

class DataFile : public File{

public:
    DataFile(const string &name);
    DataFile(const string &name, time_t t);


    virtual const Type getType() const override { return Type::DATA_FILE; }
    vector<char>& getData() { return data; }

    

    void print() const override;
    virtual void printContent() const override;


    class iterator {
    public:

        iterator(std::vector<char>::iterator it): current(it) {}
        iterator(const iterator& other) : current(other.current) {}

        char& operator*() { return *current; }
        iterator& operator++();
        bool operator!=(const iterator& other) const { return current != other.current; }
        std::vector<char>::iterator& getCurrent() { return current; }

    
    private:
        std::vector<char>::iterator current;
    };

    iterator begin();
    iterator end();

    virtual ~DataFile();

private:
    vector<char> data; // holds data byte-by-byte, thus char
};

class Folder : public File{
public:
    Folder(const string &name, time_t t, Folder *pre = nullptr);
    Folder(const string &name, Folder *pre = nullptr);

    virtual const Type getType() const override;
    

    File* findInFolder(const string& name) const; // searches this for the name, if not found returns nullptr
    static Folder* root;

    virtual void printContent() const override;

    vector<File *> &getFiles() { return files; } // returns files, files may be modified
    const vector<File *> &getFiles() const { return files; } // const version, immutable

    void newFolder(const string &name); // creates a new folder inside this folder, binds it

    Folder *getPrevious() const { return previous; } // returns the folder this is in
    const string &tracePath(Folder *pre, string &input);
    void setPrevious(Folder *v) { previous = v; } // binds this file to folder given as argument

    void add(File* file); // adds a file to list
    void erase(File* file); // deletes matching pointer from list

    class iterator {

    public:
        iterator(std::vector<File*>::iterator it): current(it) {}
        iterator(const iterator& other) : current(other.current) {}

        File*& operator*() { return *current; }
        iterator& operator++();
        bool operator!=(const iterator& other) const { return current != other.current; }
        std::vector<File*>::iterator& getCurrent(){ return current; }

    private:
        std::vector<File*>::iterator current;
    };

    iterator begin();
    iterator end();

    virtual ~Folder(); // calls delete for its content as well

private:
    vector<File *> files; // holds anything that derived from file, currently folders, datafiles and linkedfiles
    Folder *previous;
};

class Linked : public File
{
public:
    Linked(const string &name) : File(name) {}
    Linked(const string &name, time_t t) : File(name, t) {}

    const string &getPath() { return filepath; };
    void setPath(const string &path) { filepath = path; };

    void print() const override;
    virtual void printContent() const override;

    File* getLink(); // returns pointer of the file its linked to, until File is not of the Type::LINKED_FILE, so it reaches to the original file even if its linked a few times
    File* getLink() const;

    File* pathToPointer(File* root, const string& path) const; // returns a pointer from that path

    const Type getType() const override { return Type::LINKED_FILE; }

private:
    string filepath;
};

}
#endif