
# 🏷️ AVL树的概念

AVL树是一种自平衡二叉搜索树，由苏联计算机科学家阿迪·加莫夫（Adelson-Velsky）和伊万·兰斯科伊（Landis）在1962年共同发明。AVL是他们姓氏的首字母缩写。

AVL树的主要特点是：

1. **二叉搜索树**：每个节点的左子树只包含小于该节点的键，右子树只包含大于该节点的键。

2. **自平衡**：通过在插入和删除操作后进行旋转操作来保持树的平衡。旋转操作包括左旋、右旋、左右旋和右左旋。

3. **平衡因子**：每个节点都有一个平衡因子，定义为左子树的高度减去右子树的高度。在AVL树中，任何节点的平衡因子只能是-1、0或1。

4. **旋转操作**：
   - **单旋转**：包括左旋（LL旋转）和右旋（RR旋转）。
   - **双旋转**：包括左右旋（LR旋转）和右左旋（RL旋转）。

5. **时间复杂度**：在AVL树中，插入、删除和查找操作的时间复杂度都是O(log n)，其中n是树中节点的数量。

6. **应用场景**：由于AVL树的高度平衡，它在需要频繁进行查找、插入和删除操作的应用中非常有用，例如数据库索引、字典实现等。

AVL树的自平衡特性确保了树的高度不会变得过大，从而避免了退化成链表的情况，这使得AVL树在处理大量数据时非常高效。

## 📌 搜索二叉树存在的问题

### ✏️ 搜查二叉树知识回顾

搜索二叉树，也称为二叉搜索树或二叉排序树，是一种特殊的二叉树，具有以下性质：

1. **二叉树**：它是一个二叉树，即每个节点最多有两个子节点，通常左子节点称为左孩子，右子节点称为右孩子。

2. **节点值**：每个节点都有一个键值（Key），且每个节点的键值是唯一的。

3. **排序性质**：对于树中的任意节点，其左子树中的所有节点的键值都小于该节点的键值，其右子树中的所有节点的键值都大于或等于该节点的键值。

4. **递归性质**：搜索二叉树的左子树和右子树也分别是一个搜索二叉树。

5. **平衡性**：在最理想的情况下，搜索二叉树是完全平衡的，即每个节点的左右子树的高度差为1，这样可以保证树的高度最小，从而使得查找、插入和删除操作的时间复杂度为O(log n)。但在最坏的情况下，如果树完全不平衡，退化成链表，那么这些操作的时间复杂度会退化到O(n)。

6. **操作**：搜索二叉树支持的主要操作包括查找、插入和删除节点。这些操作的时间复杂度依赖于树的高度。

7. **应用**：搜索二叉树常用于实现数据库索引、字典、符号表等数据结构，因为它们可以提供快速的查找、插入和删除操作。

### ✏️ 搜索二叉树的问题

#### ❓搜索二叉树的平衡问题

搜索二叉树,它允许我们快速地插入、查找和删除元素。但是，它的一个潜在问题就是可能会变得不平衡。这里的“不平衡”是指树的形状变得非常“瘦高”，就像一条链表一样。

#### ❓为什么会变成链表

想象一下，如果我们有一个空的搜索二叉树，然后我们开始插入一系列已经排序好的数字，比如1, 2, 3, 4, 5。在这种情况下，每次插入的数字都会比前一个数字大，所以它们都会被插入到当前节点的右子树中。这样，树的形状就会变成一条链表，每个节点都只有一个右孩子，没有左孩子。

#### 💡树的高度和操作时间复杂度

在理想的搜索二叉树中，树的高度应该是O(log n)，其中n是树中节点的数量。这是因为在平衡的树中，每个节点都有左右子树，所以查找任何节点都只需要遍历树的高度。但是，如果树变成了一条链表，那么树的高度就变成了n，因为我们需要遍历所有的节点才能找到目标节点。

- **查找操作**：在平衡的搜索二叉树中，查找一个节点的时间复杂度是O(log n)。但是，如果树变成了链表，查找一个节点的时间复杂度就变成了O(n)，因为我们需要遍历所有的节点。

- **插入操作**：在平衡的搜索二叉树中，插入一个新节点的时间复杂度也是O(log n)。但是，如果树变成了链表，插入一个新节点的时间复杂度就变成了O(n)，因为我们需要遍历所有的节点才能找到插入的位置。

- **删除操作**：在平衡的搜索二叉树中，删除一个节点的时间复杂度是O(log n)。但是，如果树变成了链表，删除一个节点的时间复杂度就变成了O(n)，因为我们需要遍历所有的节点才能找到要删除的节点。

