/*
最佳判定数、最优二叉树时一种带权路径长度最短的二叉树，常用于数据压缩
带权路径长度时书中所有的叶子节点的权只诚意其到根节点的路径长度
Sum = (W1 * L1 + W2 * L2 + .....Wn * Ln);

一组权值
从权值里面选取最小的两个权值，构造一颗二叉树出来
（生成的父节点的权值时两个孩子节点的权值之和）
再把当前生成的二叉树的根节点权值，放入原始的权值列表当中，
继续重复1步骤 知道权值列表中只剩下一个节点

权值 2 2 4 6 8 10

应用场景
数据压缩 数据进行编码 统计数据的出现频率（权值）
出现频率高的（权值大）期望编码短一些
出现频率小的（权值小的）可以编码长一些


使用最小堆！ priority_queeu 默认为一个大根堆 =>改为小根堆
向左走为0，向右走为1

*/

/*

ABACDAEFDEG
1.统计字符出现的频率(权值)
A:3
B:1
C:1
D:2
E:2
F:1
G:1

变长编码
具有立刻解码性（其他编码序号不为当前编码的前缀） 非常重要的特性 ：其他编码序号不为当前编码的前缀
因为字符（权值）都出现再叶子节点
A01
D10
E11
B0000
C0001
F0010
G0011

*/

/*
文件压缩 20k -->12k  100M -->20M
		1k --->文件变大 ？？？ 正常
1.读取文件的所有内容，按照字节统计字节数据的权值，生成哈夫曼树
2.哈夫曼树---->哈夫曼编码
3.encode 把文件里面按字节进行编码，编码后的内容按位存储，存储到磁盘文件中
存储0、1码 还要把原始文件字节数据以及权值存储到压缩文件当中
解压缩时才能生成哈夫曼树  继续读取压缩文件里的0、1码，根据哈夫曼树，解压缩、还原出原始的文件数据

*/


#include<queue>
#include<algorithm>
#include<iostream>
#include<map>
#include<unordered_map>
#include<functional>

using namespace std;

using uint = unsigned int;
struct Node {
	Node* left;
	Node* right;
	uint weight;
	char data;
	Node(char data, uint weight, Node* left = nullptr, Node* right = nullptr)
		:data(data),
		weight(weight),
		left(left),
		right(right)
	{}
	bool operator<(const Node& node) {
		return weight > node.weight;// 默认的大根堆 反转为小根堆
	}
};

using MinHeap = priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>>;

class HuffmanTree {

public:
	HuffmanTree()
		:minHeap([](Node* n1, Node* n2)->bool {return n1->weight > n2->weight; }),
		root(nullptr)
	{}

	~HuffmanTree() {
		if (root != nullptr) {
			//层序遍历释放所有节点
			queue<Node*> que;
			que.push(root);
			while (!que.empty()) {
				Node* top = que.front();
				que.pop();
				if (top->left != nullptr) {
					que.push(top->left);
				}
				if (top->right != nullptr) {
					que.push(top->right);
				}
				delete top;
			}
		}
	}

	//创建哈夫曼树（给定所有字符 ---转换为其他符号传输）
	void createstring(const string& str) {
		unordered_map<char, uint>dataMap;//词频
		//统计词频
		for (int i = 0; i < str.size(); i++) {
			dataMap[str[i]]++;
		}

		//char + weight 入堆
		for (auto& pair : dataMap) {
			minHeap.push(new Node(pair.first, pair.second));
		}

		//所有节点入堆了 从权值小的从底往上建树
		while (minHeap.size() > 1) {
			//取出权值最小的两个节点 创建父节点
			Node* left = minHeap.top(); minHeap.pop();
			Node* right = minHeap.top(); minHeap.pop();
			Node* head = new Node('\0', left->weight + right->weight, left, right);
			minHeap.push(head);
		}
		root = minHeap.top();//最后一个就是root
		getHuffmanCode();//填好 codeMap
	}// n logn 

