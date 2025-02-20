#include <iostream>
#include "RBTree.h"
using namespace std;

int main()
{
    int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
    RBTree<int, int> t;
    for (auto e : a)
    {
        t.Inster(make_pair(e, e));
    }
    t.InOrder();

    cout << t.IsBalance() << endl;

    return 0;
}