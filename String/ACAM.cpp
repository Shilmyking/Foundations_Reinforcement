
// AC自动机模版(优化版)
// 给你若干目标字符串，还有一篇文章
// 返回每个目标字符串在文章中出现了几次
// 测试链接 : https://www.luogu.com.cn/problem/P5357
#if 0
#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<cstring>
#include<set>
#include<unordered_set>
using namespace std;

#define int long long
#define endl "\n"
// 2000_000
const int MAXN = 2e5 + 2;
const int MAXS = 2e5 + 5;

int End[MAXN];//每个目标串的结尾节点编号
int tree[MAXS][26];//前缀树  
int fail[MAXS];//fail指针
int cnt = 0;//0号head节点

int times[MAXS];//收集每个节点的词频

int box[MAXS];//作为容器  queue  Stack

//链式前向星  少一个边权
int head[MAXS];
int nexts[MAXS];
int to[MAXS];
int edge = 1;//指向待添加的哪一个位置

void addEdge(int u, int v) {
	nexts[edge] = head[u];//这条边的上一条边是head[u]
	to[edge] = v;
	head[u] = edge++;//head[u]节点指向新加入的边
}

bool visited[MAXS];//遍历反图 非递归版本

int n;
string s, t;
//i 代表第几个字符
void insert(int i, const string& s) {//前缀树插入
	int cur = 0;//初始节点是0 head
	for (auto& v : s) {
		int path = v - 'a';//这才是path  路！！ 就是26字母当种的一个
		if (tree[cur][path] == 0) {
			//不存在就创建
			tree[cur][path] = ++cnt;
		}
		cur = tree[cur][path];
	}
	End[i] = cur;
}

// 设置fail指针  bfs
// AC优化版本
void setFail() {
	int cur = 0;
	int l = 0, r = 0;//队列 bfs
	for (int i = 0; i < 26; i++) {
		if (tree[cur][i] > 0) {// tree[0][i]  对的对的 就是 root节点的下一批
			box[r++] = tree[cur][i];
		}
	}//第一层节点加入

	while (l < r) {
		cur = box[l++];//队首
		//加入下级节点 还有设置当前节点的fail指针
		for (int i = 0; i < 26; i++) {
			if (tree[cur][i] == 0) {//根本不存在这个下级节点
				//不存在这个节点 那设置为父节点fail指针指向的下级相同的那个元素
				tree[cur][i] = tree[fail[cur]][i];//父节点fail
			}
			else {
				// 存在这个孩子节点 设置fail指针 
				// fail指向 为父节点的fail指向的节点的下一级相同的元素
				// 放入 bfs
				fail[tree[cur][i]] = tree[fail[cur]][i];
				box[r++] = tree[cur][i];
			}
		}
	}
}

void f1(int u) {
	for (int i = head[u]; i > 0; i = nexts[i]) {
		f1(to[i]);//汇总完 这个子节点 
		//然后累加到当前节点
		times[u] += times[to[i]];
	}
}

//非递归  自己压栈
void f2(int u) {
	//box 作为栈模拟递归
	// 需要visited数组作为一个标识当前节点是否遍历到
	int r = 0;
	box[r++] = u;
	int cur;
	while (r > 0) {
		cur = box[r - 1];
		//第一次遍历到
		if (!visited[cur]) {
			//把所有的子节点压栈 然后visited设置为true
			for (int ei = head[cur]; ei > 0; ei = nexts[ei]) {
				box[r++] = to[ei];
			}
			visited[cur] = true;
		}
		// 第二此遍历到这个节点 说明他的子节点都已经汇总完了 
		// 汇总孩子的信息
		else {
			r--;//弹栈
			for (int ei = head[cur]; ei > 0; ei = nexts[ei]) {
				times[cur] += times[to[ei]];
			}

		}
	}
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	// i从1开始
	for (int i = 1; i <= n; i++) {
		cin >> t;
		insert(i, t);//第i个字符串 t
	}
	setFail();
	cin >> s;
	// u 从0开始
	for (int i = 0,u=0; i < s.size(); i++) {
		u = tree[u][s[i] - 'a'];
		times[u]++;//遍历一遍字符串s  设置全部times
		//最后构建反图 然后深搜 自底向上汇总times
	}
	for (int i = 1; i <= cnt; i++) {
		addEdge(fail[i], i);
		// i号节点 指向 fail指针的节点 
		// 这里做反图  其实就是树
	}
	//遍历fail指针构建的树
	//汇总每个节点的词频
	f1(0);

	for (int i = 1; i <= n; i++) {
		cout << times[End[i]] << endl;
	}
}

#endif