/*
最佳判定数、最优二叉树时一种带权路径长度最短的二叉树，常用于数据压缩
带权路径长度时书中所有的叶子节点的权只诚意其到根节点的路径长度
WPL = (W1 * L1 + W2 * L2 + .....Wn * Ln);

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
具有立刻解码性（其他编码序号不为当前编码的前缀）
因为字符（权值）都出现再叶子节点
A01
D10
E11
B0000
C0001
F0010
G0011

*/
#include<iostream>
#include<unordered_map>
#include<string>
#include<cstring>
#include<functional>
#include<queue>//


/*
文件压缩 20k -->12k  100M -->20M
		1k --->文件变大 ？？？ 正常
1.读取文件的所有内容，按照字节统计字节数据的权值，生成哈夫曼树
2.哈夫曼树---->哈夫曼编码
3.encode 把文件里面按字节进行编码，编码后的内容按位存储，存储到磁盘文件中
存储0、1码 还要把原始文件字节数据以及权值存储到压缩文件当中
解压缩时才能生成哈夫曼树  继续读取压缩文件里的0、1码，根据哈夫曼树，解压缩、还原出原始的文件数据


*/
/*
using MinHeap = priority_queue < Node*, vector<Node*>, function < bool(Node*, Node*)>>;
MinHeap minHeap_;
minHeap_([](Node* n1, Node* n2)->bool {return n1->weight_ > n2->weight_; })//初始化为小根堆

如果给定
节点 权值
节点 权值
*/
#if 0
using namespace std;
using uint = unsigned int;
using PAIR = pair<string, uint>;
class HuffmanTree {
public:
	//传入函数对象
	HuffmanTree()
		:minHeap_([](Node* n1, Node* n2)->bool {return n1->weight_ > n2->weight_; })//初始化为小根堆
		, root_(nullptr)
	{}
	~HuffmanTree() {//层序遍历  广度优先析构
		queue<Node*>que;
		que.push(root_);
		if (root_ == nullptr)
			return;
		while (!que.empty()) {
			Node* node = que.front();
			que.pop();
			if (node->left_ != nullptr)
				que.push(node->left_);
			if (node->right_ != nullptr)
				que.push(node->right_);
			delete node;
		}
		return;
	}
	//创建哈夫曼树（给定所有字符 ---转换为其他符号传输）
	void creatstring(string str) {
		//先统计字符的权值
		unordered_map<char, uint>dateMap;
		for (char ch : str) {
			dateMap[ch]++;
		}

		//生成节点，放入小根堆
		for (auto& pair : dateMap) {//传引用
			minHeap_.push(new Node(pair.first, pair.second));//字符  权值
		}

		//处理小根堆直至一个元素
		while (minHeap_.size() > 1) {
			Node* n1 = minHeap_.top();
			minHeap_.pop();
			Node* n2 = minHeap_.top();
			minHeap_.pop();
			//生成父节点
			Node* node = new Node('\0', n1->weight_ + n2->weight_);//父节点不存储字符
			node->left_ = n1;
			node->right_ = n2;
			minHeap_.push(node);//返回为小根堆
		}

		root_ = minHeap_.top();//最后一个数为根节点
		minHeap_.pop();
	}

	void creatchar(int n) {
		int tmp = n - 1;

		while (tmp--) {
			char ch; uint num;
			cin >> ch >> num;
			minHeap_.emplace(new Node(ch, num));
		}

		while (minHeap_.size() > 1) {
			Node* n1 = minHeap_.top();
			minHeap_.pop();
			Node* n2 = minHeap_.top();
			minHeap_.pop();
			Node* node = new Node('\0', n1->weight_ + n2->weight_);
			node->left_ = n1;
			node->right_ = n2;
			minHeap_.emplace(node);
		}

		root_ = minHeap_.top();
		minHeap_.pop();

	}
	//输出哈夫曼编码
	void showHuffmanTree() {
		string code = "";
		getHuffmanCode(root_, code);

		for (auto& pair : codeMap_) {
			cout << pair.first << ": " << pair.second << endl;
		}

		cout << endl;
	}
	void getHuffmanCode() {
		string code = "";//传入，递推遍历时到节点 将对应字符给为编码
		getHuffmanCode(root_, code);
	}

	//encode
	string encode(string str) {
		getHuffmanCode();
		string encode_str;

		for (auto ch : str) {
			encode_str.append(codeMap_[ch]);
		}

		return encode_str;
	}
	string decode(string encode) {
		string decode_str;
		Node* cur = root_;

		if (root_ == nullptr)
			return "";

		for (char ch : encode) {
			if (ch == '0') {
				cur = cur->left_;
			}
			else {
				cur = cur->right_;
			}
			if (cur->left_ == nullptr && cur->right_ == nullptr) {
				decode_str.push_back(cur->date_);
				cur = root_;
			}
		}

		return decode_str;
	}

private:
	struct Node {
		Node(char date, uint weight)
			:date_(date)
			, weight_(weight)
			, left_(nullptr)
			, right_(nullptr)
		{}
		//bool operator>(const Node& node)const { return weight_ > node.weight_; }
		char date_;//字符数据
		uint weight_;//节点权值
		Node* left_;//左孩子
		Node* right_;//右孩子

	};

private:
	Node* root_;//指向根节点
	unordered_map<char, string>codeMap_;//存储字符对应的哈夫曼编码
	//自定义小根堆排序方法
	//存储Node* 提供比较方法（权值）不然比较地址 给函数对象---》比较方法
	using MinHeap = priority_queue < Node*, vector<Node*>, function < bool(Node*, Node*)>>;
	MinHeap minHeap_;

private:

	void getHuffmanCode(Node* root_, string code) {
		//VLR
		if (root_ == nullptr)
			return;
		if (root_->left_ == nullptr && root_->right_ == nullptr) {//到达根节点
			codeMap_[root_->date_] = code;//尾节点---》string node
			return;
		}

		getHuffmanCode(root_->left_, code + "0");//哈夫曼树往左走则加0
		getHuffmanCode(root_->right_, code + "1");//
	}
};

int main() {
	HuffmanTree htree;
	int n;
	cin >> n;
	htree.creatchar(n);
	htree.showHuffmanTree();
	return 0;
}

int main_1() {
	int n;
	cin >> n;
	string str = "NEWNEWSTRINGSTRINGCODE";
	HuffmanTree htree;
	htree.creatstring(str);
	htree.showHuffmanTree();
	//string encode = htree.encode(str);
	//cout << "encode:" << htree.encode(str) << endl;
	//cout << "decode:" << htree.decode(encode) << endl;
	return 0;
}
#endif