	//输入 char + 词频进行建树
	void creatchar(int n) {
		char ch;
		uint weight;
		while (n--) {
			cin >> ch >> weight;
			minHeap.push(new Node(ch, weight));
		}
		//所有节点入堆了 从权值小的从底往上建树
		while (minHeap.size() > 1) {
			//取出权值最小的两个节点 创建父节点
			Node* left = minHeap.top(); minHeap.pop();
			Node* right = minHeap.top(); minHeap.pop();
			Node* head = new Node('\0', left->weight + right->weight, left, right);
			minHeap.push(head);
		}
		root = minHeap.top();//最后一个就是root
		getHuffmanCode();
	}

	//输出哈夫曼编码
	void showHuffmanTree() {
		for (auto& pair : codeMap) {
			cout << pair.first << ": " << pair.second << endl;
		}
		cout << endl;
	}

	//encode
	string encode(const string& str) {
		string encodeString;
		// 遍历每一个char  查表
		for (int i = 0; i < str.size(); i++) {
			encodeString.append(codeMap[str[i]]);
		}
		return encodeString;
	}

	// 传入的是一个 01序列
	// 01 010 111 011 00
	// 
	string decode(const string& encode) {
		string decodeString;//解码为字符
		Node* cur = root;

		if (root == nullptr) {
			return decodeString;
		}
		int Size = encode.size();
		// Size  O(1) 
		// inline 
		for (int i = 0; i < encode.size(); i++) {
			if (encode[i] == '0') {
				cur = cur->left;
			}
			else { // '1'
				cur = cur->right;
			}
			if (cur == nullptr) {
				//??建树出错了
				throw "error:decode";
				return decodeString;
			}
			//到达叶子节点 收集答案
			if (cur->left == nullptr && cur->right == nullptr) {
				decodeString.push_back(cur->data);
				cur = root;//从根继续开始解码下一个
			}
		}

		return decodeString;
	}

private:
	void getHuffmanCode() {
		getHuffmanCode(root, "");//统计所有叶节点的 编码值  填好codeMap表
	}

	void getHuffmanCode(Node* head, string code) {
		if (head == nullptr) {//当前为nullptr节点 啥也没有
			return;
		}
		//叶子节点
		if (head->left == nullptr && head->right == nullptr) {
			codeMap[head->data] = code;
			return;
		}
		//左滑 0
		getHuffmanCode(head->left, code + "0");

		getHuffmanCode(head->right, code + "1"); // 右滑 1
	}

private:
	Node* root;
	unordered_map<char, string>codeMap;//编码
	MinHeap minHeap;
};


class {

};

struct TreeNode {
	TreeNode* left;
	TreeNode* right;
	uint weight;
	TreeNode(int w, TreeNode* left = nullptr, TreeNode* right = nullptr)
		:weight(w),
		left(left),
		right(right)
	{}
};

int WPL = 0;
// 0
int dfs_WPL(TreeNode* root, int depth) {
	if (root == nullptr) {
		return 0;
	}
	//叶子节点收集答案
	if (root->left == nullptr && root->right == nullptr) {
		WPL += root->weight * (depth );
		cout << "depth: " << depth  <<" curNodeWeight: " << root->weight<< " curWPL: " << WPL << endl;
	}
	//去孩子节点
	dfs_WPL(root->left, depth+1);

	dfs_WPL(root->right, depth+1);

}

void test_WPL() {

	TreeNode* root = new TreeNode(1, nullptr, nullptr);
	WPL = 0;
	dfs_WPL(root, 0);
	cout << "WPL:" << WPL << endl << endl;

}

void test1_WPL() {
	TreeNode* llt = new TreeNode(4);
	TreeNode* lrt = new TreeNode(5);
	TreeNode* lt = new TreeNode(2, llt, lrt);

	TreeNode* root = new TreeNode(1, lt);
	WPL = 0;
	dfs_WPL(root, 0);
	cout << "WPL:" << WPL << endl << endl;
}

