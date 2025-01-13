
// 定义红黑数的颜色
enum Colour
{
    RED,
    BLACK
};

template <class K, class V>
struct RBTreeNode
{
    RBTreeNode<K, V> *_left;
    RBTreeNode<K, V> *_right;
    RBTreeNode<K, V> *_parent;
    pair<K, V> _kv;
    Colour _col;
    RBTreeNode(const pair<K, V> &kv)
        : _left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv), _col(RED)
    {
    }
};

template <class K, class V>
class RBTree
{
    typedef RBTreeNode<K, V> Node;

public:
    bool Inster(const pair<K, V> &kv)
    {
        if (_root == nullptr)
        {
            _root = new Node(kv);
            _root->_col = BLACK; // 如果是空的，那我们要插入一个节点，这个节点的颜色是黑色，因为性质2，跟节点的颜色是黑色的。
            return true;
        }

        Node *parent = nullptr;
        Node *cur = _root;

        while (cur)
        {
            if (cur->_kv.first < kv.first)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if (cur->_kv.first > kv.first)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                return false;
            }
        }

        cur = new Node(kv);
        if (parent->_kv.first < kv.first)
        {
            parent->_kv.first < kv.first;
            cur->_parent = parent;
        }
        else if
        {
            parent->_left = cur;
            cur->parent = parent;
        }

        return true;
    }

private:
    Node *_root = nullptr;
};