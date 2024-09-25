#include <iostream>
#include <set>
#include <map>
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

void test_map1()
{
    map<string, string> dict;

    dict.insert(pair<string, string>("sort", "排序"));
    dict.insert(pair<string, string>("insert", "插入"));
    dict.insert(pair<string, string>("left", "左边"));
    dict.insert(make_pair("right", "右边"));
    dict.insert(make_pair("left", "左边"));
    // 迭代器遍历
    map<string, string>::iterator it = dict.begin();
    while (it != dict.end())
    {
        cout << (*it).first << ":";
        cout << (*it).second << endl;
        ++it;
    }
    cout << endl;

    // 范围 for遍历
    for (const auto &kv : dict)
    {
        cout << kv.first << ":" << kv.second << endl;
    }
}

void test_map2() // 用 map 来统计次数
{

    string arr[] = {"苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉"};
}

int main()
{
    test_map1();
    test_map2();
    return 0;
}
