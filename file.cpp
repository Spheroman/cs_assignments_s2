#include <iostream>

using namespace std;

template<class T>
class Node
{
    T data;
    Node<T> *prev, *next;
public:
    Node(T d) : data(d), prev(NULL), next(NULL) {}
    operator T()
    {
        return data;
    }
    Node<T> *getPrev()
    {
        return prev;
    }
    Node<T> *getNext()
    {
        return next;
    }
    void setPrev(Node<T> *p)
    {
        prev = p;
    }
    void setNext(Node<T> *n)
    {
        next = n;
    }
};

template<class T>
class LinkedList
{
    Node<T> *head, *tail;
public:
    LinkedList() : head(NULL), tail(NULL) {}
    Node<T> *insertFromHead(T d)
    {
        Node<T> *newNode = new Node<T>(d);
        if(head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->setNext(head);
            head->setPrev(newNode);
            head = newNode;
        }
        return newNode;
    }
    Node<T> *insertFromTail(T d)
    {
        Node<T> *newNode = new Node<T>(d);
        if(tail == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        }
        return newNode;
    }
    Node<T> *removeFromHead()
    {
        Node<T> *j = head;
        if(head != NULL)
        {
            head = head->getNext();
            if(head != NULL)
                head->setPrev(NULL);
            else
                tail = NULL;
        }
        if(j != NULL)
            j->setNext(NULL);
        return j;
    }
    Node<T> *removeFromTail()
    {
        Node<T> *j = tail;
        if(tail != NULL)
        {
            tail = tail->getPrev();
            if(tail != NULL)
                tail->setNext(NULL);
            else
                head = NULL;
        }
        if(j != NULL)
            j->setPrev(NULL);
        return j;
    }
    operator int()
    {
        int size = 0;
        Node<T> *j = head;
        while(j != NULL)
        {
            size ++;
            j = j->getNext();
        }
        return size;
    }
    friend ostream &operator<<(ostream &out, const LinkedList<T> ll)
    {
        cout << "[";
        Node<T> *j = ll.head;
        while(j != NULL)
        {
            if(j != ll.head)
                cout << ", ";
            cout << *j;
            j = j->getNext();
        }
        cout << "]";
    }
};

template<class T>
class Stack : public LinkedList<T>
{
public:
    Node<T> *pop()
    {
        return this->removeFromHead();
    }
    Node<T> *push(T d)
    {
        return this->insertFromHead(d);
    }
};

int main()
{
    //Node<int> *n = new Node<int>(10);
    //cout << *n;
    /*LinkedList<int> *ll = new LinkedList<int>();
    int j;
    for(j = 1;j <= 5;j ++)
      ll->insertFromHead(j);
    for(j = 6;j <= 10;j ++)
      ll->insertFromTail(j);
    cout << *ll << endl;
    Node<int> *k = ll->removeFromTail();
    while(k != NULL)
    {
      cout << *k << endl;
      int s = *ll;
      cout << s << ":" << *ll << endl;
      k = ll->removeFromTail();
    }*/
    Stack<char> *stack = new Stack<char>();
    int j;
    for(j = 'A';j < 'E';j ++)
        stack->push(j);
    int s = *stack;
    while(s > 0)
    {
        Node<char> *d = stack->pop();
        cout << *d << endl;
        s = *stack;
    }
}