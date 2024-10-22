
template <class K, class V>
struct AVLTreeNote
{
    AVLTreeNote<K, V> *_left;
    AVLTreeNote<K, V> *_right;
    AVLTreeNote<K, V> *_parent;
    pair<K, V> _kv;
    int _bf; // balance factor 平衡因子
};

template <class K, class V>
class AVLTree
{
    typedef AVLTreeNote<K, V> Node; // 这个写起来有点长，我们取个新的名字

public:
    // 插入：
    bool Insert(const K &key)
    {
        if (_root == nullptr)
        {
            _root = new Node(key);
            return true;
        }
    }

private:
    Node *_root = nullptr; // 定义根节点
};
