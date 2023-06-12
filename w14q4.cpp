#include <iostream>
using namespace std;

template<typename T>
class Set
{
public:
    Set(){
        count = 0;
    }

    Set(const Set& in){
        for(int i = 0; i < in.count; i++)
            element[i] = in.element[i];
        count = in.count;
    }

    int add(T in) {
        if(contains(in))
            return 0;
        if (count< 100) {
            element[count++] = in;
            return 1;
        }
        return 0;
    }

    int add(Set anotherSet) {
        int ret = 0;
        for (int i = 0; i < anotherSet.count; ++i) {
            ret += add(anotherSet.element[i]);
        }
        return ret;
    }

    void display()
    {
        int j;
        for(j = 0;j < count;j ++)
            std::cout<<element[j]<<" ";
    }

    Set operator+(const Set& in){
        Set tmp(*this);
        tmp.add(in);
        return tmp;
    }

    Set operator-(const Set& in){
        Set tmp;
        for(int i = 0; i < in.count; i++)
            if(this->contains(in.element[i]))
                tmp.add(in.element[i]);
        return tmp;
    }
private:
    T element[100];
    int count;

    bool contains(T in){
        for(int i = 0; i < count; i++)
            if(element[i] == in)
                return true;
        return false;
    }
};