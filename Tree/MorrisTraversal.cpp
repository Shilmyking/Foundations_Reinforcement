//
//#include<algorithm>
//#include<vector>
//#include<iostream>
//#include<string>
//#include<cstring>
//using namespace std;
//
//struct TreeNode {
//    int val;
//    TreeNode* left;
//    TreeNode* right;
//    TreeNode() : val(0), left(nullptr), right(nullptr) {}
//    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
//};
//
//const int MAXN = 100;
//int morris[MAXN], morrisi = 0;
//int pre[MAXN],prei=0;
//int in[MAXN], ini=0;
//int post[MAXN], posti = 0;
//
//TreeNode* reverse(TreeNode* root);
//void collect(TreeNode* root);
//
//
//void Morris(TreeNode* root) {
//    TreeNode* cur = root;
//    while (cur != nullptr) {
//        //需要找到前驱节点
//        TreeNode* mostRight = cur->left;
//        //存在左子树的话 找到左子树的最右节点
//        if (mostRight != nullptr) {
//            //最后可能 遇到nullptr 停止  或者 遇到cur停止
//            while (mostRight->right != nullptr && mostRight->right != cur) {
//                mostRight = mostRight->right;
//            }
//            //第一次来到cur这个节点
//            if (mostRight->right != cur) {
//
//                morris[morrisi++] = cur->val;
//                pre[prei++] = cur->val;
//                cout << "first time（waiting for second time）:" << cur->val << endl;
//
//                mostRight->right = cur;
//                //cur 往左继续走
//                cur = cur->left;
//            }
//            else {//cur
//                morris[morrisi++] = cur->val;
//                in[ini++] = cur->val;
//                cout << "second time:" << cur->val << endl;
//
//                //第二次来到cur这个节点
//                mostRight->right = nullptr;//恢复原样
//
//                //恢复好结构之后 收集post
//                collect(cur->left);
//
//                //去右子树继续 遍历   左树已经遍历完了
//                cur = cur->right;
//            }
//        }
//        else {
//            morris[morrisi++] = cur->val;
//            pre[prei++] = cur->val;
//            in[ini++] = cur->val;
//            cout << "first time:" << cur->val << endl;
//            //不存在 左子树 直接去右树
//            cur = cur->right;
//        }
//    }
//    collect(root);
//}
//
//TreeNode* reverse(TreeNode* root) {
//    TreeNode* pre = nullptr;
//    TreeNode* cur = root;
//    TreeNode* next = nullptr;
//    while (cur != nullptr) {
//        next = cur->right;
//        cur->right = pre;
//        pre = cur;
//        cur = next;
//    }
//    return pre;
//}
//
//
//// 收集 当前节点为root的子树的 右边界
//// 当然是要逆序收集 
//void collect(TreeNode* root) {
//    //抓末尾节点
//    TreeNode* tail = reverse(root);
//    TreeNode* cur = tail;
//    //遍历收集一遍
//    while (cur != nullptr) {
//        post[posti++] = cur->val;
//        cur = cur->right;
//    }
//    reverse(tail);//恢复结构
//}
//
//void print() {
//    cout << "morris: ";
//    for (int i = 0; i < morrisi; i++) {
//        cout << morris[i] << " ";
//    }
//    cout <<endl<< "pre: ";
//    for (int i = 0; i < prei; i++) {
//        cout << pre[i] << " ";
//    }
//    cout << endl<<"in: ";
//    for (int i = 0; i < ini; i++) {
//        cout << in[i] << " ";
//    }
//    cout << endl << "post: ";
//    for (int i = 0; i < posti; i++) {
//        cout << post[i] << " ";
//    }
//    cout << endl;
//}
//
//int main() {
//
//    TreeNode* llt = new TreeNode(4);
//    TreeNode* lrt = new TreeNode(5);
//    TreeNode* lt = new TreeNode(2, llt, lrt);
//
//    TreeNode* rlt = new TreeNode(6);
//    TreeNode* rrt = new TreeNode(7);
//    TreeNode* rt = new TreeNode(3, rlt, rrt);
//
//    TreeNode* root = new TreeNode(1, lt, rt);
//    Morris(root);
//    print();
//}