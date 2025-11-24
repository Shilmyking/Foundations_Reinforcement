
// 文本编辑器，FHQ-Treap实现区间移动
// 一开始文本为空，光标在文本开头，也就是1位置，请实现如下6种操作
// Move k     : 将光标移动到第k个字符之后，操作保证光标不会到非法位置
// Insert n s : 在光标处插入长度为n的字符串s，光标位置不变
// Delete n   : 删除光标后的n个字符，光标位置不变，操作保证有足够字符
// Get n      : 输出光标后的n个字符，光标位置不变，操作保证有足够字符
// Prev       : 光标前移一个字符，操作保证光标不会到非法位置
// Next       : 光标后移一个字符，操作保证光标不会到非法位置
// Insert操作时，字符串s中ASCII码在[32,126]范围上的字符一定有n个，其他字符请过滤掉
// 测试链接 : https://www.luogu.com.cn/problem/P4008

//FHQ-Treap 实现区间移动

#if 0
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<climits>


using namespace std;
#define endl "\n"

const int MAXN = 2e6 + 2;
const int INF = 0x3f3f3f3f;
int head = 0;
int cnt = 0;
char key[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
//最好也可以是 int 类型  没有归一化的必要  double反而耗内存  效率低
int pr[MAXN];//尬住了 是double类型

char ans[MAXN];
int ansi;

void up(int i) {
	sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
}
int init(char ch) {
	key[++cnt] = ch;
	sz[cnt] = 1;
	pr[cnt] = (rand() % INF);
	return cnt;
}

//根据排名进行 split  --->维护inOrder序列的顺序
// l、r上一次遍历到(符合rank)的节点..
// i当前节点i为头的子树去查找排名为rank的节点
// 大于rank的 去右树
// 小于等于 rank的去左树
void split(int l, int r, int i, int rank) {
	if (i == 0) {
		ls[r] = rs[l] = 0;
	}
	else {
		//当前位置的rank小于等于传入的参数rank 也就是被分配到左树
		if (sz[ls[i]] + 1 <= rank) {
			rs[l] = i;
			split(i, r, rs[i], rank - sz[ls[i]] - 1);
		}
		else {
			//当前位置的rank 大于 参数rank
			// 去右树
			ls[r] = i;
			split(l, i, ls[i], rank);
		}
		up(i);
	}
}

//按照rank进行排序 ---> 优先级大的当爹
//返回当爹的节点
int merge(int l, int r) {
	if (l == 0 || r == 0) {
		return l + r;//一方为0 ---返回
	}
	if (pr[l] >= pr[r]) {
		// 维持顺序 BSTree的性质  
		rs[l] = merge(rs[l], r);
		up(l);
		return l;
	}
	else {
		ls[r] = merge(l, ls[r]);
		up(r);
		return r;
	}
}

//中序收集 打印
void inOrder(int i) {
	if (i != 0) {
		inOrder(ls[i]);
		ans[ansi++] = key[i];
		inOrder(rs[i]);
	}
}

int t,len;
int pos = 0;
//舍弃使用 s 这题输入有点搞
string op;

//光标处插入 len长度的s 光标位置不变
void Insert() {
	split(0, 0, head, pos);//分为 <=pos  >pos的两颗子树
	int l = rs[0], r = ls[0];
	//分裂之后 一个一个和左树merge
	for (int i = 0; i < len; i++) {
		//统一用 cin  不能getchar
		char ch;
		cin.get(ch);
		while ((ch < 32) || (ch > 126)) {
			//必须使用  cin.get(ch)  cin会吞掉空格
			cin.get(ch);
		}
		l = merge(l, init(ch));
	}
	head = merge(l, r);
}

//删除光标后 len长度的字符
void Delete() {
	split(0, 0, head, pos + len);
	int l = rs[0], r = ls[0];
	//分裂出 后面的部分
	//再分裂前面的部分
	split(0, 0, l, pos);
	int ll = rs[0];
	head = merge(ll, r);
}

//打印光标后 len长度的字符
void Get() {
	split(0, 0, head, pos + len);
	int l = rs[0], r = ls[0];

	split(0, 0, l, pos);
	int ll = rs[0], lr = ls[0];
	
	ansi = 0;
	inOrder(lr);//收集打印

	head = merge(merge(ll, lr),r);
	for (int i = 0; i < ansi; i++) {
		cout << ans[i];
	}
	cout << endl;
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	srand(time(0));
	cin >> t;

	for (int i = 0; i < t; i++) {
		//t 条指令
		cin >> op;
		if (op == "Move") {
			cin >> pos;
		}
		else if (op == "Insert") {
			cin >> len;
			//光标出插入 len长度的s 光标位置不变
			Insert();
		}
		else if (op == "Delete") {
			cin >> len;
			//删除光标后 len长度的字符
			Delete();
		}
		else if (op == "Get") {
			cin >> len;
			//打印光标后 len长度的字符
			Get();
		}
		else if (op == "Prev") {
			pos--;
		}
		else if (op == "Next") {
			pos++;
		}

	}
}

#endif