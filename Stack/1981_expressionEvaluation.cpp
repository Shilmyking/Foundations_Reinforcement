#include<iostream>
#include<string>

using namespace std;
#define int long long
#define endl "\n"

#if 0
const int N = 1e6 + 5;
int nums[N];
int Size = 0;
const int mod = 1e4;//10000
//1+1234567890*1

//正常的这种表达式 存在多种运算符  需要使用两个栈  
// 这里只有 +  or  *  所以就一个数字栈

int num;
char op;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> num;
	nums[Size++] = num%mod;

	while (cin >> op >> num) {
		num %= mod;
		if (op == '*') {
			int left = nums[--Size];
			nums[Size++] = ((num * left) % mod);
		}
		else {
			nums[Size++] = num % mod;//留到最后一起加
		}
	}

	num = 0;
	while (Size != 0) {
		num += (nums[--Size]);
		num %= mod;
	}
	cout << num << endl;
}
#endif