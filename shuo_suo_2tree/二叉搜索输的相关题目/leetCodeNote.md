# 🏷️ 二叉搜索树的相关题目

## 📌 [606. 根据二叉树创建字符串](https://leetcode.cn/problems/construct-string-from-binary-tree/)

给你二叉树的根节点  `root` ，请你采用前序遍历的方式，将二叉树转化为一个由括号和整数组成的字符串，返回构造出的字符串。

空节点使用一对空括号对  `"()"`  表示，转化后需要省略所有不影响字符串与原始二叉树之间的一对一映射关系的空括号对。

**示例 1：**

![](https://assets.leetcode.com/uploads/2021/05/03/cons1-tree.jpg)

**输入** : root = [1,2,3,4]
**输出：**"1(2(4))(3)"
**解释** : 初步转化后得到 "1(2(4)())(3()())" ，但省略所有不必要的空括号对后，字符串应该是"1(2(4))(3)" 。

**示例 2：**

![](https://assets.leetcode.com/uploads/2021/05/03/cons2-tree.jpg)

**输入：** root = [1,2,3,null,4]
**输出：**"1(2()(4))(3)"
**解释：** 和第一个示例类似，但是无法省略第一个空括号对，否则会破坏输入与输出一一映射的关系。

**提示：**

- 树中节点的数目范围是  `[1, 104]`
- `-1000 <= Node.val <= 1000`

### ✏️ 解答：

#### 📎 读懂题目意思

题目的要求其实就是一个**前序遍历**，你看嘛，输出的是：`1, 2, 4, 3` ，少年！，扰乱你心智的就是那些括号。
题目是这样的意思，安照前序遍历：最先是`结点 1` 嘛，然后就该它的左子树了嘛，但是我们要用括号把`结点 1` 的左子树包起来，像这样：`1()` ，括号里就填左子树：`1(2)` ，按照前序遍历，我们该访问`节点 2` 的左子树了，我们依然要用括号包起来，像这样：`1(2())` ，括号里面就填 2 的左子树: `1(2(4))` ，看一下括号关系：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2e1e570f310d4746af45b2f3f5e04472.png)

以此类推,我们继续下去：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5c8b25c8db0649c18607f6f88d2da6da.png)
看清楚括号的关系没，就是：` 根 （左子树）（右子树）`

所以题目上的描述是有错误的"1(2(4)())(3()())"❌, 它 4 哪里少了 2 对括号

但是这道题又要求我们把**不必要的括号** 省略掉，就是把**空的括号**（即：结点为空）的给省略掉：
如下：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/b47022f3ee544588969840f4597758ec.png)
那就变成这样的了：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/80e4c46594cf45eba87df19bb14e9af0.png)

我们再来分析示例 2

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/dd2875d8cb954b26a62320a6763461b3.png)

我们发现当结点的左子树为空的时候是不能省略的，因为如果省略的话，就会造成歧义，无法判断此结点到底是左为空还是右为空。

- 左右为空可以省略括号
- 右为空省略括号
- 左为空,不能省略括号,无法跟右为空区分

#### ✏️ 解题：

大致思路：

```c++
class Solution
{
public:
    string tree2str(TreeNode *root)
    {
        string str;
        if (root == nullptr)
        {
            return str;
        }
        else
        {
            str += to_string(root->val); // val是 int 我们要记得转成 string,这一步就把根给 str
            str += "(";                  // 开始递归左子树之前，我们要记得加上括号
            str += tree2str(root->left); // 递归左子树
            str += ")";                  // 完成之后别忘了还有个括号

            str += "(";
            str += tree2str(root->right);
            str += ")";
        }
        return str;
    }
};
```

**以上代码是错的** ，因为我们还没按照题目的要求**去除掉空的括号** ，下面我们一起完善代码:

根据我们上面分析出来的结论，我们在代码中加上一些判断语句：

- 左右为空可以省略括号
- 右为空省略括号
- 左为空,不能省略括号,无法跟右为空区分

```c++
class Solution
{
public:
    string tree2str(TreeNode *root)
    {
        string str;
        if (root == nullptr)
            return str;

        str += to_string(root->val);
        if (root->left || root->right) // 这里的"||" 非常巧妙的解决了以下问题：
                                       // 如果左右都是空，那就都不用加括号
                                       // 如果左为空，右不为空，那左括号不能省略
        {
            str += "(";
            str += tree2str(root->left);
            str += ")";
        }

        if (root->right) // 如果右边不是空，那我们就要加上括号
        {
            str += "(";
            str += tree2str(root->right);
            str += ")";
        }

        return str;
    }
};
```
