#include <iostream>

using namespace std;

template <typename T> class LinkedList {
public :
    class Node {
    public :
        Node() : next(nullptr), data(0) {}

        Node(T d) : next(nullptr), data(d) {}

        Node(Node *n) : next(n), data(0) {}

        Node(Node *n, T d) : next(n), data(d) {}

        T data;
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

    bool addFromHead(T d) {
        head = new Node(head, d);
        return true;
    }

    bool addFromTail(T d) {
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

    int searchData(T d) {
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

    T operator[](int i){
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