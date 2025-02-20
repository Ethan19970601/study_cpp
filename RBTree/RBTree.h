
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
        // 新增节点，我们默认给红色
        cur->_col = RED;
        if (parent->_kv.first < kv.first)
        {
            parent->_kv.first < kv.first;
            cur->_parent = parent;
        }
        else
        {
            parent->_left = cur;
            cur->_parent = parent;
        }

        while (parent && parent->_col == RED) // 如果新增节点的父亲是红色的
        {
            // 我们通过上面的分析得出的一个关键点就是，我们要看叔叔
            Node *grandfather = parent->_parent;
            if (parent == grandfather->_left)
            {
                Node *uncle = grandfather->_right; // 父亲是祖父的左孩子，那叔叔就是祖父的又孩子
                if (uncle && uncle->_col == RED)   // 走到这里，说明父亲和叔叔都是红色，那就满足我们的情况1了
                {
                    // 变色
                    parent->_col = uncle->_col = BLACK;
                    grandfather->_col = RED;

                    // 继续往上处理,所以我们要更新值
                    cur = grandfather;
                    parent = cur->_parent;
                }
                else // 情况2 叔叔不存在，或是叔叔存在且为黑色
                {
                    // 通过上面的if语句，走到这里的时候，说明 parent是 grandpa的左孩子，但是cur是那边的孩子我们还不确定，所以我们这里要判断一下
                    if (cur == parent->_left)
                    {
                        RotateR(grandfather);
                        parent->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    else // 这个是双旋转对应的情况
                    {
                        RotateL(parent);
                        RotateR(grandfather);
                        cur->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    break;
                }
            }
            else if (parent == grandfather->_right)
            {
                Node *uncle = grandfather->_left;
                if (uncle && uncle->_col == RED)
                {
                    // 变色
                    parent->_col = uncle->_col = BLACK;
                    grandfather->_col = RED;

                    // 继续往上处理
                    cur = grandfather;
                }
                else
                {
                    if (cur == parent->_right)
                    {
                        RotateL(grandfather);
                        parent->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    else if (cur == parent->_left)
                    {
                        RotateR(parent);
                        RotateL(grandfather);

                        cor->_col = BLACK;
                        parent->_col = RED;
                    }
                }
            }
        }

        _root->_col = BLACK; // 保证根节点是黑色的
        return true;
    }
    void RotateL(Node *parent)
    {
        Node *subR = parent->_right;
        Node *subRL = subR->_left;

        parent->_right = subRL;
        subR->_left = parent;

        Node *parentParent = parent->_parent;

        parent->_parent = subR;
        if (subRL)
            subRL->_parent = parent;

        if (_root == parent)
        {
            _root = subR;
            subR->_parent = nullptr;
        }
        else
        {
            if (parentParent->_left == parent)
            {
                parentParent->_left = subR;
            }
            else
            {
                parentParent->_right = subR;
            }

            subR->_parent = parentParent;
        }

        parent->_bf = subR->_bf = 0;
    }

    void RotateR(Node *parent)
    {
        Node *subL = parent->_left;
        Node *subLR = subL->_right;

        parent->_left = subLR;
        if (subLR)
            subLR->_parent = parent;

        Node *parentParent = parent->_parent;

        subL->_right = parent;
        parent->_parent = subL;

        if (_root == parent)
        {
            _root = subL;
            subL->_parent = nullptr;
        }
        else
        {
            if (parentParent->_left == parent)
            {
                parentParent->_left = subL;
            }
            else
            {
                parentParent->_right = subL;
            }

            subL->_parent = parentParent;
        }

        subL->_bf = parent->_bf = 0;
    }

    void RotateRL(Node *parent)
    {
        Node *subR = parent->_right;
        Node *subRL = subR->_left;
        int bf = subRL->_bf;

        RotateR(parent->_right);
        RotateL(parent);

        if (bf == 0)
        {
            // subRL自己就是新增
            parent->_bf = subR->_bf = subRL->_bf = 0;
        }
        else if (bf == -1)
        {
            // subRL的左子树新增
            parent->_bf = 0;
            subRL->_bf = 0;
            subR->_bf = 1;
        }
        else if (bf == 1)
        {
            // subRL的右子树新增
            parent->_bf = -1;
            subRL->_bf = 0;
            subR->_bf = 0;
        }
        else
        {
            assert(false);
        }
    }

    void RotateLR(Node *parent)
    {
        Node *subL = parent->_left;
        Node *subLR = subL->_right;
        int bf = subLR->_bf;
        RotateL(parent->_left);
        RotateR(parent);
        if (bf == 0)
        {
            subL->_bf = subLR->_bf = parent->_bf = 0;
        }
        else if (bf == 1)
        {
            subL->_bf = -1;
            subLR->_bf = 0;
            parent->_bf = 0;
        }
        else if (bf == -1)
        {
            subL->_bf = 0;
            subLR->_bf = 0;
            parent->_bf = 1;
        }
        else
        {
            assert(false);
        }
    }

    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }

    void _InOrder(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }
        _InOrder(root->_left);
        cout << root->_kv.first << " ";
        _InOrder(root->_right);
    }

    // balcknum 是根节点到当前节点的这条路劲上黑色节点的数量
    bool Check(Node *root, int balcknum)
    {
        if (root == nullptr)
        {
            cout << balcknum << endl;
            return true;
        }
        if (root->_col == RED && root->_parent->_col == RED)
        {
            cout << "有连续的红色节点" << endl;
            return false;
        }

        if (root->_col == BLACK)
        {
            ++balcknum;
        }

        return Check(root->_left, balcknum) && Check(root->_right, balcknum);
    }

    // 判断平衡
    bool IsBalance()
    {
        if (_root == nullptr) // 如果根是空，就return ture
            return ture;
        if (_root->_col == RED) // 如果根的颜色是红色，就说明是错的
            return false;

        int balcknum = 0;
        return Check(_root);
    }

private:
    Node *_root = nullptr;
};