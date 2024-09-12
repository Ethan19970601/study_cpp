#include <iostream>
#include <set>
using namespace std;

void test_set1()
{
    set<int> s;
    s.insert(5);
    s.insert(2);
    s.insert(6);
    s.insert(1);
    s.insert(1);
    s.insert(2);
    s.insert(5);
    s.insert(5);
    // 接受 insert 的返回值
    pair<set<int>::iterator, bool> ret1 = s.insert(5);
    cout << ret1.second << endl;
    // 但是这里我们可以简写：auto
    auto ret2 = s.insert(5);
    cout << ret2.second << endl;

    // 遍历方法使用迭代器
    set<int>::iterator it = s.begin();
    while (it != s.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;

    // 范围 for
    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;

    // erase
    s.erase(2);
    set<int>::iterator it1 = s.find(3);
    if (it1 != s.end())
    {
        s.erase(it1);
    }
    cout << endl;

    // 范围 for
    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;
}

void test_set2()
{
    set<int> myset;
    set<int>::iterator itlow, itup;
    for (int i = 1; i < 10; i++)
    {
        myset.insert(i * 10);
    }

    itlow = myset.lower_bound(30);
    itup = myset.upper_bound(60);

    myset.erase(itlow, itup);

    for (auto e : myset)
    {
        cout << e << " ";
    }
}

void test_set3()
{
    std::set<int> myset;

    for (int i = 1; i <= 5; i++)
        myset.insert(i * 10); // myset: 10 20 30 40 50

    std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator> ret;
    ret = myset.equal_range(30);

    std::cout << "the lower bound points to: " << *ret.first << '\n';
    std::cout << "the upper bound points to: " << *ret.second << '\n';
}

void test_set4()
{
    multiset<int> s;
    s.insert(5);
    s.insert(2);
    s.insert(6);
    s.insert(1);
    s.insert(1);
    s.insert(2);
    s.insert(5);
    s.insert(5);

    multiset<int>::iterator it = s.begin();
    while (it != s.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;

   // auto ret = s.equal_range(2);
   // s.erase(ret.first, ret.second);
    s.erase(2);
    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;
}

int main()
{
    // test_set1();
    // test_set2();
    // test_set3();
    test_set4();
    return 0;
}