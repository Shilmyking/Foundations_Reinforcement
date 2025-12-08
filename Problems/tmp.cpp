
//线性探测哈希表

/*

增加： 通过哈希函数 计算存放位置
该位置空闲 直接存储
被占用 当前位置向后找空闲位置、存放哈希表（要防止越界）

查询： 通过哈希函数计算数据存储分位置 取值 判断状态STATE_USING
	该值==查询值 找到了
		！=   发生哈希冲突 往后遍历寻找该元素
		1.该位置一直为空 ，没放过元素  ---不需要继续往后搜索
		2.位置为空 以前放过元素，后来被删除 ---需要往后搜索

删除： 通过哈希函数计算数据存储位置，从该位置取该值，判断状态STATE_USING
		== 直接求改当前位置的状态就可以 STATE_DEL
		！= 要删除的值（之前有哈希冲突），从当前位置向后遍历，找到该元素，修改状态，
		入宫遇到STATE_UNUSE结束


*/
#if 0

#include<iostream>
using namespace std;
//桶的状态
enum State {
	STATE_UNUSE,//从未使用过的桶
	STATE_USING,//正在使用
	STATE_DEL,//元素被删除了  不必把值给置空 根据状态判断
};

struct Bucket {
	Bucket(int key = 0, State state = STATE_UNUSE)
		:key_(key)
		, state_(state) {}
	int key_;//存储的数据
	State state_;//桶当前的状态
};

//线性探测哈希表类型
class HashTable {
public:

	HashTable(int size = primes_[0], double loadFactor = 0.75)
		:useBucketNum_(0)
		, loadFactor_(loadFactor)
		, primeIdx_(0)
	{
		//将传入的size调整为素数表上相近的素数
		if (size != primes_[0]) {
			for (; primeIdx_ < PRIME_SIZE; primeIdx_++) {
				if (primes_[primeIdx_] > size) break;
			}
			//用户传入的size值过大，已经超过最后一个素数，调整为最后一个素数
			if (primeIdx_ == PRIME_SIZE)
				primeIdx_--;
		}
		tableSize_ = primes_[primeIdx_];
		table_ = new Bucket[tableSize_];
	}

	~HashTable() {
		delete[] table_;
		table_ = nullptr;
	}

public:

	bool insert(int key) {
		//考虑扩容
		double factor = useBucketNum_ * 1.0 / tableSize_;//两个整数相除
		if (factor > loadFactor_) {
			expand();
		}
		int idx = key % tableSize_;
		int i = idx;
		do {
			if (table_[idx].state_ != STATE_USING) {
				table_[idx].state_ = STATE_USING;
				table_[idx].key_ = key;
				useBucketNum_++;
				return true;
			}
			i = (i + 1) % tableSize_;
		} while (i != idx);

		/*
		重复代码优化
		do while() 先做循环体再判断条件
		if (table_[idx].state_ != STATE_USING) {
			table_[idx].state_ = STATE_USING;
			table_[idx].key_ = key;
			useBucketNum_++;
			return true;
		}
		for (int i = (idx + 1) % tableSize_; i != idx; i=(i+1)%tableSize_) {
			if (table_[i].state_ != STATE_USING) {
				table_[i].state_ = STATE_USING;
				table_[i].key_ = key;
				useBucketNum_++;
				return true;
			}
		}
		*/
		return false;
	}

	bool erase(int key) {
		int idx = key % tableSize_;
		int i = idx;
		do {
			if (table_[i].state_ == STATE_USING && table_[i].key_ == key) {
				table_[i].state_ = STATE_DEL;
				useBucketNum_--;
			}
			i = (i + 1) % tableSize_;
		} while (table_[i].state_ != STATE_UNUSE && i != idx);
		return true;
	}

	//查询 count(key)
	bool find(int key) {
		int idx = key % tableSize_;
		int i = idx;
		do {
			if (table_[i].state_ == STATE_USING && table_[i].key_ == key) {
				return true;
			}
			i = (i + 1) % tableSize_;
		} while (table_[i].state_ != STATE_UNUSE && i != idx);
		return false;
	}

private:
	//扩容操作
	void expand() {
		if (primeIdx_ == PRIME_SIZE)
			throw "HashTable is too large,can't expand anymore!";
		primeIdx_++;

		Bucket* newTable = new Bucket[primes_[primeIdx_]];
		for (int i = 0; i < tableSize_; i++) {
			//旧表有效的数据，重新哈希放到扩容后的新表
			if (table_[i].state_ == STATE_USING)
			{
				int idx = table_[i].key_ % primes_[primeIdx_];
				int k = idx;
				do {
					if (newTable[k].state_ != STATE_USING) {
						newTable[k].state_ = STATE_USING;
						newTable[k].key_ = table_[i].key_;
						break;
					}
					k = (k + 1) % primes_[primeIdx_];
				} while (k != idx);
			}
		}
		delete[]table_;
		table_ = newTable;
		tableSize_ = primes_[primeIdx_];
	}

private:
	Bucket* table_;//指向动态开辟的哈希表//不使用vector（会自增长）
	int tableSize_;//哈希表当前的长度
	int useBucketNum_;//已经使用的桶的个数
	double loadFactor_;//哈希表的装载因子
	//素数表 3，7，23，47，97，251，443，991，1471，42773 内存字节数与堆内存相同
	static const int PRIME_SIZE = 10;//素数表的大小
	static int primes_[PRIME_SIZE];
	int primeIdx_;//当前使用的素数下标
};

