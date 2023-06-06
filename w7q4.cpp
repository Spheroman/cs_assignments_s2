#include <iostream>
using namespace std;

class Alphabet {
private:
    char ch;
public:
    Alphabet(int ch) {
        this->ch = ch;
    }


    friend ostream& operator<<(ostream& os, const Alphabet& obj) {
        os << obj.ch;
        return os;
    }

    void operator<<(int n){
        int base;
        if(ch>='A'&&ch<='Z')
            base='A';
        else
            base='a';
        ch-=n;
        while(ch<base)
            ch+=26;
    }
    void operator>>(int n){
        int base;
        if(ch>='A'&&ch<='Z')
            base='Z';
        else
            base='z';
        ch+=n;
        while(ch>base)
            ch-=26;
    }
};

int main() {
    Alphabet a('X'), b('c');
    cout << a << endl; // display X
    cout << b << endl; // display c
    a >> 3;
    b << 4;
    cout << a << endl; // display A
    cout << b << endl; // display y

    return 0;
}