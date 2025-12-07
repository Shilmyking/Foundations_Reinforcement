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
		delete [] table_;
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