#include <iostream>
#include <vector>
#include <string>

using std::ostream;
using std::cout;
using std::endl;
using std::vector;
using std::string;


template<class T1, class T2>
class pair{
    public:
    pair(){}
    pair(const T1& f, const T2& s):  first(f), second(s) {}
    pair(const pair<T1, T2>& o) : first(o.first), second(o.second) {}


    T1 getFirst() const {
        return first;
    }

    T2 getSecond() const {
        return second;
    }

    void setFirst(const T1& f) {
        first = f;
    }

    void setSecond(const T2& s) {
        second = s;
    }

    void setPair(const T1& f, const T2& s){
        first = f;
        second = s;
    }
    
    friend ostream& operator<<(ostream& out, const pair<T1, T2>& obj){
        out<<"("<<obj.first<<", "<<obj.second<<")";
        return out;
    }

     const pair<T2, T1> swap() {
        return pair<T2, T1>(second, first);
    }

    const pair operator+(const pair<T1, T2>& o) const {
        return pair<T1, T2>(first + o.first, second + o.second);
    }

    const pair operator-(const pair<T1, T2>& o) const {
        return pair<T1, T2>(first - o.first, second - o.second);
    }

    bool operator==(const pair& other) const {
        return (first == other.first) && (second == other.second);
    }

    bool operator!=(const pair& other) const {
        return !(*this == other);
    }

    private:
    T1 first;
    T2 second;
};




int main(){
    pair<int, int> obj;
    obj.setPair(5, 3);
    cout<<obj<<endl;

    pair<string, string> name("test", "type");

    cout<<name<<endl;

    
}