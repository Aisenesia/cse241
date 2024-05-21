#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using std::cout;
using std::endl;


template<class T>
class pfarray {
public:
    pfarray(int cap = 10);
    pfarray(const pfarray<T>& o);

    void addElement(const T& element);
    void deleteElement(const T& element);
    int findElement(const T& element) const;
    int getCap() const;
    int getUsed() const;
    void print() const;


    T& operator[](int index);
    pfarray& operator=(const pfarray<T>& o);

    ~pfarray();

protected:
    void incCapacity();
    void setCap(int new_cap);
    void setUsed(int new_used);

private:
    T* arr;
    int used;
    int capacity;
};

template<class T>
pfarray<T>::pfarray(int cap) : used(0), capacity(cap) {
    if (cap < 1) throw std::invalid_argument("Capacity must be at least 1");
    arr = new T[capacity];
}

template<class T>
pfarray<T>::pfarray(const pfarray<T>& o) : used(o.used), capacity(o.capacity) {
    arr = new T[capacity];
    for (int i = 0; i < used; ++i) {
        arr[i] = o.arr[i];
    }
}

template<class T>
pfarray<T>& pfarray<T>::operator=(const pfarray<T>& o) {
    if (this != &o) {
        delete[] arr;
        used = o.used;
        capacity = o.capacity;
        arr = new T[capacity];
        for (int i = 0; i < used; ++i) {
            arr[i] = o.arr[i]; 
        }
    }
    return *this;
}

template<class T>
pfarray<T>::~pfarray() {
    delete[] arr;
}

template<class T>
void pfarray<T>::incCapacity() {
    setCap(capacity*2);
    
}

template<class T>
void pfarray<T>::setCap(int new_cap) {
    if(new_cap<1){
        throw std::invalid_argument("invalid capacity value!");
    }
    if(capacity>new_cap) used = new_cap;//this is done if there need be to shrink array
    T* new_arr = new T[new_cap];  
    for (int i = 0; i < used; ++i) {
        new_arr[i] = arr[i];
    }
    delete[] arr;  
    arr = new_arr;
    capacity = new_cap;
    
    
}

template<class T>
void pfarray<T>::setUsed(int new_used) {
    if (new_used >= 0 && new_used <= capacity) {
        used = new_used;
    }
    else{
        throw std::invalid_argument("Invalid used value!");
    }
}

class myex{
    public:
    myex(const char* arr): emsg(arr){
        
    }
    const std::string& what() const{
        return emsg;
    }
    private:
    std::string emsg;
};

template<class T>
T& pfarray<T>::operator[](int index) {
    if(index<0 || index>capacity) throw myex("Invalid index!");
    else return arr[index];
}

template<class T>
void pfarray<T>::addElement(const T& element){
    if(capacity<used+2){
        incCapacity();
    }
    arr[used++] = element;
}

template <class T>
int pfarray<T>::findElement(const T& element) const {
    for(int i = 0; i<used; i++){
        if(element == arr[i]) return i;
    }
    return -1;
}

template <class T>
void pfarray<T>::deleteElement(const T& element){
    int index = findElement(element);
    if (index == -1) return;

    for(int i = index; i<used; i++){
        arr[i] = arr[i+1];
    } used--;
}

template <class T>
int pfarray<T>::getCap() const {
    return capacity;
}

template <class T>
int pfarray<T>::getUsed() const {
    return used;
}

template <class T>
void pfarray<T>::print() const {
    for(int i = 0; i<getUsed(); i++){
        cout<<"i: "<<i<<" -> "<<arr[i]<<endl;
    }
    cout<<"cap:"<<getCap()<<endl;
    cout<<"used:"<<getUsed()<<endl;
}

int main() {
    pfarray<double> myarr(20);
    pfarray<int> exception_test;
    for(int i = 0; i<24; i++){
        myarr.addElement((double)i*3.);
        exception_test.addElement(i*3);
        
    }
    myarr.deleteElement(33);

    pfarray<double> copied(myarr);
    pfarray<double> assigned;
    assigned = copied;
    assigned.print();

    
    bool flag = true;
    int inp;
    while(flag){
        try{
            flag = false;
            cout<<"enter an index: ";
            std::cin>>inp;
            cout<<exception_test[inp]<<endl;
        }
        catch(const myex& e){
            cout<<"catched exception throw: "<<e.what()<<endl;
            flag = true;
        }
    }

    //uncatched exception
    cout<<exception_test[-5];
}