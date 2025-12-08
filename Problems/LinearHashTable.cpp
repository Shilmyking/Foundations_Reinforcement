
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;

#define PRIME_SIZE 9

//素数表 3，7，23，47，97，251，443，991，1471，42773 内存字节数与堆内存相同
const int primes[PRIME_SIZE] = { 3,7,23,47,97,251,443,1471,42773 };

//哈希桶的状态
enum State{
	UNUSE,
	USING,
	DEL,
};

struct Bucket {
	int key;
	State state;
	Bucket(int k = 0, State s = UNUSE) :key(k), state(s) {}
};


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

class HashTable {
private:
	Bucket* table;//哈希表
	int tableSize;//总大小
	int useBucketNum;//已经使用的个数
	double loadFactor;//装载因子
	int primeIndex;// 素数表下标

private:
	void expand() {
		//数据全部迁移到 新表
		if (primeIndex + 1 == PRIME_SIZE) {
			return;
		}
		int newSize = primes[primeIndex + 1];
		Bucket* newTable = new Bucket[newSize];//新表
		
		for (int i = 0; i < primeIndex; i++) {
			if (table[i].state == USING) {
				int index = table[i].key % newSize;
				int nextI = index;
				if (newTable[nextI].state == USING) {
					//往后找到位置
					nextI = (nextI + 1) % newSize;
					while (nextI != index && newTable[nextI].state == USING) {
						nextI = (nextI + 1) % newSize;
					}
				}
				newTable[nextI].state = USING;
				newTable[nextI].key = table[i].key;

			}
		}
		tableSize = newSize;
		primeIndex++;
		delete[]table;
		table = newTable;
	}
public:
	HashTable(int size = primes[0], int loadFactor = 0.75) :loadFactor(loadFactor),useBucketNum(0), primeIndex(0) {
		// 根据size找到合适的初始大小
		if (size != primes[0]) {
			while (primeIndex < PRIME_SIZE - 1 && primes[primeIndex] < size) {
				primeIndex++;
			}
		}
		tableSize = primes[primeIndex];
		table = new Bucket[tableSize];
	}

	bool insert(int key) {
		double factor = useBucketNum * 1.0 / tableSize;
		if (factor > loadFactor) {//扩容
			expand();
		}
		int index = key % tableSize;
		int i = index;//直接映射到的下标 如果遇到 哈希冲突就往后找

		//哈希冲突 往后找第一个能插入的位置 如果转了一圈都没有找到 那就是return false 了 无法插入？
		//哈希冲突 去找后续的位置
		if (table[i].state == USING) {
			//只要 不越界  +  这个位置不能放 也就是 是USING
			while (i != index&& table[i].state == USING) {
				i = (i + 1) % tableSize;
			}
		}//出循环要么找到位置 能放下   回到index要么无法放下
		if (i == index) {
			return false;
		}

		table[i].state = USING;
		table[i].key = key;
		useBucketNum++;
		return true;
	}

	//return true 找到了 并且删除
	// return false 没找到
	bool earse(int key) {
		int index = key % tableSize;
		int i = index;
		if (table[i].state == USING && table[i].key == key) {
			table[i].state = UNUSE;
			return true;
		}
		//i位置不是 key 那就是往后找一圈
		i = (i + 1) % tableSize;
		while (i != index && !(table[i].key != key && table[i].state == USING)) {
			i = (i + 1) % tableSize;
		}
		//这个位置就是存储的位置
		if (table[i].key == key && table[i].state == USING) {
			table[i].state = DEL;
			return true;
		}
		// 还是没找到
		return false;//不存在
	}

	//找到return true  没找到 return false
	bool find(int key) {
		int index = key % tableSize;
		int i = index;

		if (table[i].state==USING&&table[i].key == key) {
			return true;
		}
		i = (i + 1) % tableSize;
		while (i != index) {
			if (table[i].state == USING && table[i].key == key) {
				return true;
			}
			i = (i + 1) % tableSize;
		}
		return false;
	}

};