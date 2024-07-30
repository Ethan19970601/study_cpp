

#include <iostream>
using namespace std;

template <class K>
// 定义二叉搜索树的节点
struct BSTreeNode
{
    BSTreeNode<K> *_left;
    BSTreeNode<K> *_right;
    K _key;

    BSTreeNode(const K &key) : _left(nullptr), _right(nullptr), _key(key) {}
};

template <class K>
class BSTree
{
    typedef BSTreeNode<K> Node;

public:
    bool Insert(const K &key)
    {
        if (_root == nullptr)
        { // 如果是空，那么我们就创建一个节点
            _root = new Node(key);
            return true;
        }
        else
        {                           // 如果不是空，那我们就要找到插入的位置
            Node *parent = nullptr; // 为了在找到要插入的位置之后，将待插入的节点与整个二叉树链接起来，所以我们要设置一个父节点
            Node *cur = _root;
            while (cur)
            {                 // 循环的终止条件是：当插入到空的时候就截止了
                parent = cur; // 每次 cur 的值更新之前也不要忘了更新 parent 的值。
                if (cur->_key < key)
                { // 如果插入的值大于该节点的值我们要往右走。
                    cur = cur->_right;
                }
                else if (cur->_key > key)
                { // 如果插入的值小于该节点的值我们就往左走
                    cur = cur->_left;
                }
                else
                {
                    return false; // 默认情况下搜索二叉树是不允许有值相等的
                }
            }
            cur = new Node(key); // 创建一个节点出来
            if (parent->_key < key)
            {
                parent->_right = cur; // 我们要区分一下，把这个新的节点链接到左边还是右边?
            }
            else
            {
                parent->_left = cur;
            }
            return true;
        }
    }

