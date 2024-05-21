#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;


class iarr{
    private:
    shared_ptr<int[]> arr;
    int size;
    int used;

    public:
    iarr(int s = 10): used(0), size(s), arr(new int[s]){
        
    }
    iarr(const iarr& o): used(o.used), size(o.size), arr(new int[size]){
        for(int i = 0; i<used; i++){
            arr[i] = o.arr[i];
        }
    }
    const iarr& operator=(const iarr& o){
        size = o.size;
        used = o.used;
        shared_ptr<int[]> temp(new int[size]);
        arr = temp;
        for(int i = 0; i<used; i++){
            arr[i] = o.arr[i];
        }
        return *this;
    }
    
    virtual ~iarr(){}

    iarr(iarr&& o)noexcept: used(o.used), size(o.size), arr(o.arr){
        o.arr = nullptr;
    }

    iarr& operator=(iarr&& o){
        used = o.used;
        size = o.size;

        shared_ptr<int[]> temp = o.arr;
        arr = temp;
        return *this;
    }

    void ensureCapacity(){
        if(used >= size){
            size = 2 * size;
            shared_ptr<int[]> temp(new int[size]);
            for(int i = 0; i<used; i++){
                temp[i] = arr[i];
            } arr = temp;
        }
    }

    void add(int element){
        ensureCapacity();
        arr[used++] = element;
    }

    void remove(int index){
        --used;
        for(int i = index; i<used; i++){
            arr[i] = arr[i+1];
        }
    }




    class iterator {
    private:
        int* ptr;

    public:
        iterator(int* p) : ptr(p) {}

        int& operator*() const {
            return *ptr;
        }

        iterator& operator++() {
            ++ptr;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++ptr;
            return temp;
        }

        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }
    };

    iterator begin() const {
        return iterator(arr.get());
    }

    iterator end() const {
        return iterator(arr.get() + used);
    }

    friend ostream& operator<<(ostream& out, const iarr& o){
        if(o.arr != nullptr){
            out<<"Elements:";
            for(auto a: o){
                out<<" "<<a;
            }
        }
        return out;
    }

    int& operator[](int index){
        return arr[index];
    }

    const int& operator[](int index) const {
        return arr[index];
    }
    
    iarr operator+(const iarr& o){
        iarr temp(*this);
        for(int i = 0; i < o.used; i++){
            temp[i+used] = o.arr[i];
        }
        temp.used = used+o.used;
        return temp;
    }


    bool operator!=(const iarr& o){
        if(size != o.size || used != o.used) return true;
        for(int i = 0; i<used; i++){
            if(arr[i] != o.arr[i]) return true;
        }
        return false;
    }

    bool operator==(const iarr& o){
        return !(operator!=(o));
    }


};


template <class T>
void swap2(T& a, T& b){
    T temp = move(a);
    a = move(b);
    b = move(temp);
}

int main(){
    iarr a;
    a.add(6);
    a.add(5);
    a.add(4);

    cout<<a<<endl;
    a.remove(0);
    cout<<a<<endl;
    iarr b(a);

    if(b==a) cout<<"lolol\n";
    b.add(7);
    
    swap2(a, b);
    
    
    cout<<a;
}