#### 总结

所以，搜索二叉树的一个潜在问题就是它可能会变得不平衡，导致树的高度增加，从而使得查找、插入和删除操作的时间复杂度从理想的O(log n)退化到O(n)。

## 📌 AVL 树 ----- 为了解决搜索二叉树存在的问题

 二叉搜索树虽可以缩短查找的效率，但如果数据有序或接近有序二叉搜索树将退化为单支树，查找元素相当于在顺序表中搜索元素，效率低下。因此，两位俄罗斯的数学家G.M.Adelson-Velskii和E.M.Landis在1962年发明了一种解决上述问题的方法：当向二叉搜索树中插入新结点后，如果能保证每个结点的左右子树高度之差的绝对值不超过1(需要对树中的结点进行调整)，即可降低树的高度，从而减少平均搜索长度。AVL是他们姓氏的首字母缩写。

### ✏️ 特点

- 要求这棵树的左右高度差(简称平衡因子)不超过 1
 	- 是绝对值不超过 1 [[AVL树#❓ 为什么是不超过 1 呢？]]
- 这棵树的左子树和右子树也都要是 `AVL` 树

❓ 平衡因子是什么：

就是：`右子树的高度 - 左子树的高度`（也有说是左子树的高度 - 右子树的高度的，总之不影响我们使用它的目的）

[这个 up 的视频来了解 avl 树的旋转操作](https://www.bilibili.com/video/BV1tZ421q72h/?spm_id_from=333.337.search-card.all.click&vd_source=fc113385b66ad95c43b04f6e00442a98)

### ❓ 为什么是不超过 1 呢？

AVL 树 叫做高度平衡二叉搜索树，它是通过高度来平衡的，它要求左右子树的高度差不超过 1 ，那为什么是相等呢？ 因为有些数量下我们是做不到左右节点高度差相等的，但是我们可以做到高度差不超过 1

## 📌 实现 AVL 树

### ✏️ AVLTree.h

```c++

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
   // ***************************** 未完 *************
            return ture;
        }
    }

private:
    Node *_root = nullptr; // 定义根节点
};

```

### ✏️ 更新平衡因子的值

❓ 思考，如果我们插入了一个新的节点，那我们该如何来更新平衡因子？

- 父节点的平衡因子应该怎么更新
 如果我插入的是结点`cur` 是插入到父节点的左边的，那么根据平衡因子的公式：`右树高度-左树高度` 此时左树的高度由于我的插入而增加`1` 导致公式的结果会减少 `1`。所以这种情况下父节点的平衡因子应该`-1`
 
 同理：如果我插入的结点在右边，那么插入结点的父节点的平衡因子应该 `+1`
 
- 注意：新增一个结点可能会影响到的是此节点的祖先的平衡因子
 那如何判断这个新增节点会不会影响祖先节点的平衡因子呢？
  - 如果子树的高度变化，就会向上影响祖先的平衡因子
  - 如果子树的高度不变，就不会向上影响祖先的平衡因子
- 新插入的结点的平衡因子 = 0， 因为新插入的结点都是叶子结点
- 总结如下：
 	- 1. 父节点的`bf` (平衡因子）如果在插入结点后变成了 `0`，即：bf == 0，不用继续往上更新了，插入结束。
  		- 原因：插入之后变成 0 了，说明插入之前的 bf = -1 或者 bf = 1，插入的位置刚好把高度低的那棵树补平了，子树的高度没有反生变化所以不会影响到祖先结点
 	- 2. 父节点的平衡因子`bf`，如果在插入之后变成了 `-1, 1`，即 bf == -1 || bf == 1，则要继续往上更新。
  		- 原因：插入之后变成 -1 或者 1， 说明插入之前的 bf == 0 ，即：左右子树的高度是相等的，现在你插入了一个结点，让子树的高度发生了变化，所以会影响祖先结点的平衡因子，所以我们要继续往上更新
 	- 3. 父节点的平衡因子更新后变成了`-2 或者 2`，更加不行，这都违反了AVL树的规则，继续向上跟新

```c
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
```  

### ✏️  旋转

[这个 up 的视频来了解 avl 树的旋转操作](https://www.bilibili.com/video/BV1tZ421q72h/?spm_id_from=333.337.search-card.all.click&vd_source=fc113385b66ad95c43b04f6e00442a98)

### 🧲 旋转的目的

1. 让左右均衡一些
2. 保持搜索树的规则

### 🧲 旋转代码的实现

### 单方向旋转

#### 📎 插入的结点是 RR 型 - 右（R）子树的右（R）孩子

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/01c75403a1f6446abfb24c9be407b044.png)

##### ==**解决办法** ：左旋==

由图可知，失去平衡节点是节点 5 ，它的`_bf` 已经等于 2 了，不满足条件了，我们的解决办法是将 `结点 5` 向左旋转（逆时针旋转)，让`节点 5`转下来成为 `节点 9`的左孩子，这个时候由于`节点 9` 已经有了左孩子了，所以就冲突了，我们就把冲突的那个`节点 6` 变成`节点 5`的右孩子就可以了，看图：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/949a4839c15f4628a5372102fcc1a5d5.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/881f94a171184a5ba9cb0740ffd43e66.png)

为了便于代码编写，我们给以下节点取个名字：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0846337a71ae4884b5479352a44a2070.png)

按照上面👆🏻的思路我们可以写下如下的代码：

```c++
    void RotateL(Node *parent) // 左单旋转代码,新插入的结点是 RR 型
    {
        Node *subR = parent->_right;
        Node *subRL = subR->_left;

        // 开始旋转,看着图来理解下面的代码，或者自己画一下图
        parent->_right = subRL;
        subR->_left = parent;
    }

```

==但是这样的代码是有问题的：==

1. 根没有处理
2. `parent` 没有处理。（你看结节 6，就是那个`subRL`，它的`parent` 还是指向结点 9 的，但是旋转之后他的 parent 应该是指向结点 5 的）

所以我们要修改一下我们的代码，我们先来理一下各节点的关系：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/aeac2de93aec4cffbc907be54e909a0d.png)

