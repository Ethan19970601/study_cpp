# unordered系列关联式容器

在C++98中，STL提供了底层为红黑树结构的一系列关联式容器，在查询时效率可达到$log_2N$，即最差情况下需要比较红黑树的高度次，当树中的节点非常多时，查询效率也不理想。最好的查询是，进行很少的比较次数就能够将元素找到，因此在C++11中，STL又提供了4个unordered系列的关联式容器，这四个容器与红黑树结构的关联式容器使用方式基本类似，只是其底层结构不同。

## 关联式容器和序列式容器

在c++ 中关联式容器是一类标准模板库（stl)提供的容器类型，与序列容器不同，它主要用于存储元素，并且通过元素的键值（key) 来快速访问和操作这些元素。关联式容器的元素通常是基于键值排序的，以提供对特定元素的快速查找。

### 主要关联式容器

C++ 标准模板库提供了以下几种关联式容器：

1. **`set`**
    - **定义**：`set` 是一个排序的容器，存储唯一元素。
    - **特点**：
        - 元素唯一，不存储重复值。
        - 元素按照升序或降序（默认升序）排列。
        - 提供对数级别的插入、删除和查找操作时间复杂度。
    - **使用场景**：适用于需要存储唯一元素，并且需要按顺序访问或快速查找的场景。
2. **`multiset`**
    - **定义**：与`set`类似，但允许存储重复的元素。
    - **特点**：
        - 元素可以重复，允许同一值出现多次。
        - 元素按有序排列，相同的元素相邻。
        - 与`set`相同的时间复杂度。
    - **使用场景**：适用于需要存储可重复元素，并且需要按顺序访问或快速查找的场景。
3. **`map`**
    - **定义**：`map` 是一个键值对（Key-Value）的有序容器，每个键值对中的键是唯一的。
    - **特点**：
        - 键值对中的键（Key）唯一，值（Value）可以重复。
        - 根据键的升序或降序排列。
        - 提供通过键快速查找值的功能。
    - **使用场景**：适用于需要通过键值快速查找对应值，并且键值对按顺序存储的场景。
4. **`multimap`**
    - **定义**：与`map`类似，但允许存储多个相同的键。
    - **特点**：
        - 键可以重复，允许同一键对应多个值。
        - 元素按有序排列，相同的键对应的元素相邻。
    - **使用场景**：适用于需要存储可重复键，并且需要按顺序访问或快速查找的场景。

### 关联式容器与序列容器的区别

与序列容器（如`vector`、`list`等）不同，关联式容器在存储和管理元素的方式上侧重于快速查找和有序存储，而序列容器更关注元素的线性排列和顺序访问。
关联式容器通常用于需要快速查找和有序存储的场景，例如：

- 管理一个电话簿（使用`map`，键为姓名，值为电话号码）。
- 统计学生的考试成绩（使用`multiset`，存储多个学生成绩，按顺序排列）。
- 维护一个单词词典（使用`set`，存储唯一的单词）。

## unordered_map