    // 查找
    bool Find(const K &key)
    {
        Node *cur = _root;
        while (cur)
        {
            if (cur->_key < key)
            {
                cur = cur->_right;
            }
            else if (cur->_key > key)
            {
                cur = cur->_left;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    // 删除节点—— 替换法
    bool Erase(const K &key)
    {
        Node *parent = nullptr;
        Node *cur = _root;
        while (cur)
        {
            if (cur->_key < key)
            { // 要删除的值比当前节点的值要大，说明我们要往这个节点的右子树去找
                parent = cur;
                cur = cur->_right;
            }
            else if (cur->_key > key) // 要删除的值比当前节点的值要小，所以我们要往左子树去找
            {
                parent = cur;
                cur = cur->_left;
            }
            else // 相等的话我们就找到了，就可以进行删除的操作了
            {
                /*****************************************左孩子是空的情况******************************/
                if (cur->_left == nullptr) // 如果 cur 只有一个孩子，它的左孩子是空
                {
                    if (cur == _root) // 不要忘了考虑 cur 是根节点的情况
                    {
                        _root = cur->_right; // 因为大前提是左孩子是空，所以你不可能把左孩子用来当成根节点吧
                    }
                    if (cur == parent->_left) // 恰好，cur 又是父节点的左孩子
                    {
                        parent->_left = cur->_right; // 满足搜索二叉树的性质：左边的数要小，右边的数要大）
                    }
                    else if (cur == parent->_right)
                    {
                        parent->_right = cur->_right;
                    }
                }
                /**************************************右孩子是空的情况*************************** */
                else if (cur->_right == nullptr) // 如果 cur 这个节点的右孩子是空的
                {
                    if (cur == _root)
                    {
                        _root = cur->_left;
                    }
                    if (cur == parent->_left) // 恰好，cur 又是父节点的左孩子
                    {
                        parent->_left = cur->_left; // 满足搜索二叉树的性质：左边的数要小，右边的数要大）
                    }
                    else if (cur == parent->_right)
                    {
                        parent->_right = cur->_left;
                    }
                }
                /**********************************左右孩子都不是空的情况************************ */
                else if (cur->_left != nullptr && cur->_right != nullptr)
                {
                    // 这个时候，我们就要用替换法了，左树的最大节点，右树的最小节点都可以
                    // 那我们这里默认找右树的最小节点来替代
                    Node *subLeft = cur->_right; // subLeft 表示的是右树的最小节点,通过观察我们可以知道右树的最小节点在最左边，同理，左树的最大结点在最右边，所以我们这里找右树的最小的节点取名为：subLeft
                    Node *parent = cur;
                    while (subLeft->_left) // 如果 subLeft->left 不是空，说明它还不是最小的那个节点，我们呢就要继续往左找
                    {
                        parent = subLeft;
                        subLeft = subLeft->_left;
                    }
                    // 通过上面的代码， subLeft 已经到了右子树最小节点的那个位置了，现在我们可以开始替换操作了
                    swap(cur->_key, subLeft->_key); // subLeft 是我们要找的那个值，我把它用来替换要删除的值 cur
                                                    // subLeft现在成为了我们要删除的那个节点，因为我们上面进行了替换的操作，现在我们要把 subLeft的孩子节点处理好，让他们连接上新的父节点
                    if (subLeft == parent->_left)   // 如果 subLeft 是parent的左子树，那么它的孩子的值都是小于parent的
                    {
                        parent->_left = subLeft->_right; // 自己画图会好理解一点
                    }
                    else // 如果 subLeft 是一个右子树，那么我们知道它的孩子的值都是大于parent的
                    {
                        parent->_right = subLeft->_right;
                    }
                }
                return true;
            }
        }
        return false; // 找不到就返回错
    }

    // 中序遍历
    void _InOrder(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }
        else
        {
            _InOrder(root->_left);
            cout << root->_key << " ";
            _InOrder(root->_right);
        }
    }

    // 但是我们这个中序遍历是成员函数，它的参数 root 也是成员变量，我们在类外面无法访问这个成员变量，那怎么办呢？
    // 我可以写个：getRoot() 的 成员函数来返回一个 root, 但是下面的处理办法也同样巧妙
    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }

    bool EraseR(const K &key)
    {
        return _EraseR(_root, key);
    }
    bool FindR(const K &key)
    {
        return _FindR(_root, key);
    }

    bool InsertR(const K &key)
    {
        return _InsertR(_root, key);
    }

    // 默认构造函数-----由于我们下面写了构造函数（拷贝构造函数），所以编译器就不会自动生成默认构造函数了
    // 所以我们这里要写一个默认构造函数了，但是我们的成员变量已经给了缺省值，所以我可以直接这样写：
    BSTree() {} // 它会用缺省值去初始化

    // 或者也可以这样写：
    //  BSTree() = default; // 代表强制生成默认构造函数

    // 析构函数
    ~BSTree()
    {
        Destroy(_root);
    }

    // 拷贝构造函数
    BSTree(const BSTree<K> &t)
    {
        _root = Copy(t._root);
    }

    // 赋值,重载运算符，=
    BSTree<K> &operator=(BSTree<K> t)
    {
        swap(_root, t._root);
        return *this;
    }

private:
    // 拷贝构造函数
    Node *Copy(Node *root)
    {
        if (root == nullptr)
            return nullptr;
        Node *newRoot = new Node(root->_key);
        newRoot->_left = Copy(root->_left);
        newRoot->_right = Copy(root->_right);
        return newRoot;
    }
    // 析构函数
    void Destroy(Node *&root)
    {
        if (root == nullptr)
            return;

        Destroy(root->_left);
        Destroy(root->_right);
        delete root;
        root = nullptr;
    }

    // 递归的删除函数的写法 Erase
    bool _EraseR(Node *&root, const K &key)
    {
        if (root == nullptr)
        {
            return false;
        }
        else if (root->_key > key)
        {
            return _EraseR(root->_left, key);
        }
        else if (root->_key < key)
        {
            return _EraseR(root->_right, key);
        }
        else if (root->_key == key)
        {
            // 这里就要进行删除操作了，同时我们要注意有很多种情况需要我们去解决
            /*****************        左孩子为空的情况        ****************************** */
            if (root->_left == nullptr)
            {
                Node *del = root;
                root = root->_right;
                delete del;
                return true;
            }
            /********************      右孩子为空        ***************************88 */
            else if (root->_right == nullptr)
            {

                Node *del = root;
                root = root->_left;
                delete del;
                return true;
            }
            /********************      左右孩子都不为空       ************************* */
            else
            {
                // 这里用替代法；
                Node *subLeft = root->_right; // 同上，subLeft 是我们要去寻找的替代者,为什么要让它指向 root->right? 因为我们之前说过，替代者是左子树的最大结点或者是右子树的最小结点都行，所以我们这里找的是右子树的最小结点
                while (subLeft->_left)        // 只要它还有左子树，就说明还不是最小的那个结点，所以我们要继续找
                {
                    subLeft = subLeft->_left;
                }
                swap(root->_key, subLeft->_key);   // 交换要删除的节点和替代者
                return _EraseR(root->_right, key); // 用递归的方式来删除，我们去子树中删除。
            }
        }
    }
    // 递归的插入函数的写法：
    bool _InsertR(Node *&root, const K &key) // 这里的处理相当的巧妙，我指的是：Node *&root,
    {                                        // 你会感到疑问，为什么我们这里要加个 &，我来告诉你加 & 目的
                                             // 加了 & 之后，就直接把我们要插入的节点链接到树上了，我们不是要插入一个新的节点吗
                                             // 为了插入这个新的节点我们的思路是： 1. 找到节点要插入的位置 2. 将节点插入进去（要和它的父节点链接起来）
                                             // 这里使用了 & （即：引用，取别名）, 在它找节点的过程中，它对应的父节点通过&的方式有了一个新的名字：root
                                             // 然后在递归遍历的时候，我们是这样的：root->left,root->right,如果 root 恰好是空，我们就 new 一个新的结点
        if (root == nullptr)                 // 这样刚好就链接上了，自己动手画递归展开图更易理解

        {
            root = new Node(key);
            return true;
        }
        if (root->_key < key)
        {
            return _InsertR(root->_right, key);
        }
        else if (root->_key > key)
        {
            return _InsertR(root->_left, key);
        }
        else
        {
            return false;
        }
    }
    // 递归的查找函数的方法
    bool _FindR(Node *root, const K &key)
    {
        if (root == nullptr)
        {
            return false;
        }
        else
        {
            if (root->_key == key)
            {
                return true;
            }
            else if (root->_key > key)
            {
                return _FindR(_root->_left, key);
            }
            else if (root->_key < key)
            {
                return _FindR(_root->_right);
            }
        }
    }
    // 中序遍历
    // void _InOrder(Node *root)
    //{
    // if (root == nullptr)
    //{
    // return;
    //}
    // else
    //{
    //_InOrder(root->_left);
    // cout << root->_key << " ";
    //_InOrder(root->_right);
    //}
    //}

private:
    Node *_root = nullptr;
};

// int main()
//{
//     int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};
//     BSTree<int> bt; // 定义一个二叉搜索树
//     for (auto e : a)
//     {
//         bt.InsertR(e); // 使用插入操作
//     }
//     bt.InOrder();
//     bt.EraseR(14);
//     bt.InOrder();
//
//     bt.EraseR(8);
//     bt.InOrder();
//
//     bt.EraseR(3);
//     bt.InOrder();
//
//     for (auto e : a)
//     {
//
//         bt.EraseR(e);
//         bt.InOrder();
//     }
//     return 0;
// }

int main()
{
    int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};
    BSTree<int> bt; // 定义一个二叉搜索树
    for (auto e : a)
    {
        bt.InsertR(e); // 使用插入操作
    }
    bt.InOrder();
    BSTree<int> copy(bt);
    copy.InOrder();
}