###### ==处理`parent`:==

旋转之后我们发现节点之间的父子关系发生了变化
节点 5（parent）的父亲变成了 结点 9（subR）

```c++
parent->_parent = subR;
```

节点 6 （subRL）的父亲变成了节点 5 （parent）

```c++
subRL->_parent = parent; 
```

**💥 注意：这里还有一个容易被忽略的问题：节点 6 （subRL）可能是一个空节点**，如何来应对这种情况？
所以我们在把节点 6 的父节点变成节点 5 之前要先做一个判断：

```c++
if (subRL) // 只有节点 6 不为空才能这样。
{
 subRL->_parent = parent;
}
```

###### ==处理根：==

这个时候，subR(节点 9) 成为了这棵树的根节点，但是它的 父节点还是指向节点 5 的，我们要更新一下他的父节点，但是我们首先要弄明白一件事：那就是我们现在看到的这棵树，有可能就这么大了，节点 9 就是这整棵树的根，但是还有一种可能，我们看到的这棵树只是另一棵更大的树的一个局部，节点 9 的上面还有父结点。所以我们要综合的考虑这两种情况。

1. 情况 1 ，节点 9 就是这整棵树的根节点了

```c++
if (_root == parent)
{
 _root = subR; // 把 subR 更新为最新的根节点
 subR->parent = nullptr; // 由于 subR 是这棵树的根节点了，所以它的父节点是空
}
```

2. 情况 2，节点 9 的上面还有父节点,我们假设叫他父节点的父节点即：parentParent，我们在改变 parent这个节点的指向之前要提前把它的父节点给记录📝下来并存放到 parentParent 这个节点中：``Node* parentParent = parent->_parent;``
 这个时候又要分 2 种情况，我们只知道节点 9 上面还有节点，但是这个节点 9 是它父节点的左孩子还是右孩子呢？着我们不清楚，所以我们也要分情况讨论

```c++
else 
{
 // 此节点是其父节点的左孩子
 if (parentParent->_left == parent)
 {
  parentParent->_left = subR;
 }
 // 此节点是其父节点的右孩子
 else
 {
  parentParent->_right = subR;
 }
 // 最后不要忘了，把新的根节点的父节点给链接上去
 subR->_parent = parentParent;
}
```

本步骤完整代码展示：

```c

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
    }

```

###### ==最后一个步骤更新平衡因子==

到这一步的时候我们的左旋已经结束了，平衡因子也应该做适当的更新，我们可以观察图形：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/aeac2de93aec4cffbc907be54e909a0d.png)

通过图形我们可以知道，`subR` 和`parent` 的平衡因子都变成了 0 ，所以我们的代码如下：

```c
parent->_bf = subR->_bf = 0;
```

#### 📎 插入的结点是 LL 型 - 左（L）子树的左（L）孩子

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a272625d7fd343c7b28436a3ca36e867.png)

