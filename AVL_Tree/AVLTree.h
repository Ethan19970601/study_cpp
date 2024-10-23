
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
    bool Insert(const pair<K, V> &kv)
    {
        if (_root == nullptr)
        {
            _root = new Node(kv);
            return true;
        }
        else
        {
            Node *parent = nullptr;
            Node *cur = _root;
            while (cur)
            {
                if (cur->_kv.first < key) // 如果要插入的值 key 大于当前节点值的值，我们往右子树走
                {
                    parent = cur;
                    cur = cur->_right;
                }
                else if (cur->_kv.first > key) // 如果要插入的值 key 小于当前节点值 我们就往左子树走
                {
                    parent = cur;
                    cur = cur->_left;
                }
                else // 如果相等就不让插入
                {
                    return false;
                }
            }
            // 当我们把 while 循环走完之后，我们就走到了要插入的地方了
            cur = new Node(kv); // new 一个节点出来
            if (parent->_kv.first < key)
            {
                parent->_right = cur;
                cur->_parent = parent;
            }
            else
            {
                parent->_left = cur;
                cur->_parent = parent;
            }

            return ture;
        }
    }

private:
    Node *_root = nullptr; // 定义根节点
};
