
---

[本节目标]

1. 关联式容器

2. 键值对

3. 树形结构的关联式容器

4. 底层结构

# 🏷️ 关联式容器

序列式容器：vector list 栈 队列 (类似以前学习的线性表).....
关联式容器： map set .....

关联式容器，数据与数据之间有很强的关联，并不是单纯的存储数据

关联式容器也是用来存储数据的，与序列式容器不同的是，其里面存储的是``<key, value>``结构的键值对，在数据检索时比序列式容器效率更高。
 

# 🏷️ 键值对

用来表示具有一一对应关系的一种结构，该结构中一般只包含两个成员变量``key``和``value``，``key``代表键值，``value``表示与``key``对应的信息。比如：现在要建立一个英汉互译的字典，那该字典中必然有英文单词与其对应的中文含义，而且，英文单词与其中文含义是一一对应的关系，即通过该应该单词，在词典中就可以找到与其对应的中文含义。

# 🏷️ 树形结果的关联式容器

根据应用场景的不同，STL总共实现了两种不同结构的管理式容器：**树型结构**与**哈希结构**。树型结
构的关联式容器主要有四种：``map、set、multimap、multiset``。这四种容器的共同点是：使
用**平衡搜索树(即红黑树)** 作为其底层结果，容器中的元素是一个有序的序列。下面一依次介绍每一
个容器。

## 📌 set

set 是 key搜索模型的容器，用来判断在不在的，所以我们可以增加，删除，查看，==但是没有修改==  

来，我们浅浅感受一下set
```c++
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

    // 遍历方法使用迭代器
    set<int>::iterator it = s.begin();
    while (it != s.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;
}

int main()
{
    test_set1();
    return 0;
}
```

上面👆🏻代码的运行结果是：
```c++
1 2 5 6
```

观察这个结果，我们可以知道，底层是搜索树，走的是中序遍历，不会往里面插入重复的值，

### ✏️ 我们在这里提一下：``pair``


我们通过刚才的的实验知道，``insert``  不会插入重复的元素，如果是重复的元素，insert 函数会返回 ``false``
但是我们这里没法使用 ``bool`` 值来接收它的放回值，因为这里的``insert`` 函数的返回值并不是只返回了``bool``
[set : insert 函数的返回值](https://legacy.cplusplus.com/reference/set/set/insert/)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/bd70d1847da4441ba5e644ada87bb45a.png)
**❓ 那什么是[pair](https://legacy.cplusplus.com/reference/utility/pair/?kw=pair)?** 

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/03ed43e973ce4f7595a120d8c0d1d412.png)

这也就意味着我们可以这样来接收``insert`` 函数的返回值：

```c++
pair< set<int>::iterator,  bool> ret1 = s.insert(5);
// 打印：
cout << ret1.second << endl; // 取到这个 bool 值
```

这里我们也可以简写：

```c++
 auto ret2 = s.insert(5);
 cout << ret2.second << endl;
```


### ✏️ 回到我们的 set

 **我们除了用迭代器来遍历，我们同样也可以使用范围 for**

```c++
    // 范围 for
    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;
```

> 栈不能用范围 for 。因为栈没有**迭代器**。范围 for 的底层是==替换成迭代器==，只要支持迭代器就支持范围 for 

### ✏️ [erase 删除](https://legacy.cplusplus.com/reference/set/set/erase/)

举个例子，比如我们要把 ``2`` 给删除了

**方式一：**``s.erase(2)``

**方式二** ：
```c++
set<int>::iterator it = s.find(2);
if (it != s.end())
{
	s.erase(it);
}
cout << endl;
```

**``find函数``的[返回值](https://legacy.cplusplus.com/reference/set/set/find/)是一个迭代器，如果找到了 就返回指向当前元素的迭代器，如果没找到就返回 end**
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ae0e10dc07c745f7b3f090c9640eb7e9.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/24c604b66e4e4fb68efdde94395b4cc0.png)

如果是删除的一个不存在的值：比如
```c++
s.erase(1000)  // 1000 不在我们的set<int> s之中，但是，这样写程序也不会崩溃，不会有任何事情发生
 ```

### ✏️ ``lower_bound`` , ``upper_bound`` 函数

```c++
void test_set2()
{
    set<int> myset;
    set<int>::iterator itlow, itup;
    for (int i = 1; i < 10; i++)
    {
        myset.insert(i * 10);
    }

    itlow = myset.lower_bound(30); // >= val值位置的 iterator
    itup = myset.upper_bound(60);  // > val值位置的 iterator

    myset.erase(itlow, itup);

    for(auto e:myset)
    {
        cout << e << " ";
    }
}
```


``lower_bound（val）``: 返回的是：值 >= val 位置的 迭代器 
``upper_bound（val）``: 返回的是：值 > val 位置的 迭代器 


### ✏️ [equal_range](https://legacy.cplusplus.com/reference/set/set/equal_range/)函数

```c++
// set::equal_elements
#include <iostream>
#include <set>

int main ()
{
  std::set<int> myset;

  for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50

  std::pair<std::set<int>::const_iterator,std::set<int>::const_iterator> ret;
  ret = myset.equal_range(30);

  std::cout << "the lower bound points to: " << *ret.first << '\n';
  std::cout << "the upper bound points to: " << *ret.second << '\n';

  return 0;
}
```

运行结果：
```c++
the lower bound points to: 30
the upper bound points to: 40
```
这个函数的返回值类型也是：``pair`` 类型，其中``first`` 是 >= val 的值，``second`` 是 > val 的值

> 注意： set 不支持 修改

###  ✏️ multiset

set: 排序 + 去重 ，可以查找在不在

multiset: 排序 但是不去重

```c++
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

}
```

这段代码运行结果：
```c++
1 1 2 2 5 5 5 6 
```

这个 multiset 也是走的中序。

**❓ 来看看这个 multiset 的迭代器，如果有多个值，那我们返回哪个值呢？**

```c++
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

    // 如果有多个2，Find 返回中序的第一个 2
    it = s.find(2);
    while (it != s.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;
}
```


==如果有多个值，Find 返回中序的第一 个val==

🧲 **equal_range** 在 muliset 中的使用：

比如你想把下面代码中所有的 2 都删除掉

```c++
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
// 目的是把所有的 2 都删除掉，我们可以这样做：
    auto ret = s.equal_range(2);
    s.erase(ret.first, ret.second);
// 打印删除之后的结果
    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;
}
```

上面👆🏻代码中``equal_range(2)``，``first`` 是 ``>= 2`` 的值，``second`` 是 ``> 2`` 的值，类比到数学中的区间就是：
```
[>=2, >2)
```

**❓ 如果我在 multiset 容器里使用（结合上面代码）：``s.erase(2)`` 它是删一个 2 还是把所有的 2全部删除？**

```c++
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

    s.erase(2);
    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;
}
```

运行上面👆🏻的代码，我们发现它是全删的。

## 📌[map](https://legacy.cplusplus.com/reference/map/map/)

我们先来简单的创建一个``map`` 类型的 ``dict`` （这是字典的英文缩写）我们想要用 map 来实现一个简单的字典的功能，比如：sort 是 排序的意思。 insert 是插入的意思

```c++
void test_map1()
{
    map<string, string> dict;
    
}

int main()
{
    test_map1();
    return 0;
}
```

那我们如何向里面插入数据呢？

### ✏️ map 如何插入数据？

我们看到``map`` 的相关知识：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d7819ed22ca34cef9e7b03ac2be4353b.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6807f96ceee646c199890155701be3d7.png)

