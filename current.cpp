#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class building{
public:
    int x1, x2, h;
    building* next = nullptr;

    building(int a, int b, int c){
        x1 = a;
        x2 = c;
        h = b;
    }

    void add(building* b){
        if(b->x1 > x2){
            next = new building(x2, 0, b->x1);
            next->next = b;
            return;
        }
        if(b->h > h){
            if(b->x2 < x2){
                b->next = new building(b->x2, h, x2);
                x2 = b->x1;
            }
        }
        else if(b->h < h){
            b->x1 = x2;
            if(b->x2 < x2){
                if (b->next != nullptr)
                    this->add(b->next);
                return;
            }
        }
        if (this->find(b->x2) != nullptr && this->find(b->x2) != this){
            b->add(this->find(b->x2));
        }
        next = b;
    }

    building* last(){
        if(next == nullptr)
            return this;
        return next->last();
    }

    building* find(int x){
        if(x < x1)
            return nullptr;
        if(x > x2 && next != nullptr)
            return next->find(x);
        if(next != nullptr && next->find(x) != nullptr)
            return next->find(x);
        return this;
    }

    void print(){
        cout << x1 << " " << h << " ";
        if(next != nullptr)
            next->print();
    }

};

class skyline{
public:
    building* head;
    skyline(){
        head = nullptr;
    }

    void add(int a, int b, int c){
        building* bld = new building(a, b, c);
        if(head == nullptr){
            head = bld;
            return;
        }
        building* cur = head->find(a);
        cur->add(bld);
    }
};


int main(){
    skyline* sk = new skyline();
    int a, b, c;
    while(cin.peek() != EOF){
        cin >> a >> b >> c;
        sk->add(a, b, c);
    }
    sk->add(a, 0, c + 1);
    sk->head->print();
}