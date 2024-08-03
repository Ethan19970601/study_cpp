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