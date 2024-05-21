#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class cst{
    public:
    //default con
    cst(int s = 10): size(s), arr(new char[size]) {}

    //big three
    cst(const cst& o) {
        size = o.size;
        arr = new char[size];
        for(int i = 0; i<size; i++){
            arr[i] = o.arr[i];
        }
        
    }

    cst& operator=(const cst& o){
        if(&o != this){
            delete[] arr;

            size = o.size;
            arr = new char[size];
            for(int i = 0; i<size; i++){
                arr[i] = o.arr[i];
            }
        }
        return *this;
    }

    ~cst(){
        delete[] arr;
    }

    //move
    cst(cst&& o) noexcept : size(o.size), arr(o.arr)  {
        o.arr = nullptr;
    }

    cst& operator=(cst&& o){
        size = o.size;
        delete[] arr;
        arr = o.arr;
        o.arr = nullptr;
        return *this;
    }

    private:
    char* arr;
    int size;
};




int main(){
    vector<cst> vect (3);

    vect.push_back(cst(5)); 

}