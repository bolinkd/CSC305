#include <iostream>
#include "rectangle.h"
#include "linkedlistnode.h"

using namespace std;

int main()
{
    Rectangle x;
    cout << x.Area() << endl;

    int stuff = 12;
    LinkedListNode<int> head(stuff);
    cout << "Stuff: " << head.getData() << endl;


    return 0;
}

