// 用一个枚举类型 给哈希表的每个空间给个标记

// EMPTY 表示此位置为空
// EXIST 表示此位置已经有元素了
// DELETE 表示元素已经删除

enmu State{
    EMPTY,
    EXIST,
    DELETE};

// 注意：假如实现的哈希表中元素唯一，即key相同的元素不再进行插入
// 为了实现简单，此哈希表中我们将比较直接与元素绑定在一起
template <class K, class V>
class HashTable
{
    struct Elem
    {
        pair<K, V> _val;
        State _state;
    };

public:
    HashTable(size_t capacity = 3) : _ht(capacity), _size(0)
    {
        for (size_t i = 0; i < capacity; ++i)
            _ht[i]._state = EMPTY;
    }
    bool Insert(const pair<K, V> &val)
    {
        // 检测哈希表底层空间是否充足
        // _CheckCapacity();
        size_t hashAddr = HashFunc(key);
        // size_t startAddr = hashAddr;
        while (_ht[hashAddr]._state != EMPTY)
        {
            if (_ht[hashAddr]._state == EXIST && _ht[hashAddr]._val.first == key)
                return false;
            hashAddr++;
            if (hashAddr == _ht.capacity())
                hashAddr = 0;
            /* // 转一圈也没有找到，
            注意：动态哈希表，该种情况可以不用考虑，哈希表中元素个数到达一定的数量，哈希冲突概率会增大，需要扩容来降低哈希冲突，因此哈希表中元素是 不会存满的
            if(hashAddr == startAddr)
            return false;
            */
        }
        // 插入元素
        _ht[hashAddr]._state = EXIST;
        _ht[hashAddr]._val = val;
        _size++;
        return true;
    }
    int Find(const K &key)
    {
        size_t hashAddr = HashFunc(key);
        while (_ht[hashAddr]._state != EMPTY)
        {
            if (_ht[hashAddr]._state == EXIST && _ht[hashAddr]._val.first == key)
                return hashAddr;
            hashAddr++;
        }
        return hashAddr;
    }
    bool Erase(const K &key)
    {
        int index = Find(key);
        if (-1 != index)
        {
            _ht[index]._state = DELETE;
            _size++;
            return true;
        }
        return false;
    }

    size_t Size() const;
    bool Empty() const;
    void Swap(HashTable<K, V, HF> &ht);

private:
    size_t HashFunc(const K &key) { return key % _ht.capacity(); }

private:
    vector<Elem> _ht;
    size_t _size;
};
