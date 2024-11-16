#include <assert.h>
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
                if (cur->_kv.first < kv.first) // 如果要插入的值 key 大于当前节点值的值，我们往右子树走
                {
                    parent = cur;
                    cur = cur->_right;
                }
                else if (cur->_kv.first > kv.first) // 如果要插入的值 key 小于当前节点值 我们就往左子树走
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
                else if (parent->_bf == 2 || parent->_bf == -2)
                // 走到这里说明平衡因子 _bf!= 0 || _bf != 1 ||  _bf != -1, 出问题了,需要旋转治疗一下了。
                {
                    // 旋转
                    // 插入的结点如果是 RR 型
                    if (parent->_bf == 2 && cur->_bf == 1)
                    {
                        RotateL(parent);
                    }
                    // 插入的结点如果是 LL 型
                    else if (parent->_bf == -2 && cur->_bf == -1)
                    {
                        RotateR(parent);
                    }

                    // 插入的节点如果是 RL 型 --- 各个击破
                    else if (parent->_bf == 2 && cur->_bf == -1)
                    {
                        Rotate_RL(parent); // 这个函数是用来先向右旋转，再向左旋转的
                    }
                    // 插入的节点是 LR 型
                    else if (parent_bf == -2 && cur->_bf = 1)
                    {
                        Rotate_LR(parent);
                    }

                    // 旋转完成了，我们就可以退出了
                    break;
                }
                else
                {
                    assert(false); // 断言,走到这一步说明之前的代码肯定是有问题的，说明插入之前就不是平衡的，所以我们在这里断言，如果代码走到这一步，我们就要好好检查一下我们之前的代码
                }
            }

            return true;
        }
    }

    void RotateL(Node *parent) // 左单旋转代码,新插入的结点是 RR 型
    {
        Node *subR = parent->_right;
        Node *subRL = subR->_left;
        Node *parentParent = parent->_parent; // 把它的父节点先记录下来
        // 开始旋转,看着图来理解下面的代码，或者自己画一下图
        parent->_right = subRL;
        subR->_left = parent;
        // 处理parent
        parent->_parent = subR;
        if (subRL) // subRL 不是空指针才行
        {
            subRL->_parent = parent;
        }

        // 处理根
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
            else if (parentParent->_right == parent)
            {
                parentParent->_right = subR;
            }
            subR->_parent = parentParent;
        }
        parent->_bf = subRL->_bf = 0; // 更新平衡因子
    }

    // 右旋代码，插入的节点是LL型，即：右子树的右结点
    void RotateR(Node *parent)
    {
        // 先把我们要用的节点给定义出来
        Node *subL = parent->_left;
        Node *subLR = subL->_right;
        Node *parentParent = parent->_parent;

        // 然后开始右旋
        parent->_left = subLR; // 先把结点 9 链接到结点 14 的左边，让节点 9 把位置给空出来
        subL->_right = parent; // 然后就可以把结点 14 放入空的那个位置了

        // 接下来我们同左旋一样，我们仍然要解决 2 个大问题：1. 根的问题（更新根） 2.parent 节点的问题
        // 1. 根的问题
        if (_root == parent) // 如果这个 parent 就是这整棵树的根了
        {
            _root = subL;
            subL->_parent = nullptr;
        }
        else // 如果这个 parent 只是一个局部
        {
            // 如果它是一个局部的话，我们又要分两种情况来考虑：1.它是左子树 2. 它是右子树
            subL->_parent = parentParent;
            // 1. 他是左子树
            if (parentParent->_left == parent)
            {
                parentParent->_left = subL;
            }
            // 2. 它是右子树
            else if (parentParent->_right == parent)
            {
                parentParent->_right = subL;
            }
        }
        // 2. 解决 parent 节点的问题,更新节点之前的父子关系
        parent->_parent = subL;
        if (subLR) // subRL 这个节点可能为空，所以我们要排除一下这种情况
            subLR->_parent = parent;

        // 最后更新平衡因子
        subL->_bf = parent->_bf = 0;
    }

    // 右左双旋函数
    void Rotate_RL(Node *parent)
    {
        Node *subR = parent->_right;
        Node *subRL = subR->_left;
        // 由于接下来会有单旋的操作，会改变我们的平衡因子，所以我们需要记录一下
        int bf = subRL->_bf;

        RotateR(parent->_right);
        RotateL(parent);

        if (bf == 0)
        {
            // subRL 本身就是被插入的那个节点
            parent->_bf = subR->_bf = subRL->_bf = 0;
        }
        else if (bf == 1) // 新插入的节点在 subRL 的右子树
        {
            parent->_bf = -1; // 为啥事-1？ 画图可以帮助你的理解
            subR->_bf = subRL = 0;
        }
        else if (bf == -1) // 新插入的节点在 subRL 的左子树
        {
            parent->_bf = 0;
            subR->_bf = 1;
            subRL->_bf = 0;
        }
        else
        {
            assert(false); // 只能是上面的 3 种情况，如果走到了这里就说明出问题了。
        }
    }

    void Rotate_LR(Node* parent)
    {
        // ......
        Node *subL = parent->_left;
        Node *subLR = subL->_right;

        RotateL(parent->_left);
        RotateR(parent);

        int bf = subLR->_bf;

        if (bf == 0)
        {
            // subRL 本身就是被插入的那个节点
            parent->_bf = subL->_bf = subLR->_bf = 0;
        }
        else if (bf == -1) // 新插入的节点在 subRL 的右子树
        {
            parent->_bf = -1; // 为啥事-1？ 画图可以帮助你的理解
            subL->_bf = subLR = 0;
        }
        else if (bf == 1) // 新插入的节点在 subRL 的左子树
        {
            parent->_bf = 0;
            subL->_bf = 1;
            subLR->_bf = 0;
        }
        else
        {
            assert(false); // 只能是上面的 3 种情况，如果走到了这里就说明出问题了。
        }
    }

private:
    Node *_root = nullptr; // 定义根节点
};

// 提交说明