我们观察插入节点前后的变化：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/84afa1a06e124d93b796a5e3d54a7b0a.png)

##### ==解决办法：右旋==

观察图形我们可以知道，失去平衡的结点是**14** ，它的平衡因子由-1 变成了 -2，我们想到的办法是让 14 这个结点向右旋转（即：顺时针旋转），让 14 这个节点转下来，让 14 这个节点成为节点 6 的右孩子，但是节点 6 之前就已经有了右孩子 9，这个时候就冲突了，我们的做法是让节点 9 成为节点 14 的左孩子。如图：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a8a8540dcf474c96a79d503c50dcaee0.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7beaf8a9a1e44d2883a429c797399ba9.png)

同样的为了便于代码编写，我们可以给以下节点取名字：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2e037e579d9f48cfa609641b6e3ce785.png)

通过上面的思路我们可以编写出如下的代码：

```c++

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
        if (subRL) // subRL 这个节点可能为空，所以我们要排除一下这种情况
            subRL->_parent = parent;

        // 最后更新平衡因子
        subL->_bf = parent->_bf = 0;
    }

```

### 双旋

#### 📎 插入的结点是 RL 型 - 右（R）子树的左（L）孩子

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/35997dfa28d44051b568c38a0e106612.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/40e80ddeb93142328681822954d04b5d.png)

这个时候我们应当如何来恢复平衡呢？我们观察上面的图形发现：失去平衡的节点是 5 。因为我们插入的节点 8 是在节点 5 的右孩子的左子树上面。这种失衡的状态我们叫做：RL 型。
RL 型的特征就是：失衡节点的平衡因子是 -2 ，它的右节点的平衡因子是 -1 。
为了让它平衡，我们采取的方法是：==各个击破==。
你发现没，之前我们讲单方向旋转的时候，单方向旋转适用的场景是一种非常简单的情况：树的一边高另一边低，如果是左边高，我们就往右单旋。如果是右边高，我们就往左单旋。这样来使树保持平衡。
可是在这里，这种方法显然无法行通，因为此时的树🌲并不是单纯的一边高另一边就低了。而是子树的某一边高但是子树的子树却是另一边偏高，在这里就是：节点 5 的右子树 9偏高，但是节点9 的却是左子树偏高。
我们采取各个击破的方式，你的节点9 不是左边偏高吗？那我就先把你这个节点9 向右旋转来平衡了，把你这个 9 平衡之后，我们再来出来节点 5，你这个节点 5 不是右边偏高吗？那我就向左旋转来把你这个节点 5 给平衡了。
像这样经过 2 次旋转，我们最终就可以解决这个问题了。

我们来看看旋转之后的图片：

第一次旋转：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a2103bf7ef484ecf845761a6f79d7fbe.png)

第二次旋转：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a1369896d2f347d68673c52f11a6797f.png)

我们再来看看旋转前后平衡因子的变化：
情况 1：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/fa9920cdfe5348c4af6e176518217577.png)

情况 2：
你发现没，我们插入的节点 8 是插入到节点 6 的右子树，那如果我们新的节点是插入到节点 6 的左子树呢？情况会有什么不同吗？
其实，旋转的方法是一样的，无论你新插入的节点是在 6 的左子树还是右子树，都是各个击破，对 RL 来说都是先右旋小的那个部分 最后在左旋大的部分，只是最后由于你插入的位置不同会造成平衡因子的结果不同:

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0118dc161e5d447b95a6ffe1b34dbe7a.png)

情况 3：
其实还有最后一种情况，
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/70b78a556cab4b41a05ebfed4dcab2b4.png)

为了便于代码编写，我们可以给上面的节点命名：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/3a4f7ed215804fa9bc198f0b040b7836.png)

而且，我们可以通过 subRL 的平衡因子的值来区分我们上面说到的三种情况：

1. 如果 subRL 的平衡因子等于 1， 那么新插入的结点是插入在 subRL 的右子树的
2. 如果 subRL 的平衡因子等于 -1， 那么新插入的结点是插入在 subRL 的左子树的
3. 如果 subRL 的平衡因子等于 0， 那么新插入的结点就是 subRL 本身

根据上面的分析，我们来写代码：

```c++
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
```

我们现在来测试一下，当然，我们的代码还有一些地方没有写全 ，下面是补充了一些的代码，让程序可以运行起来，并不是最后的版本：
Test.cpp

