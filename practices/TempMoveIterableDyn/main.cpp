#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <class T>
class dyn{
    public:

    dyn(int cap = 0);

    dyn(const dyn<T>& o);
    const dyn<T>& operator=(const dyn<T>& o);
    ~dyn();
    
    dyn(dyn<T>&& o);
    dyn<T>& operator=(dyn<T>&& o);

    void add(const T& element);
    void remove(int index);
    void ensureCapacity();

    template<class A>
    friend ostream& operator<<(ostream& out, const dyn<A>& o);

    T& operator[](int index);
    const T& operator[](int index) const;
   

    dyn<T> operator+(const dyn<T>& o);

    bool operator!=(const dyn<T>& o);
    bool operator==(const dyn<T>& o);



    int size() const;

   class iterator {
    public:
        iterator(T* ptr) : current(ptr) {}

        T& operator*() const {
            return *current;
        }

        iterator& operator++() {
            ++current;
            return *this;
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        private:
        T* current;
   };

    iterator begin() const {
        return iterator(arr);
    }
    
    iterator end() const {
        return iterator(arr + used);
    }

    
    private:
    T* arr;

    int used;
    int capacity;
};


template<class T>
dyn<T>::dyn(int cap): capacity(cap) {
    used = 0;
    arr = new T[capacity];
}

template<class T>
dyn<T>::dyn(const dyn<T>& o): capacity(o.capacity), used(o.used) {
    arr = new T[capacity];
    for(int i = 0; i<used; i++){
        arr[i] = o.arr[i];
    }
}

template<class T>
const dyn<T>& dyn<T>::operator=(const dyn<T>& o){
    if(this == &o) return *this;
    T* old = arr;
    capacity = o.capacity;
    used = o.used;

    arr = new T[capacity];
    for(int i = 0; i<capacity; i++){
        arr[i] = o.arr[i];
    }
    delete[] old;
    return *this;
}

template<class T>
dyn<T>::~dyn(){
    delete[] arr;
}

template<class T>
dyn<T>::dyn(dyn<T>&& o): capacity(o.capacity), used(o.used) {
    arr = o.arr;
    o.arr = nullptr;
}

template<class T>
dyn<T>& dyn<T>::operator=(dyn<T>&& o){
    delete[] arr;
    capacity = o.capacity;
    used = o.used;
    arr = o.arr;
    o.arr = nullptr;
    return *this;
}

template<class T>
void dyn<T>::ensureCapacity(){
    if(used >= capacity){
        T* old = arr;
        capacity = 2 * capacity;
        arr = new T[capacity];
        for(int i = 0; i<used; i++){
            arr[i] = old[i];
        } delete[] old;
    }
}

template<class T>
void dyn<T>::add(const T& element){
    ensureCapacity();
    arr[used++] = element;

}

template<class T>
void dyn<T>::remove(int index){
    --used;
    for(int i = index; i<used; i++){
        arr[i] = arr[i+1];
    }
}

template <class A>
ostream& operator<<(ostream& out, const dyn<A>& o){
    if(o.arr != nullptr){
        out<<"Elements:";
        for(auto a: o){
            out<<" "<<a;
        }
    }
    return out;
}

template <class T>
T& dyn<T>::operator[](int index){
    return arr[index];
}

template <class T>
const T& dyn<T>::operator[](int index) const {
    return arr[index];
}


template <class T>
dyn<T> dyn<T>::operator+(const dyn<T>& o){
    dyn<T> temp(*this);
    for(int i = 0; i < o.used; i++){
        temp[i+used] = o.arr[i];
    }
    temp.used = used+o.used;
    return temp;
}

template <class T>
bool dyn<T>::operator!=(const dyn<T>& o){
    if(capacity != o.capacity || used != o.used) return true;
    for(int i = 0; i<used; i++){
        if(arr[i] != o.arr[i]) return true;
    }
    return false;
}

template <class T>
bool dyn<T>::operator==(const dyn<T>& o){
    return !(operator!=(o));
}

template <class T>
void swap2(T& a, T& b){
    T temp = move(a);
    a = move(b);
    b = move(temp);
}

int main(){
    dyn<int> a;
    a.add(6);
    a.add(5);
    a.add(4);

    cout<<a<<endl;
    a.remove(0);
    cout<<a<<endl;
    dyn<int> b(a);

    if(b==a) cout<<"lolol\n";
    b.add(7);
    
    swap2(a, b);
    
    
    cout<<a;
}