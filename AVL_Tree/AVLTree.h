
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

            // 更新平衡因子的值
            while ()
            {
                if (cur == parent->_left) // 插入的节点在左边
                {
                    parent->_bf--;
                }
                else if (cur == parent->_right) // 插入的结点在右边
                {
                    parent->_bf++;
                }
                if (parent->_bf == 0) // 如果父节点的平衡因子== 0，说明插入的结点刚好让左右子树的高度相等了，这种情况下，我们不需要继续向上更新了
                {
                    break; // 不需要更新，直接退出就行了
                }
                else if (parent->_bf == 1 || parent->_bf == -1) // 说明插入节点所在的子树高度变化了，要继续往上更新
                {
                    cur = parent;
                    parent = parent->_parent;
                }
                else // 走到这里说明平衡因子 _bf!= 0 || _bf != 1 ||  _bf != -1, 出问题了,需要旋转治疗一下了。
                {
                    // 旋转
                }
            }

            return ture;
        }
    }

private:
    Node *_root = nullptr; // 定义根节点
};