[unordered_map](https://cplusplus.com/reference/unordered_map/unordered_map/?kw=unordered_map) 在线文档

我们之间也学过一个`map` 那这个`unordered_map` 和我们之前学的  map 有什么区别吗？

我们之前学的那个map 底层是红黑树，而这个`unordered_map` 底层是哈希，所以这样会更好理解一点：之前学的 map 我们可以称之为`tree_map` 。现在这个`unordered_map` 我们可以称之为`hash_map` ，之所以要叫`unordered` 这个名字，是因为这个`unordered`的单词意思是：无序。由于unorderde_map 的底层是哈希表所以它的元素是无序的，但是map的底层是红黑树，它的元素是有序的

`unordered_map` 是 C++ 标准模板库（STL）中的一个关联式容器，它基于哈希表（hash table）实现，存储键值对（key-value pairs）。`unordered_map` 的设计目标是在平均情况下提供较快速的插入、删除和查找操作。以下是对 `unordered_map` 的详细介绍：

### 1. **基本概念**

- **键值对存储**：`unordered_map` 中的每个元素都是一个键值对，键（`key`）是唯一的，值（`value`）可以重复。
- **无序性**：元素的存储顺序是==无序的==，这与 `map`（基于红黑树实现）的有序性不同。

### 2. **底层实现**

- 基于哈希表（hash table）实现。哈希表通过哈希函数将键映射到存储位置（桶），从而实现快速访问。
- 如果不同的键被哈希到相同的存储位置（冲突），通常使用链地址法（拉链法）或开放地址法来解决冲突。

### 3. **主要特点**

- **高效查找、插入和删除**：在平均情况下，`unordered_map` 的查找、插入和删除操作的时间复杂度为 O(1)。但在最坏情况下（哈希冲突频繁），时间复杂度可能为 O(N)。
- **不保证元素顺序**：元素的存储顺序是无序的，无法按特定顺序遍历元素。
- **键的唯一性**：每个键在 `unordered_map` 中只能出现一次。如果需要存储多个相同的键，可以使用 `unordered_multimap`。

### 4. **常用操作**

- **插入元素**：使用 `insert()` 或 `operator[]` 插入键值对。
- **查找元素**：通过 `operator[]`、`at()` 或 `find()` 查找键对应的值。
- **删除元素**：使用 `erase()` 删除指定键的元素。
- **遍历容器**：通过迭代器遍历所有键值对。

### 5. **示例代码**

```cpp
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<int, string> umap;

    // 插入元素
    umap[1] = "apple";
    umap[2] = "banana";
    umap[3] = "cherry";

    // 查找元素
    cout << "Key 2: " << umap[2] << endl;

    // 插入新元素
    umap.insert(pair<int, string>(4, "date"));

    // 遍历容器
    cout << "All elements:" << endl;
    for (auto& pair : umap) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // 删除元素
    umap.erase(3);

    // 处理不存在的键
    if (umap.find(5) != umap.end()) {
        cout << "Key 5 found" << endl;
    } else {
        cout << "Key 5 not found" << endl;
    }

    return 0;
}
```

### 6. **适用场景**

- **快速查找和插入**：适用于需要快速查找和插入键值对的场景，例如模拟数据库索引、字典等。
- **大容量数据处理**：由于高效的操作时间复杂度，适用于处理大量数据的场景。

`unordered_map` 是 C++ 中非常强大且灵活的容器之一，特别适用于需要快速查找和插入操作的场景。通过合理使用哈希函数，可以充分发挥其性能优势。

> unordered_map是存储<key, value>键值对的关联式容器，其允许通过keys快速的索引到与其对应的value。
在unordered_map中，键值通常用于惟一地标识元素，而映射值是一个对象，其内容与此键关联。键和映射值的类型可能不同。
在内部,unordered_map没有对<kye, value>按照任何特定的顺序排序, 为了能在常数范围内找到key所对应的value，unordered_map将相同哈希值的键值对放在相同的桶中。
unordered_map容器通过key访问单个元素要比map快，但它通常在遍历元素子集的范围迭代方面效率较低。
unordered_maps实现了直接访问操作符(operator[])，它允许使用key作为参数直接访问value。
它的迭代器至少是前向迭代器。

## unordered_map 接口说明

### `unordered_map` 的构造

`unordered_map` 提供了多种构造方式：

#### **1. 默认构造**

```cpp
unordered_map<int, std::string> myMap;
```

创建一个空的 `unordered_map`，键的类型为 `int`，值的类型为 `std::string`。

#### **2. 使用初始化列表构造**

```cpp
unordered_map<int, std::string> myMap = {
    {1, "Alice"},
    {2, "Bob"},
    {3, "Charlie"}
};
```

通过初始化列表直接填充 `unordered_map`。

#### **3. 通过范围构造**

```cpp
// 已经有一个范围，可以是数组、另一个容器等
std::vector<std::pair<int, std::string>> vec = {
    {1, "Apple"}, {2, "Banana"}, {3, "Cherry"}
};
unordered_map<int, std::string> myMap(vec.begin(), vec.end());
```

### `unordered_map` 的容量

   `unordered_map` 提供了以下函数来查询其容量：

#### **1. `empty()`**

```cpp
if (myMap.empty()) {
    std::cout << "The map is empty." << std::endl;
}
```

检查 `unordered_map` 是否为空。

#### **2. `size()`**

```cpp
std::cout << "The size is: " << myMap.size() << std::endl;
```

返回 `unordered_map` 中键值对的数量。

### `unordered_map` 的迭代器

`unordered_map` 的迭代器支持以下操作：

#### **1. `begin()` 和 `end()`**

```cpp
for (auto it = myMap.begin(); it != myMap.end(); ++it) {
    std::cout << it->first << " : " << it->second << std::endl;
}
```

`begin()` 返回指向第一个元素的迭代器，`end()` 返回指向最后一个元素之后位置的迭代器。

#### **2. `cbegin()` 和 `cend()`**

```cpp
for (auto it = myMap.cbegin(); it != myMap.cend(); ++it) {
    std::cout << it->first << " : " << it->second << std::endl;
}
```

返回常量迭代器，用于只读访问。

### `unordered_map` 的元素访问

`unordered_map` 提供了以下几种访问元素的方式：

#### **1. `operator[]`**

```cpp
myMap[4] = "Date";
std::cout << myMap[4] << std::endl; // 输出 "Date"
```

如果键不存在，`operator[]` 会插入一个默认构造的值。

#### **2. `at()`**

```cpp
try {
    std::cout << myMap.at(5) << std::endl;
} catch (const std::out_of_range& e) {
    std::cout << "Key not found." << std::endl;
}
```

`at()` 会检查键是否存在，如果不存在，会抛出 `std::out_of_range` 异常。

### `unordered_map` 的查询

`unordered_map` 提供了以下查询函数：

#### **1. `find()`**

```cpp
auto it = myMap.find(2);
if (it != myMap.end()) {
    std::cout << "Found: " << it->second << std::endl;
}
```

`find()` 返回一个迭代器，指向键对应的元素，如果找不到则返回 `end()`。

#### **2. `count()`**

```cpp
if (myMap.count(3) > 0) {
    std::cout << "Key 3 exists." << std::endl;
}
```

`count()` 返回键对应的元素数目，对于 `unordered_map` 来说，通常是 0 或 1。

### `unordered_map` 的修改操作

`unordered_map` 支持以下修改操作：

#### **1. `insert()`**

```cpp
myMap.insert({4, "Elderberry"}); // 插入一个键值对
```

#### **2. `erase()`**

```cpp
myMap.erase(1); // 删除键为 1 的元素
```

#### **3. `clear()`**

```cpp
myMap.clear(); // 清空所有元素
```

### `unordered_map` 的桶操作

`unordered_map` 内部使用桶（bucket）来组织数据。以下是一些桶操作：

#### **1. `bucket_count()`**

```cpp
std::cout << "Number of buckets: " << myMap.bucket_count() << std::endl;
```

  **bucket_count**：返回哈希表中桶的数量。

#### **2. `bucket_size()`**

```cpp
std::cout << "Bucket 0 size: " << myMap.bucket_size(0) << std::endl;
```

 **bucket_size**：返回第 `n` 个桶中的元素数目。

#### **3. `bucket()`**

```cpp
std::cout << "Key 2 is in bucket: " << myMap.bucket(2) << std::endl;
```

**bucket**：返回键对应桶的索引。

## `unordered_set` 的介绍

`unordered_set` 是 C++ 标准库中的一个容器，它存储唯一的元素，不保存任何顺序。与 `set` 不同，`unordered_set` 内部使用哈希表结构，因此在查询、插入和删除操作时具有更快的平均时间复杂度，通常为 O(1)。

## 1.1 `unordered_set` 的用途

当你需要存储一组不重复的元素，并且希望快速判断某个元素是否存在时`unordered_set` 是一个理想的选择。例如，在处理大量数据时快速过滤重复元素。

## 1.2 `unordered_set` 的构造

`unordered_set` 提供了多种构造方法：

### **1. 默认构造**

```cpp
unordered_set<int> mySet;
```

这会创建一个空的 `unordered_set`，键的类型为 `int`。

### **2. 使用初始化列表构造**

```cpp
unordered_set<int> mySet = {1, 2, 3, 4, 5};
```

通过初始化列表直接填充 `unordered_set`。

### **3. 通过范围构造**

```cpp
std::vector<int> vec = {10, 20, 30, 40, 50};
unordered_set<int> mySet(vec.begin(), vec.end());
```

## 1.3 `unordered_set` 的容量

`unordered_set` 提供了以下函数来查询其容量：

### **1. `empty()`**

```cpp
if (mySet.empty()) {
    std::cout << "The set is empty." << std::endl;
}
```

检查 `unordered_set` 是否为空。

### **2. `size()`**

```cpp
std::cout << "The size is: " << mySet.size() << std::endl;
```

返回 `unordered_set` 中元素的数量。

## 1.4 `unordered_set` 的迭代器

`unordered_set` 的迭代器支持以下操作：

### **1. `begin()` 和 `end()`**

```cpp
for (auto it = mySet.begin(); it != mySet.end(); ++it) {
    std::cout << *it << " ";
}
```

`begin()` 返回指向第一个元素的迭代器，`end()` 返回指向最后一个元素之后位置的迭代器。

### **2. `cbegin()` 和 `cend()`**

```cpp
for (auto it = mySet.cbegin(); it != mySet.cend(); ++it) {
    std::cout << *it << " ";
}
```

返回常量迭代器，用于只读访问。

## 1.5 `unordered_set` 的元素访问

`unordered_set` 提供了以下几种查询元素的方式：

### **1. `find()`**

```cpp
auto it = mySet.find(3);
if (it != mySet.end()) {
    std::cout << "Found: " << *it << std::endl;
}
```

`find()` 返回一个迭代器，指向键对应的元素，如果找不到则返回 `end()`。

### **2. `count()`**

```cpp
if (mySet.count(5) > 0) {
    std::cout << "Key 5 exists." << std::endl;
}
```

`count()` 返回键对应的元素数目，对于 `unordered_set` 来说，通常是 0 或 1。

## 1.6 `unordered_set` 的修改操作

`unordered_set` 支持以下修改操作：

### **1. `insert()`**

```cpp
mySet.insert(6); // 插入单个元素
mySet.insert({7, 8, 9}); // 插入多个元素
```

### **2. `erase()`**

```cpp
mySet.erase(2); // 删除单个元素
```

### **3. `clear()`**

```cpp
mySet.clear(); // 清空所有元素
```

## 1.7 `unordered_set` 的桶操作

`unordered_set` 内部使用桶（bucket）来组织数据。以下是一些桶操作：

### **1. `bucket_count()`**

```cpp
std::cout << "Number of buckets: " << mySet.bucket_count() << std::endl;
```

### **2. `bucket_size()`**

```cpp
std::cout << "Bucket 0 size: " << mySet.bucket_size(0) << std::endl;
```

### **3. `bucket()`**

```cpp
std::cout << "Key 2 is in bucket: " << mySet.bucket(2) << std::endl;
```
