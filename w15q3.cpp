#include <iostream>

using namespace std;

template<typename T>
class LinkedList {
public :
    class Node {
    public :
        Node() : next(nullptr), data(0) {}

        Node(T d) : next(nullptr), data(d) {}

        Node(Node *n) : next(n), data(0) {}

        Node(Node *n, T d) : next(n), data(d) {}

        ~Node() {
            delete next;
        }

        T data;
        Node *next;
    };

    LinkedList() {
        head = nullptr;
    }

    ~LinkedList() {
        delete head;
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
        Node *curr = head;
        int index = 0;
        while (curr) {
            if (curr->data == d)
                return index;
            index++;
            curr = curr->next;
        }
        return -1;
    }

    T operator[](int i) {
        if (i < 0)
            return -1;
        Node *cur = head;
        while (i > 0) {
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

template<class T>
class Set : public LinkedList<T> {
public:
    Set<T>() : LinkedList<T>() {}

    bool addElement(T d) {
        if (this->searchData(d) == -1)
            return this->addFromTail(d);
        return false;
    }

    friend ostream &operator<<(ostream &o, Set<T> *s) {
        o << "{";
        typename LinkedList<T>::Node *cur = s->head;
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

    Set<T> *operator+(Set<T> *s) {
        Set<T> *ret = new Set<T>();
        typename LinkedList<T>::Node *cur = this->head;
        while (cur != nullptr) {
            ret->addElement(cur->data);
            cur = cur->next;
        }
        cur = s->head;
        while (cur != nullptr) {
            ret->addElement(cur->data);
            cur = cur->next;
        }
        return ret;
    }

    Set<T> *operator-(Set<T> *s) {
        Set<T> *ret = new Set<T>();
        typename LinkedList<T>::Node *cur = this->head;
        while (cur != nullptr) {
            if (s->searchData(cur->data) == -1)
                ret->addElement(cur->data);
            cur = cur->next;
        }
        return ret;
    }

    Set<T> *operator*(Set<T> *s) {
        Set<T> *ret = new Set<T>();
        typename LinkedList<T>::Node *cur = this->head;
        while (cur != nullptr) {
            if (s->searchData(cur->data) != -1)
                ret->addElement(cur->data);
            cur = cur->next;
        }
        return ret;
    }

    bool operator==(Set<T> *s) {
        if (this->getSize() != s->getSize())
            return false;
        typename LinkedList<T>::Node *cur = this->head;
        while (cur != nullptr) {
            if (s->searchData(cur->data) == -1)
                return false;
            cur = cur->next;
        }
        return true;
    }

    bool operator>(Set<T> *s) {
        if (this->getSize() <= s->getSize())
            return false;
        typename LinkedList<T>::Node *cur = s->head;
        while (cur != nullptr) {
            if (this->searchData(cur->data) == -1)
                return false;
            cur = cur->next;
        }
        return true;
    }

    bool operator<(Set<T> *s) {
        if (this->getSize() >= s->getSize())
            return false;
        typename LinkedList<T>::Node *cur = this->head;
        while (cur != nullptr) {
            if (s->searchData(cur->data) == -1)
                return false;
            cur = cur->next;
        }
        return true;
    }

    bool operator>=(Set<T> *s) {
        if (this->getSize() < s->getSize())
            return false;
        typename LinkedList<T>::Node *cur = s->head;
        while (cur != nullptr) {
            if (this->searchData(cur->data) == -1)
                return false;
            cur = cur->next;
        }
        return true;
    }

    bool operator<=(Set<T> *s) {
        if (this->getSize() > s->getSize())
            return false;
        typename LinkedList<T>::Node *cur = this->head;
        while (cur != nullptr) {
            if (s->searchData(cur->data) == -1)
                return false;
            cur = cur->next;
        }
        return true;
    }

};

int main() {
    Set<int> *s1 = new Set<int>();
    Set<int> *s2 = new Set<int>();
    s1->addElement(1);
    s1->addElement(2);
    s1->addElement(3);
    s1->addElement(4);
    s1->addElement(5);
    s2->addElement(4);
    s2->addElement(5);
    s2->addElement(6);
    s2->addElement(7);
    s2->addElement(8);
    cout << s1;
    cout << s2;
    cout << *s1 + s2;
    cout << *s1 - s2;
    cout << *s1 * s2;
    cout << s1;
    delete s1;
    return 0;
}