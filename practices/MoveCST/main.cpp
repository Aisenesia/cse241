#include <iostream>
#include <vector>
#include <string>
#include <cstring>


#define MOVEFLAG noexcept 
using namespace std;

class cst{
public:
//def con
cst(int len = 10);
cst(const char* input);
//copy con
cst(const cst& o);

//assignment
const cst& operator=(const cst& o);

//delete
~cst();

//move
cst(cst&& o) MOVEFLAG;
cst& operator=(cst&& o);

friend ostream& operator<<(ostream& out, const cst& o);


class iterator{
    public:
    iterator(const cst& obj, int i = 0): object(obj), index(i) {}

    char operator*(){
        return object.arr[index];
    }

    iterator& operator++(){
        ++index;
        return *this;
    }
    bool operator!=(const iterator& other){
        return other.index != index;
    }

    private:
    const cst& object;
    int index;

};

iterator begin() const {
    return iterator(*this, 0);
}

iterator end() const {
    return iterator(*this, length);
}

private:
    char* arr;
    int length;
};




cst::cst(int len): length(len) {
    arr = new char[length];
}

cst::cst(const char* input) {
    length = strlen(input) + 1;
    arr = new char[length];
    for(int i = 0; i<length; i++){
        arr[i] = input[i];
    }
}

cst::cst(const cst& o): length(o.length) {
    arr = new char[length];
    for(int i = 0; i<length; i++){
        arr[i] = o.arr[i];
    }
}
const cst& cst::operator=(const cst& o){
    length = o.length;
    delete[] arr;
    arr = new char[length];
    for(int i = 0; i<length; i++){
        arr[i] = o.arr[i];
    }
    return *this;
}

cst::~cst(){
    delete[] arr;
}

cst::cst(cst&& o) MOVEFLAG :  length(o.length){

    arr = o.arr;
    o.arr = nullptr;
}

cst& cst::operator=(cst&& o){
    length = o.length;
    arr = o.arr;
    o.arr = nullptr;
    return *this;
}


ostream& operator<<(ostream& out, const cst& o){
    if(o.arr != nullptr) out<<o.arr;
    return out;
}


int main(){
    vector<cst> b = {"bir", "iki", "uc"};
    for(auto a: b){
        cout<<a<<endl;
    }
    
    cst abb("test");
    b.push_back(abb);
    for(auto a: b){
        cout<<a<<endl;
    }
    return 0;
    //cout<<abb<<endl;
    cst brb(move(abb));
    cout<<brb<<endl;
    cout<<abb<<endl;
    

}