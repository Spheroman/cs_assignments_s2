#include <iostream>

using namespace std;

class LinkedList {
public :
    class Node {
    public :
        Node() : next(nullptr), data(0) {}

        Node(int d) : next(nullptr), data(d) {}

        Node(Node *n) : next(n), data(0) {}

        Node(Node *n, int d) : next(n), data(d) {}

        int data;
        Node *next;
    };

    LinkedList() {
        head = nullptr;
    }

    ~LinkedList() {
        Node *cur = head;
        while (cur != nullptr) {
            Node *tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }

    bool addFromHead(int d) {
        head = new Node(head, d);
        return true;
    }

    bool addFromTail(int d) {
        if (head == nullptr)
            head = new Node(d);
        else {
            Node *cur = head;
            while (cur->next != nullptr)
                cur = cur->next;
            cur->next = new Node(d);
        }
        return true;
    }

    bool removeFromHead() {
        if (head == nullptr)
            return false;
        Node *temp = head;
        head = temp->next;
        delete temp;
        return true;
    }

    bool removeFromTail() {
        if (head == nullptr)
            return false;
        Node *last = nullptr;
        Node *cur = head;
        while (cur->next) {
            last = cur;
            cur = cur->next;
        }
        delete cur;
        if (last)
            last->next = nullptr;
        else
            head = nullptr;
        return true;
    }

    friend ostream &operator<<(ostream &o, LinkedList *l) {
        o << "{";
        Node *cur = l->head;
        while (cur != nullptr) {
            o << cur->data;
            cur = cur->next;
            if (cur != nullptr) {
                o << ", ";
            }
        }
        o << "}";
        cout << endl;
        return o;
    }

    size_t getSize() const {
        size_t size = 0;
        Node *cur = head;
        while (cur != nullptr) {
            size++;
            cur = cur->next;
        }
        return size;
    }

    int searchData(int d) {
        int idx = 0;
        Node *cur = head;
        while(idx != -1){
            if(cur->data == d)
                break;
            if(cur->next == nullptr)
                idx = -2;
            idx++;
            cur = cur->next;
        }
        return idx;
    }

    int operator[](int i){
        if(i < 0)
            return -1;
        Node *cur = head;
        while(i > 0){
            i--;
            cur = cur->next;
            if (cur == nullptr)
                return -1;
        }
        return cur->data;
    }

protected :
    Node *head;
};

int main() {
    LinkedList *l = new LinkedList();
    cout << l;
    l->addFromHead(1);
    cout << l;
    l->removeFromTail();
    cout << l;
    l->addFromHead(2);
    l->addFromHead(3);
    l->addFromHead(4);
    l->addFromHead(5);
    cout << l;
    l->addFromTail(6);
    l->addFromHead(7);
    l->addFromHead(8);
    l->addFromHead(9);
    l->addFromHead(10);
    cout << l;
    cout << l->getSize() << endl;
    cout << l->searchData(5) << endl;
    cout << l->searchData(10) << endl;
    cout << l->searchData(1) << endl;
    cout << (*l)[0] << endl;
    cout << (*l)[1] << endl;
    cout << (*l)[2] << endl;
}