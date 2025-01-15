# 红黑树的概念

红黑树，是一种`二叉搜索树`，但在每个结点上增加一个存储位表示结点的颜色，可以是`Red`或
`Black`。 通过对任何一条从根到叶子的路径上各个结点着色方式的限制，红黑树确保没有一条路径会比其他路径长出俩倍，因而是接近平衡的。

![image.png](https://obsidian-01-1330327465.cos.ap-chengdu.myqcloud.com/202501111441171.png)

>  对比一下：
>  AVLTree ，是严格平衡，左右的高度差 不超过 1
>  红黑树，是近似平衡，最长路径不会超过最短路径的 2倍

# 红黑树的性质

1. 每个结点不是红色就是黑色
2. 根节点是黑色的 
3. 如果一个节点是红色的，则它的两个孩子结点是黑色的 
> 就是说，如果父节点是红色的，他的两个孩子也必须是红色的，不能出现连续的红色节点，即：父子节点的颜色只有这几种可能：父（黑) + 子（黑），父（黑）+ 子（红）,父（红）+ 子（黑），
4. 对于每个结点，从该结点到其所有后代叶子结点的简单路径上，均包含相同数目的黑色结点 
> 意思就是每条路径上都有相同数量的黑色节点
5. 每个叶子结点都是黑色的(此处的叶子结点指的是空结点)
> 这里的叶子节点不是指的传统意义上的叶子节点，而是指的空结点,也称NIL结点，这个NIL 节点的作用是方便我们数路劲，就是数这棵树有几条路径，比如下面的例子：
> ![image.png](https://obsidian-01-1330327465.cos.ap-chengdu.myqcloud.com/20250113110657591.png)



思考：为什么满足上
我们来分析一下，什k面的性质，红黑树就能保证：其最长路径中节点个数不会超过最短路径节点个数的两倍？ 🔎

我们来分析一下，什么情况下，路径是最短的？

根据性质4`每条路径上都包含相同数目的黑色节点` , 那就说明如果一条路径上只有黑色节点，没有红色节点的话，更其他那些有红色节点的路劲相比，它就是最短的。
所以：

**路劲最短** ： 只有黑色节点的情况

我们再来分析一下，什么情况下，路径是最长的呢？

在相同黑色节点的条件下，红色节点的个数越多，路劲就越长，根据性质3，要尽可能的增加红色节点的个数的的话，它们之间的搭配条件要尽可能满足：父（黑）+ 子（红）+ 孙子（黑）+ 重孙子（红），这样的红黑红黑的交替的情况，所以最长的路径就是最短路径的2倍

**路径最长** ： 在黑色节点数目一定的情况下，红色节点的数目最多

综上所述，假设有N个黑色的节点，每条路径的的节点的个数的范围是`[N,2N]`


# 📌红黑树节点的定义
的定义：
```c++
enum Color{RED,BLACK};
// ekkkkk
kkkkk：
```c+num 是一个枚举类型，第一个RED是第一kkkkkk'k'k'k+
enum Color{RED,BLACKk'k'k'k;
// enum 是一个枚举类型，第一个RED是第一个枚举值，默认是 0、
// 第二个BLACK 是第二个枚举值，kkkkk
k'k'k'k
红黑树节点的定义：
```c++
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
```


🍉 上面的构造函数中，为什么默认节点的颜色要给成 红色呢？
> 1. 保持树的黑色高度不变。
> 	因为红黑数的性质4: 对于每个结点，从该结点到其所有后代叶子结点的简单路径上，均包含相同数目的黑色结点 
> 2. 减少插入时的调整操作：
> 	如果插入的是黑色节点，需要进行更多的调整操作来恢复红黑树的性质


# 📌红黑树的插入操作

```c++

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
		cur->_col = RED;
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
```


我们插入节点的的时候，如果插入的是一个红色的节点，但是这个新增节点的父亲是黑色的，那么插入结束，我们可以不做任何处理。

![image.png](https://obsidian-01-1330327465.cos.ap-chengdu.myqcloud.com/20250113224947456.png)
但是，如果我们插入一个红色的节点，但是他的父亲也是红色的，这个时候该怎么处理呢？

![image.png](https://obsidian-01-1330327465.cos.ap-chengdu.myqcloud.com/20250113225319722.png)
以上的这种情况是违反规则 3 的，所以，我们必然要做的一步就是：把新增节点的父亲变成**黑色** 节点，然后，我们在根据规则对其他节点颜色的颜色进行相应的调整以维护红树黑树的性质

![image.png](https://obsidian-01-1330327465.cos.ap-chengdu.myqcloud.com/20250113230214266.png)

这么看来红黑树的插入操作挺麻烦的呀，那为之奈何呀？
其实也有一定的规律在里面，下面我们细细的分析

**首先，我们新增一个节点，我们选择的是新增红色的节点，这样对整个树的影响会小一些** 

如果新增节点的父亲是黑色的，那我们不需要处理。
如果新增节点的父亲是红色的，那我们需要处理，处理的方式可能是：1. 旋转 2. 变色
有可能只变色就可以了，也有可能既要旋转又要变色。

### 第一种情况：

新增节点是红色的，新增节点的父亲也是红色的，祖父是黑色节点。并且叔叔存在而且叔叔也是红色的；

![image.png](https://obsidian-01-1330327465.cos.ap-chengdu.myqcloud.com/20250114172444994.png)

我们的解决办法是，
将父亲节点和叔叔节点变成红色，
祖父节点：
1. 如果祖父节点是这棵树的根节点，那就必须是黑色，所以保持颜色不变。
2. 如果祖父节点也只是这棵树的一个局部，那我们要把祖父节点变成红色的，这样才能保持这条路径中黑色节点的个数不变。

![image.png](https://obsidian-01-1330327465.cos.ap-chengdu.myqcloud.com/20250114172811735.png)
但是，这样我们忽略了一个问题：如果祖父节点的父亲（曾祖父）是红色的咋办？如下图：

![image.png](https://obsidian-01-1330327465.cos.ap-chengdu.myqcloud.com/20250114174018090.png)


遇到这种情况，首先，如果曾祖父是红色的，说明曾祖父不是根节点，因为根节点一定是黑色的，所以我们要往上走，把曾祖父当成当前节点，然后继续的看曾祖父的父节点和祖父节点，这样循环的往上处理。


### 第二种情况：

当前的节点是红色，父亲节点是红色，祖父节点是黑色，叔叔节点要么不存在，要么存在是黑色

cur : 表示当前节点
p   : parent 表示父亲节点
g   : grandpa 表示祖父节点
u   : uncle 表示叔叔节点

1. 当前节点是红色，父亲节点是红色，祖父节点是黑色，叔叔节点不存在：

![image.png](https://obsidian-01-1330327465.cos.ap-chengdu.myqcloud.com/20250115114517495.png)


![image.png](https://obsidian-01-1330327465.cos.ap-chengdu.myqcloud.com/20250115114811868.png)

2. 如果叔叔存在且为黑色：

![image.png](https://obsidian-01-1330327465.cos.ap-chengdu.myqcloud.com/20250115115107479.png)
