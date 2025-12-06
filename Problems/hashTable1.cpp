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