void test2_WPL() {
	TreeNode* llt = new TreeNode(4);
	TreeNode* lrt = new TreeNode(5);
	TreeNode* lt = new TreeNode(2, llt, lrt);

	TreeNode* rlt = new TreeNode(6);
	TreeNode* rrt = new TreeNode(7);
	TreeNode* rt = new TreeNode(3, rlt, rrt);

	TreeNode* root = new TreeNode(1, lt, rt);
	WPL = 0;
	dfs_WPL(root, 0);
	cout << "WPL:" << WPL << endl << endl;
}

void test3_WPL() {

	TreeNode* llt = new TreeNode(4, new TreeNode(8));
	TreeNode* lrt = new TreeNode(5);
	TreeNode* lt = new TreeNode(2, llt, lrt);

	TreeNode* rlt = new TreeNode(6);
	TreeNode* rrt = new TreeNode(7);
	TreeNode* rt = new TreeNode(3, rlt, rrt);

	TreeNode* root = new TreeNode(1, lt, rt);
	WPL = 0;
	dfs_WPL(root, 0);
	cout << "WPL:" << WPL << endl << endl;
}


// 当前以root为头节点的子树 
// 来到当前节点 上层路径累加和为curSum
int Sum = 0;
int dfs(TreeNode* root,int preSum ) {
	if (root == nullptr) {
		return 0;
	}
	//叶子节点收集答案
	if (root->left == nullptr && root->right == nullptr) {
		Sum += preSum + root->weight;
		cout << "preSum: "<<preSum+root->weight << " curSum: " << Sum << endl;
	}
	//去孩子节点
	dfs(root->left, preSum + root->weight);

	dfs(root->right, preSum + root->weight);
	// 值传递无需操作
}

void test() {

	TreeNode* root = new TreeNode(1, nullptr, nullptr);
	Sum = 0;
	dfs(root, 0);
	cout << "Sum:" << Sum << endl << endl;

}

void test1() {
	TreeNode* llt = new TreeNode(4);
	TreeNode* lrt = new TreeNode(5);
	TreeNode* lt = new TreeNode(2, llt, lrt);

	TreeNode* root = new TreeNode(1, lt);
	Sum = 0;
	dfs(root, 0);
	cout << "Sum:" << Sum << endl << endl;
}

void test2() {
	TreeNode* llt = new TreeNode(4);
	TreeNode* lrt = new TreeNode(5);
	TreeNode* lt = new TreeNode(2, llt, lrt);

	TreeNode* rlt = new TreeNode(6);
	TreeNode* rrt = new TreeNode(7);
	TreeNode* rt = new TreeNode(3, rlt, rrt);

	TreeNode* root = new TreeNode(1, lt, rt);
	Sum = 0;
	dfs(root, 0);
	cout << "Sum:" << Sum << endl<<endl;
}

void test3() {

	TreeNode* llt = new TreeNode(4, new TreeNode(8));
	TreeNode* lrt = new TreeNode(5);
	TreeNode* lt = new TreeNode(2, llt, lrt);

	TreeNode* rlt = new TreeNode(6);
	TreeNode* rrt = new TreeNode(7);
	TreeNode* rt = new TreeNode(3, rlt, rrt);

	TreeNode* root = new TreeNode(1, lt, rt);
	Sum = 0;
	dfs(root, 0);
	cout << "Sum:" << Sum << endl<<endl;
}

//int main() {
//	string str = "aaaabbbcccddeefg";
//	HuffmanTree htree;
//	htree.createstring(str);
//	htree.showHuffmanTree();
//	//string encode = htree.encode(str);
//	//cout << "encode:" << htree.encode(str) << endl;
//	//cout << "decode:" << htree.decode(encode) << endl;
//
//	cout << endl << endl;
//	test();
//	test1();
//	test2();
//	test3();
//
//	test_WPL();
//	test1_WPL();
//	test2_WPL();
//	test3_WPL();
//}