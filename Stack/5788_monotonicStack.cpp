
#include<iostream>
#include<string>

using namespace std;

#define int long long
#define endl "\n"

const int N = 1e6 + 5;
int nums[N];
int Stack[N];
int Size;
int ans[N];

int n;

//这里题目 是洛谷的  要求右侧 第一个比自己大的元素的下标  不存在的话拿0替代
void compute() {

}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	compute();
	cout << ans[0];
	for (int i = 1; i < n; i++) {
		cout << " " << ans[i];
	}
	cout << endl;
}
