#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

template<typename T>
class LinkedListNode
{
public:
    LinkedListNode();
    LinkedListNode(T const&);
    LinkedListNode* getNext();
    LinkedListNode* getPrev();
    T getData();
    void setData(T&);

private:
    T data_;
    LinkedListNode* Next;
    LinkedListNode* Prev;
};

#endif // LINKEDLISTNODE_H
