
#include<algorithm>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
    struct Node {
        //当前节点的是否vaild
        bool isVaild;
        //右侧的最小值  要大于当前值
        int Max;
        //左侧的最大值  要小于当前值
        int Min;
        Node(bool v,int max,int min):isVaild(v),Max(max),Min(min){}
    };
public:
    //当前子树是否为BST
    // 还特别需要维护 节点的最大值和最小值信息  所以树型DP  
    const int INF = 0x3f3f3f3f;
    Node* f(TreeNode*node) {
        //左中右
        if (node->left == nullptr && node->right == nullptr) {
            return new Node(true, node->val, node->val);
        }
        if (node->left == nullptr && node->right != nullptr) {
            //左侧为nullptr  右侧存在孩子
            bool vaild = node->val < node->right->val;
            int Max = std::max(node->val, node->right->val);
            int Min = std::min(node->val, node->right->val);
            return new Node(vaild, Max, Min);
        }
        if (node->left != nullptr && node->right == nullptr) {
            //右侧为nullptr  左侧存在孩子
            bool vaild = node->val > node->left->val;
            int Max = std::max(node->val, node->left->val);
            int Min = std::min(node->val, node->left->val);
            return new Node(vaild, Max, Min);
        }
        Node* left = f(node->left);
        Node* right = f(node->right);
        int curValue = node->val;
        bool isVaild = left->isVaild && right->isVaild && (left->Max<curValue && right->Min>curValue);
        //当前子树的最大值  和最小值
        int Max = std::max(curValue, std::max(left->Max, right->Max));
        int Min = std::min(curValue, std::min(left->Min, right->Min));
        return new Node(isVaild,Max,Min);
    }
    bool isValidBST(TreeNode* root) {
        return f(root)->isVaild;
    }
};