所以我们可以这样插入：

```c++
dict.insert( pair<string, string>("sort", "排序") );
dict.insert( pair<string, string>("insert", "插入") );
```

- `dict`：这是一个`std::map`类型的变量，用于存储键值对。
- `insert`：这是`std::map`的成员函数，用于向映射中插入一个元素。
- `pair<string, string>`：这是`std::pair`类型的一个实例，用于表示键值对。
- `"sort"`：这是键（key），在`std::map`中，键是唯一的，用于查找元素。
- `"排序"`：这是值（value），与键相关联的数据。

#### 🧲 除了上面的那种插入方式之外，我们还可以使用``make_pair``来进行插入

看代码：

```c++
dict.insert( make_pair("right", "右边") );
dict.insert( make_pair("left", "左边") );

```

##### 什么是``make_pair`` ❓

`std::make_pair` 是 C++ 标准库中的一个==函数模板==，它用来创建一个 `std::pair` 对象。`std::pair` 是一个模板类，用于存储一个包含两个元素的组合，这两个元素可以是不同的类型。**`std::make_pair` 函数简化了 `std::pair` 对象的创建过程，使得代码更加清晰和易于理解**

`std::make_pair` 的基本语法如下：

```cpp
std::make_pair(T1 a, T2 b);
```

- **T1** 和 **T2** 是模板参数，表示两个元素的类型。
- **a** 是第一个元素的值。
- **b** 是第二个元素的值。

返回值：

`std::make_pair` 返回一个 `std::pair<T1, T2>` 类型的对象，其中 `T1` 和 `T2` 是自动推断的类型。

简单来说，使用``make_pair``我们就可以不用写具体的类型了，这个函数模板会自动的推断类型

### ✏️ 遍历

#### 迭代器遍历

```c++
    map<string, string>::iterator it = dict.begin();
    while (it != dict.end())
    {
        cout << (*it).first << ":";
        cout << (*it).second << endl;
        ++it;
    }
    cout << endl;
}
```

#### 范围 for 遍历

```c++
    //范围 for遍历
    for (auto kv : dict)
    {
        cout << kv.first << ":" << kv.second << endl;
    }
```

但是上面👆🏻的写法有点小瑕疵，因为范围 for 是依次取这里``dict`` 里面的数据，再来转换成迭代器的，然后把``*it`` 赋值给``kv`` , ``*it`` 是一个 ``pair``  类型的，这个``pair`` 类型里面还是个``string`` 。赋值给``kv`` 的话，这里的``string`` 就是一个深拷贝，代价太大了，所以我们用引用，如下：

```c++
    //范围 for遍历
    for (const auto &kv : dict)
    {
        cout << kv.first << ":" << kv.second << endl;
    }
```

目前代码：

```c++
#include <iostream>
#include <map>
using namespace std;


void test_map1()
{
    map<string, string> dict;

    dict.insert(pair<string, string>("sort", "排序"));
    dict.insert(pair<string, string>("insert", "插入"));
    dict.insert(pair<string, string>("left", "左边"));
    dict.insert(make_pair("right", "右边"));
    dict.insert(make_pair("left", "左边"));

    map<string, string>::iterator it = dict.begin();
    while (it != dict.end())
    {
        cout << (*it).first << ":";
        cout << (*it).second << endl;
        ++it;
    }
    cout << endl;
}

int main()
{
    test_map1();
    return 0;
}

```

> map 不支持 key 的修改，但是支撑 value 的修改