int HashTable::primes_[PRIME_SIZE] = { 3,7,23,47,97,251,443,1471,42773 };
int main() {
	HashTable htable;
	htable.insert(21);
	htable.insert(32);
	htable.insert(14);
	htable.insert(15);
	htable.insert(22);
	htable.insert(15);
	/*cout << htable.find(22) << endl;
	htable.erase(22);
	cout << htable.find(22) << endl;
	htable.insert(15);*/
	cout << htable.find(15) << endl;
}
#endif



// 链式哈希表

/*


线性探测哈希表的缺陷：
1.发生哈希冲突时，靠近O(n)的时间复杂度，存储变慢了   在线性探测哈希表中无法优化

2.多线程环境中，线性探测表所用到的基于数组实现的哈希表
只能给全局的哈希表用互斥锁来保证哈希表的原子操作，保证线程安全
//多个线程中无法在一个数组中操作   互斥操作 保证安全

当两个或多个线程并发执行时，若都发生哈希冲突 向后寻找空闲位置时 最终后放数据的线程将前者的数据覆盖、





无序关联容器 采用链式哈希表




链式哈希表：
多线程时，使用分段的锁既保证线程的安全又有一定大并发量，提高了效率

12 18 21 24 33 45 67 72   除留余数法 +链地址法

tableSize_=7
链结点
vector<list<int>>table;
在每一个哈希桶中利用一个分段锁来控制该桶
0   |21| |
1
2	|72| |
3	|24| | ——|45| |
4   |18| | ——|67| |
5   |12| | ——|33| |
6

增加：O(1)
搜索 21
21%7=0 ；O（1）
此时为 table[0] O(1)
删除 遍历链表 O（n)

解决数据过多，链表过长 效率低
优化1：当链表长度大于8（10），把桶里面的这个链表转化成红黑树O（log n）
//但红黑树每个节点花费内存（存储地址多）比链表多

优化2：链式哈希表每个桶都可以创建自己的互斥锁，不同桶中的链表操作，可以并发执行起来；
散列结果越散越好 ——最少冲突

哈希表：无限趋向于O（1） 哈希冲突的存在
*/
#if 0
#include<iostream>
#include<vector>
#include<list>
#include<functional>
using namespace std;

class HashTable {
public:
	HashTable(int size = primes_[0], double loadFactor = 0.75)
		:useBucketNum_(0)
		, loadFactor_(loadFactor)
		, primeIdx_(0)
	{
		if (size != primes_[0]) {//传入size   选取合适的除数 
			for (; primeIdx_ < PRIME_SIZE; primeIdx_++)
				if (primes_[primeIdx_] >= size)
					break;
			if (primeIdx_ == PRIME_SIZE) primeIdx_--;//不要越界
		}
		table_.resize(primes_[primeIdx_]);
	}
public:
	//增加元素 不能重复插入key
	void insert(int key) {
		double factor = useBucketNum_ * 1.0 / table_.size();
		//cout << "factor:" << factor << endl;
		if (factor > loadFactor_) expand();
		int idx = key % table_.size();
		if (table_[idx].empty()) {//桶空
			useBucketNum_++;
			table_[idx].emplace_front(key);
		}
		else {//去重  如果不存在则加入   //可以转为红黑树优化  
			auto it = std::find(table_[idx].begin(), table_[idx].end(), key);//O(n);
			if (it == table_[idx].end()) table_[idx].emplace_front(key);
		}

	}

	void erase(int key) {
		int idx = key % table_.size();
		//如果链表节点过长：如果散列结果比较集中（散列函数有问题） //如果散列结果比较离散，链表长度一般不会过长（装载因子）
		auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
		if (it != table_[idx].end()) table_[idx].erase(it);
		if (table_[idx].empty()) useBucketNum_--;
	}
	bool find(int key) {
		int idx = key % table_.size();
		auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
		return it != table_[idx].end();
	}
private:
	void expand() {
		if (primeIdx_ + 1 == PRIME_SIZE)
			throw"hashtable can not expand anymore!";
		primeIdx_++;
		useBucketNum_ = 0;
		//swap效率会不会很低？？？ 
		// 交换了两个容器的成员变量   并没有交换堆上的内存以及表里的数据
		/*
		vec1
		mpvec——堆内存

		vec2
		vec1.swap(vec2);————vec1变为空
		空间配置  C++内置  自定义
		如果两个容器使用的空间配置器allocator时一样的，
		那么直接交换两个容器的成员变量即可，效率高

		如果两个容器使用的空间配置器allocator是不一样的，
		那么意味着 两个容器管理外部堆内存的方式不一样
		此时，需要效率低的整个数据的变换
		*/
		vector <list<int>> oldTable;
		table_.swap(oldTable);
		table_.resize(primes_[primeIdx_]);
		for (auto list : oldTable) {
			for (auto key : list) {
				int idx = key % table_.size();
				if (table_[idx].empty()) {//桶空
					useBucketNum_++;
					//从哈希表里来不用去重
					table_[idx].emplace_front(key);
				}
			}
		}
	}
private:
	vector<list<int>>table_;//哈希表的数据结构
	int useBucketNum_;//记录桶的个数
	double loadFactor_;//记录哈希表装载因子
	static const int PRIME_SIZE = 10;//素数表的大小
	static int primes_[PRIME_SIZE];//素数表
	int primeIdx_;//当前使用的素数的小标
};


int HashTable::primes_[PRIME_SIZE] = { 3,7,23,47,97,251,443,1471,42773 };
int main() {
	HashTable htable;
	htable.insert(21);
	htable.insert(32);
	htable.insert(14);
	htable.insert(15);
	htable.insert(22);
	htable.insert(67);
	/*cout << htable.find(22) << endl;
	htable.erase(22);
	cout << htable.find(22) << endl;
	htable.insert(15);*/
	cout << htable.find(15) << endl;
}

#endif