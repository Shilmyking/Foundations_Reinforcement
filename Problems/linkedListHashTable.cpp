
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


#include<iostream>
#include<vector>
#include<list>
#include<functional>
#include<algorithm>
using namespace std;

const int PRIME_SIZE = 9;
int primes[PRIME_SIZE] = { 3,7,23,47,97,251,443,1471,42773 };

class linkedListHashTable {
public:
	linkedListHashTable(int tableSize = primes[0], double lF = 0.75) :tableSize(tableSize),usedBucketNums(0), primeIndex(0),loadFactor(lF) {
		int i = 0;
		if (tableSize > primes[0]) {//需要去找合适的大小
			while (i < PRIME_SIZE - 1 && tableSize > primes[i]) {
				i++;
			}//出循环 tableSize<=primes[i] || i ==PRIME_SIZE
		}
		primeIndex = i;
		tableSize = primes[i];
		table.resize(primes[i]);
	}

	//不重复加入元素
	void Insert(int key) {
		double lF =  usedBucketNums * 1.0 / tableSize;
		if (lF > loadFactor) {
			expand();
		}
		int index = key % tableSize;
		//直接加入 or 存在元素 check是否存在
		if (table[index].empty()) {
			table[index].push_front(key);
			usedBucketNums++;
		}
		else {
			//链表遍历 查找key
			auto it = ::find(table[index].begin(), table[index].end(), key);
			if (it == table[index].end()) {
				table[index].push_front(key);
			}
		}
	}

	void erase(int key) {
		int index = key % tableSize;
		auto it = ::find(table[index].begin(), table[index].end(), key);
		if (it != table[index].end()) {
			table[index].erase(it);
		}
		if (table[index].empty()) {
			usedBucketNums--;
		}
	}

	bool find(int key) {
		int index = key % tableSize;
		auto it = ::find(table[index].begin(), table[index].end(), key);
		return it != table[index].end();
	}

	void expand() {
		primeIndex += primeIndex == PRIME_SIZE - 1 ? 0 : 1;
		tableSize = primes[primeIndex];
		usedBucketNums = 0;
		vector<list<int>>oldTable;
		table.swap(oldTable);//在栈上的三个指针 交换即可 效率高
		table.resize(primes[primeIndex]);

		for (auto& list : oldTable) {
			for (auto& key : list) {
				int index = key % tableSize;
				if (table[index].empty()) {
					usedBucketNums++;
				}
				//无需考虑去重了 原本就是去重之后的
				table[index].push_front(key);
			}
		}

	}

private:
	vector<list<int>>table;
	int tableSize;
	int usedBucketNums;// 桶的个数
	double loadFactor;
	int primeIndex;
};


