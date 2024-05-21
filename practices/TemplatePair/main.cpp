#include <iostream>
#include <vector>
#include <string>

using std::ostream;
using std::cout;
using std::endl;
using std::vector;
using std::string;


template<class T>
class pair{
    public:
    pair(){}
    pair(const T& f, const T& s):  first(f), second(s) {}
    pair(pair<T>& o);

    void setPair(const T& f, const T& s){
        first = f;
        second = s;
    }
    
    friend ostream& operator<<(ostream& out, const pair<T>& obj){
        out<<"("<<obj.first<<", "<<obj.second<<")";
        return out;
    }

    void swap(){
        T temp = first;
        first = second;
        second = temp;
    }

    const pair operator+(const pair<T>& o) const {
        pair<T> temp;
        temp.first = first + o.first;
        temp.second = second + o.second;
        return temp;
    }

    const pair operator-(const pair<T>& o) const {
        pair<T> temp;
        temp.first = first - o.first;
        temp.second = second - o.second;
        return temp;
    }

    bool operator==(const pair<T>& other) const {
        return (first == other.first) && (second == other.second);
    }

    bool operator!=(const pair<T>& other) const {
        return !(*this == other);
    }

    private:
    T first;
    T second;
};




int main(){
    pair<int> obj;
    obj.setPair(5, 3);
    cout<<obj<<endl;

    pair<string> str1("test", "type");
    pair<string> str2("type", "test");

    str2.swap();

    if(str1==str2){
        cout<<"pairs are the same"<<endl;
    }
    cout<<str2<<endl;

    pair<int> obj2(3, 4);

    cout<<obj+obj2<<endl;
    cout<<obj-obj2<<endl;
    return 0;
}