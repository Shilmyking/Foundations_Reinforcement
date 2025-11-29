
#if 0
#include <iostream>
#include <vector>
#include<cstring>
#include<string>

#include <random>    
#include <algorithm> // 用于 shuffle

using namespace std;

random_device rd;
mt19937 rng(rd());

int randomInt(int min, int max) {
	uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v, TreeNode* l = nullptr, TreeNode* r = nullptr) :val(v), left(l), right(r) {}
};

TreeNode* root = nullptr;
TreeNode* insert(TreeNode* root, int val) {
	if (root == nullptr) {//basecase
		return  new TreeNode(val);
	}
	//往孩子走
	if (root->val >= val) {
		root->right = insert(root->right, val);
	}
	else {
		root->left = insert(root->left, val);
	}
	//返回当前 给父节点连接
	return root;
}

TreeNode* generateBST(int n, int minVal, int maxVal) {
	TreeNode* root = nullptr;
	for (int i = 1; i <= n; i++) {
		root = insert(root, randomInt(minVal, maxVal));
	}
	return root;
}

string getSpace(int num) {
	return string(max(0, num), ' ');
}

// 逆中序遍历 (右 -> 根 -> 左)
void printInOrderPointer(TreeNode* head, int height, string to, int len) {
	if (head == nullptr) {
		return;
	}
	// 先打印右子树 (位置在上方)
	printInOrderPointer(head->right, height + 1, "v", len);

	// 拼接当前节点内容
	string val = to + to_string(head->val) + to; // 格式如: ^10^
	int lenM = val.length();
	int lenL = (len - lenM) / 2;
	int lenR = len - lenM - lenL;

	// 计算缩进并打印
	// height * len 是层级缩进，val 被空格包裹以居中
	cout << getSpace(height * len) + getSpace(lenL) + val + getSpace(lenR) << endl;

	// 后打印左子树 (位置在下方)
	printInOrderPointer(head->left, height + 1, "^", len);
}


void printTree(TreeNode* head) {
	cout << "=== Binary Tree Structure ===========================================================================================" << endl;
	// len = 17 是每个节点占据的字符宽度，可调整
	printInOrderPointer(head, 0, "H", 17);
	cout << "============================================================================================================" << endl;
}

void Morris(TreeNode* root) {
	TreeNode* cur = root;
	while (cur != nullptr) {

		if (cur->left != nullptr) {
			TreeNode* pre = cur->left;
			while (pre->right != nullptr) {
				pre = pre->right;
			}
			// pre就是前驱
			pre->right = cur->right;

			//本题 右孩子改为指向左孩子
			cur->right = cur->left;
			cur->left == nullptr;//这里恰好 退出if再次遇到if --->走right了
		}
		else {
			cur = cur->right;//就是此前原树的左孩子
		}
	}
}

void flatten(TreeNode* root) {
	Morris(root);
}

int main() {
	root = generateBST(10, -1, 10);
	printTree(root);
	flatten(root);
	cout << root->val << endl;
	printTree(root);
}
#endif