#include <iostream>
#include <cmath>
#include <string>


class Container {
public:
    virtual void push(int) = 0;
    virtual void pop() = 0;
    virtual int top() const = 0;
    virtual bool empty() const = 0;
};

class Node{
public:
    int value;
    Node* next;
    bool tail;
    Node(int i, Node* n){
        value = i;
        next = n;
    }
};

class Stack: public Container {
    Node* head = nullptr;
    void push(int i) override{
        head = new Node(i, head);
    }

    void pop() override{
        if(!head){
            throw std::out_of_range("");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    int top() const override{
        if(!head)
            throw std::out_of_range("");
        return head->value;
    }

    bool empty() const override{
        return !head;
    }

};
class PriorityQueue: public Container {
    Node* head = new Node(0, nullptr);

    PriorityQueue(){
        head->tail = true;
    }

    void push(int i) override{
        Node* cur = head;
        while(!cur->tail && cur->value > i)
            cur = cur->next;
        cur->next = new Node(cur->value, cur->next);
        cur->next->tail = cur->tail;
        cur->tail = false;
        cur->value = i;
    }

    void pop() override{
        if (head->tail)
            throw std::out_of_range("");
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }

    int top() const override{
        if (head->tail)
            throw std::out_of_range("");
        return head->value;
    }

    bool empty() const override{
        return head->tail;
    }

};


int main(){

}