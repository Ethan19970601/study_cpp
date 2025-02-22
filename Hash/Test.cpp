#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main()
{

    unordered_set<int> s;
    s.insert(5);
    s.insert(2);
    s.insert(6);
    s.insert(1);
    s.insert(4);
    // 迭代器
    unordered_set<int>::iterator it = s.begin();

    while(it != s.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;
    
    // 范围for
    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;

    unordered_map<string, string> dict;
    dict["sort"]; // 插入
    dict["sort"] = "哈哈哈"; // 修改
    dict["string"] = "六六六"; // 插入 + 修改
    dict["abc"] = "xxx";

    // 范围for遍历
    for (auto &kv: dict) // 这里用&的目的是避免代码拷贝，提高遍历效率
    {
        cout << kv.first << ": " << kv.second << endl;
    }
    cout << endl;
    return 0;
}