```c++
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include "AVLTree.h"

int main()
{
    int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    AVLTree<int, int> t;
    for (auto e : a)
    {
        t.Insert(make_pair(e, e));
    }
    t.InOrder();
    return 0;
}
```

AVL.h

```c++
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

private:
    Node *_root = nullptr;
};

```

运行上面的代码，我们可以看到我们的树。

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/bdbad7d702f644f398b016b017c357b4.png)

我们的树是跑出来了，但是我们如何证明它是一颗平衡树呢？

### 判断是不是一颗平衡树？

我们可以通过写一个函数来判断

```c++
bool IsBalance()
```

这个函数的思路是：

```c++
// 首先，空树🌲是 avl 树
        if (root == nullptr)
            return true;
```

然后，我们计算左右字数的高度

```c++
// 计算左右子树的高度
        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
```

同过`高度差`来判断它是不是一个平衡的数

```c++
// 计算左右的高度差 ，abs 是求绝对值的
abs(leftHeight - rightHeight) < 2
```

然后我们再往下走下去，看看它的子树的子树是不是也是符合条件的，我们把这些条件写在一起就是：

```c++
        return abs(leftHeight - rightHeight) < 2 
        && _IsBalance(root->_left)
        && _IsBalance(root->_right)
        ;
```

``Isbalance`` 函数代码第一版：

```c++
    bool _IsBalance(Node *root)
    {
        // 首先，空树🌲是 avl 树
        if (root == nullptr)
            return true;
        // 计算左右子树的高度
        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
        // 计算左右的高度差 ，abs 是求绝对值的
        return abs(leftHeight - rightHeight) < 2 && _IsBalance(root->_left) && _IsBalance(root->_right);
    }
```

这个时候，通过上面的代码，树的平衡是没问题了，我们还可以顺便检查一下平衡因子`bf`，因为`bf`要是错了的话，在后面插入新的数据的时候也会影响树的平衡

```c++
        if (leftHeight - rightHeight != root->_bf)
        {
            cout << root->_kv.first << "平衡因子异常" << endl;
            return false;
        }
```

现在我们把代码加进去，`Isbalance` 函数第 2 版：

```c++
    bool _IsBalance(Node *root)
    {
        // 首先，空树🌲是 avl 树
        if (root == nullptr)
            return true;
        // 计算左右子树的高度
        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
        //检查平衡因子
        if (leftHeight - rightHeight != root->_bf)
        {
            cout << root->_kv.first << "平衡因子异常" << endl;
            return false;
        }
        // 计算左右的高度差 ，abs 是求绝对值的
        return abs(leftHeight - rightHeight) < 2 && _IsBalance(root->_left) && _IsBalance(root->_right);
    }
```

好了，我们还没有写`IsBalance`中求高度的函数，现在我们来写这个`Height`函数

```c++
    int _Height(Node *root)
    {
        // 如果是空树，那么它的高度是 0
        if (root == nullptr)
            return 0;
        // 分别求左右子树的高度
        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
        // 这棵树自己的高度 = 左右子树中高的那个 + 1
        return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
    }

```

# 目前代码

```c++
// test.cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include "AVLTree.h"

int main()
{
    int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    AVLTree<int, int> t;
    for (auto e : a)
    {
        t.Insert(make_pair(e, e));
    }
    t.InOrder();
    cout << t.IsBalance() << endl;
    return 0;
}

// int main()
//{
// map<string, string> dict;
// dict.insert(make_pair("left", "左边"));
// dict.insert(make_pair("left", "剩余"));
// dict.insert(make_pair("left", "左边"));
//
// for (auto& kv : dict)
// {
//  cout << kv.first << ":" << kv.second << endl;
// }
//
//
//
// return 0;
// }

// int main()
//{
// //int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
// int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
// AVLTree<int, int> t;
// for (auto e : a)
// {
//  t.Insert(make_pair(e, e));
// }
// t.InOrder();
// cout << t.IsBalance() << endl;
//
// return 0;
// }

/* int main()
{
    const int N = 30;
    vector<int> v;
    v.reserve(N);
    // srand(time(0));

    for (size_t i = 0; i < N; i++)
    {
        v.push_back(rand());
        cout << v.back() << endl;
    }

    AVLTree<int, int> t;
    for (auto e : v)
    {
        if (e == 14604)
        {
            int x = 0;
        }

        t.Insert(make_pair(e, e));
        cout << "Insert:" << e << "->" << t.IsBalance() << endl;
    }

    cout << t.IsBalance() << endl;

    return 0;
} */
```

```c++
// avltree.h
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

```
