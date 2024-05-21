#include <iostream>

template <typename T>
class DynamicArray {
public:
    // Constructor
    DynamicArray(std::size_t size = 10) : size_(size), data(new T[size]) {}

    // Copy Constructor
    DynamicArray(const DynamicArray& other) : size_(other.size_), data(new T[other.size_]) {
        for (std::size_t i = 0; i < size_; ++i) {
            data[i] = other.data[i];
        }
        
    }

    DynamicArray(std::initializer_list<T> values) : size_(values.size()), data(new T[size_]) {
        std::copy(values.begin(), values.end(), data);
        
    }


    DynamicArray(DynamicArray&& other) : size_(other.size_), data(other.data) {
        other.data = nullptr;
        
    }

    // Move Assignment Operator
    DynamicArray& operator=(DynamicArray&& other) {
        size_ = other.size_;
        delete[] data;
        data = other.data;
        other.data = nullptr;
        return *this;
    }

    // Copy Assignment Operator
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            
            size_ = other.size_;
            data = new T[size_];

            for (std::size_t i = 0; i < size_; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~DynamicArray() {
        delete[] data;
    }

    T& operator[](std::size_t index) {
        return data[index];
    }

    const T& operator[](std::size_t index) const {
        return data[index];
    }

    std::size_t size() const {
        return size_;
    }

    class Iterator {
    public:
        Iterator(const DynamicArray& myClass, size_t index) : myClass(myClass), index(index) {}

        int operator*() const {
            return myClass.data[index];
        }

        Iterator& operator++() {
            ++index;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return index != other.index;
        }

    private:
        const DynamicArray& myClass;
        size_t index;
    };

    Iterator begin() const {
        return Iterator(*this, 0);
    }

    Iterator end() const {
        return Iterator(*this, size_);
    }

private:
    std::size_t size_;
    T* data;
};

int main() {
    DynamicArray<int> arr = {3, 2, 3, 4, 5, 6, 9, 4 ,3, 7, 2 ,2, 3, 6};

    
    //DynamicArray<int> obj = 5;

    //std::cout<<obj.size()<<std::endl;

    for (auto element : arr) {
        std::cout << element << " ";
    }
    std::cout<<std::endl;

    return 0;
}
