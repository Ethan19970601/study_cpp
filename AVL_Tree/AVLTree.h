#include <assert.h>

template <class K, class V>
struct AVLTreeNode
{
    AVLTreeNode<K, V> *_left;
    AVLTreeNode<K, V> *_right;
    AVLTreeNode<K, V> *_parent;
    pair<K, V> _kv;

    int _bf; // balance factor

    AVLTreeNode(const pair<K, V> &kv)
        : _left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv), _bf(0)
    {
    }
};

template <class K, class V>
class AVLTree
{
    typedef AVLTreeNode<K, V> Node;

public:
    bool Insert(const pair<K, V> &kv)
    {
        if (_root == nullptr)
        {
            _root = new Node(kv);
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
            parent->_right = cur;
            cur->_parent = parent;
        }
        else
        {
            parent->_left = cur;
            cur->_parent = parent;
        }

        while (parent)
        {
            if (cur == parent->_left)
            {
                parent->_bf--;
            }
            else
            {
                parent->_bf++;
            }

            if (parent->_bf == 0)
            {
                break;
            }
            else if (parent->_bf == 1 || parent->_bf == -1)
            {
                cur = parent;
                parent = parent->_parent;
            }
            else if (parent->_bf == 2 || parent->_bf == -2)
            {
                if (parent->_bf == 2 && cur->_bf == 1)
                {
                    RotateL(parent);
                }
                else if (parent->_bf == -2 && cur->_bf == -1)
                {
                    RotateR(parent);
                }
                else if (parent->_bf == 2 && cur->_bf == -1)
                {
                    RotateRL(parent);
                }
                else if (parent->_bf == -2 && cur->_bf == 1)
                {
                    RotateLR(parent);
                }

                // 1、旋转让这颗子树平衡了
                // 2、旋转降低了这颗子树的高度，恢复到跟插入前一样的高度，所以对上一层没有影响，不用继续更新
                break;
            }
            else
            {
                assert(false);
            }
        }

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
        //...
        RotateL(parent->_left);
        RotateR(parent);
    }

    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }

    void _InOrder(Node *root)
    {
        if (root == nullptr)
            return;

        _InOrder(root->_left);
        cout << root->_kv.first << " ";
        _InOrder(root->_right);
    }

    bool IsBalance()
    {
        return _IsBalance(_root);
    }

    int _Height(Node *root)
    {
        // 如果是空树，那么它的高度是 0
        if (root == nullptr)
            return 0;
        // 分别求左右子树的高度
        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
        // 这棵树自己的高度 = 左右子树高的那个 + 1
        return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
    }

    bool _IsBalance(Node *root)
    {
        // 首先，空树🌲是 avl 树
        if (root == nullptr)
            return true;
        // 计算左右子树的高度
        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
        if (leftHeight - rightHeight != root->_bf)
        {
            cout << root->_kv.first << "平衡因子异常" << endl;
            return false;
        }
        // 计算左右的高度差 ，abs 是求绝对值的
        return abs(leftHeight - rightHeight) < 2 && _IsBalance(root->_left) && _IsBalance(root->_right);
    }

private:
    Node *_root = nullptr;
};
