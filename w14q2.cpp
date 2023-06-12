class ListNode {
public:
    int data;
    ListNode *prev, *next;
    ListNode(int Data, ListNode *p, ListNode *n){
        data = Data;
        prev = p;
        next = n;
    }
    ~ListNode() {
        if(prev)
            prev->next = next;
        if(next)
            next->prev = prev;
    }
};
