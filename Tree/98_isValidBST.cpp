
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
    using ll = long long;//8
    // INT_MAX  
    
    const ll INF = 0x3f3f3f3f3f3f3f3f;
    static const int MAXN = 1e4 + 5;
public:

    //前序限界  ---> 子树 深搜
    // 当前节点  以当前节点node为子树的所有后代 都必须在MIN~MAX这个范围内
    bool dfs(TreeNode* node,ll MIN,ll MAX) {
        if (node == nullptr) {
            return true;
        }
        //dfs
        if (!(MIN < node->val && node->val < MAX)) {
            return false;
        }

        bool Left = dfs(node->left, MIN, node->val);

        bool Right = dfs(node->right, node->val, MAX);

        return Left && Right;
    }

    bool isValidBST(TreeNode* root) {
        return dfs(root, -INF, INF);
    }


    //中序遍历
    ll last = -INF;
    // 或者使用一个 指针
    TreeNode* lastNode = nullptr;
    bool inOrder(TreeNode* root) {
        if (root == nullptr) { return true; }
        if(inOrder(root->left)==false) {
            return false;
        }
        //if (last >= root->val) {
        //    return false;
        //}
        //last = root->val;
        if (lastNode != nullptr && lastNode->val >= root->val) {
            return false;
        }
        lastNode = root;
        return inOrder(root->right);
    }

    TreeNode* Stack[MAXN];
    int Size = 0;
    bool inOrder1(TreeNode* root) {
        TreeNode* cur = root;
        TreeNode* last = nullptr;
        while (cur != nullptr || Size > 0) {
            if (cur != nullptr) {
                Stack[Size++] = cur;//先入栈 然后到下一个节点
                cur = cur->left;
            }
            else {
                //当前节点为nullptr  栈顶元素pop(回溯)
                cur = Stack[--Size];
                if (last != nullptr && last->val >= cur->val) {
                    return false;
                }
                last = cur;
                cur = cur->right;
            }
        }
        return true;
    }

    bool isValidBST2(TreeNode* root) {
        return inOrder1(root);
    }


    struct Node {
        //当前节点的是否vaild
        bool isVaild;
        //右侧的最小值  要大于当前值
        ll Max;
        //左侧的最大值  要小于当前值
        ll Min;
        Node(bool v, ll max, ll min) :isVaild(v), Max(max), Min(min) {}
    };
    // 当前子树是否为BST
    // 还特别需要维护 节点的最大值和最小值信息  所以树型DP  
    Node* f1(TreeNode* head) {
        if (head == nullptr) {
            // nullptr节点 整数最大(min) 整数最小(max)  
            // 才不会干扰上游节点BST的判断
            return new Node(true, -INF, INF);
        }
        Node* lt = f1(head->left);
        
        Node* rt = f1(head->right);

        ll Max = std::max({ lt->Max,rt->Max,(ll)head->val });
        ll Min = std::min({ lt->Min,rt->Min,(ll)head->val });
        
        return new Node(lt->isVaild && rt->isVaild && 
            ((head->val > lt->Max) && (head->val < rt->Min)), 
            Max, Min);
    }
    bool isValidBST3(TreeNode* root) {
        return f1(root)->isVaild;
    }


    // 全局  Max Min  如果这个节点的递归已经完成了 回到了这里
    ll Min, Max;
    bool f11(TreeNode* root) {
        if (root == nullptr) {
            Min = INF;
            Max = -INF;
            return true;
        }
        // 用 ll存在 INT_MAX的节点
        ll lmin, lmax, rmin, rmax;
        bool Left = f1(root->left);
        lmin = Min;
        lmax = Max;

        bool Right = f1(root->right);
        rmin = Min;
        rmax = Max;
        // 更新 Min Max
        
        Min = std::min({ lmin, rmin, (ll)root->val });
        Max = std::max({ lmax,rmax,(ll)root->val });
        return Left && Right && (root->val > lmax && root->val < rmin);
    }
    bool isValidBST3_1(TreeNode* root) {
        return f11(root);
    }

    bool Morris(TreeNode* root) {
        TreeNode* cur = root;
        TreeNode* last = nullptr;
        bool ans = true;
        while (cur != nullptr) {
            TreeNode* mostRight = cur->left;
            if (mostRight != nullptr) {
                while (mostRight->right != nullptr && mostRight->right != cur) {
                    mostRight = mostRight->right;
                }
                if (mostRight->right != cur) {//第一次
                    mostRight->right = cur;
                    cur = cur->left;
                    continue;
                }
                else {
                    mostRight->right = nullptr;
                }
            }

            // 不能提前返回 需要把此前修改过的指针 改回去
            if (last != nullptr && last->val >= cur->val) {
                ans = false;
                return false;
            }
            last = cur;

            cur = cur->right;
        }

        return ans;
    }

    bool isValidBST4(TreeNode* root) {
        return Morris(root);
    }
};
