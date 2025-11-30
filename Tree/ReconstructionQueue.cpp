
// 重建队列
// 一共n个人，每个人有(h, k)两个数据，数据h表示该人的身高
// 数据k表示该人的要求，站在自己左边的人中，正好有k个人的身高大于等于自己的身高
// 请你把n个人从左到右进行排列，要求每个人的要求都可以满足
// 返回其中一种排列即可，本题的数据保证一定存在这样的排列
// 测试链接 : https://leetcode.cn/problems/queue-reconstruction-by-height/

#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include<vector>

using namespace std;

const int MAXN = 2001;

int cnt = 0;
int head = 0;

int key[MAXN];
int height[MAXN];
int lt[MAXN];
int rt[MAXN];
int value[MAXN];
int sz[MAXN];

void up(int i) {
    sz[i] = sz[lt[i]] + sz[rt[i]] + 1;
    height[i] = std::max(height[lt[i]], height[rt[i]]) + 1;
}

int leftRoate(int i) {
    int r = rt[i];
    rt[i] = lt[r];
    lt[r] = i;

    up(i);
    up(r);
    return r;
}

int rightRoate(int i) {
    int l = lt[i];
    lt[i] = rt[l];
    rt[l] = i;

    up(i);
    up(l);
    return l;
}

int maintain(int i) {
    int hl = height[lt[i]], hr = height[rt[i]];
    if (hl - hr > 1) {
        int l = lt[i];
        if (height[lt[l]] >= height[rt[l]]) {
            i = rightRoate(i);
        }
        else {
            lt[i] = leftRoate(lt[i]);
            i = rightRoate(i);
        }
    }
    else if (hr - hl > 1) {
        int r = rt[i];
        if (height[rt[r]] >= height[lt[r]]) {
            i = leftRoate(i);
        }
        else {
            rt[i] = rightRoate(rt[i]);
            i = leftRoate(i);
        }
    }
    //无需 up了  leftRoate/rightRoate 调用的时候就是 up之后才返回的
    return i;
}

// i：此时的节点编号
// rank 在当前子树想要占据第几位   目标插入位置（即前面的元素个数，也就是 k）
// num 当前的高度
// index：前面正好有多少大于等于自己的
int add(int i, int rank, int num, int index) {
    if (i == 0) {//当前位置插入
        key[++cnt] = num;
        value[cnt] = index;
        height[cnt] = sz[cnt] = 1;
        return cnt;//给父节点返回当前的 cnt
    }
    //下面根据左孩子的这颗子树的节点个数判断往左还是往右
    // 因为是中序遍历一定是 左树先打印完才轮到 cur 和右树
    // 所以说 index 刚好等于 sz[lt[i]]的时候 也是要插入到左树  只不过应该是在最后一个位置了

    //去左侧  相等的时候也是 到左侧添加节点
    // rank == sz[lt[i]] --->前驱
    if (rank <= sz[lt[i]]) {
        lt[i] = add(lt[i], rank, num, index);
    }
    else {
        //考虑右树  如果右树
        //去右侧就是要减去 左树+当前位置的节点数目
        // rank == sz[lt[i]]+1 -->做后继

        rt[i] = add(rt[i], rank - sz[lt[i]] - 1, num, index);
    }
    up(i);
    return maintain(i);
}

void add(int num, int index) {
    head = add(head, index, num, index);
}


int fl = 0;
//中序遍历
void inOrder(vector<vector<int>>& ans, int i) {
    if (i == 0) { return; }
    inOrder(ans, lt[i]);
    // cur
    ans[fl][0] = key[i];
    ans[fl++][1] = value[i];

    inOrder(ans, rt[i]);
}

void clear() {
    memset(sz + 1, 0, cnt * sizeof(int));
    memset(lt + 1, 0, cnt * sizeof(int));
    memset(rt + 1, 0, cnt * sizeof(int));
    memset(key + 1, 0, cnt * sizeof(int));
    memset(height + 1, 0, cnt * sizeof(int));
    memset(value + 1, 0, cnt * sizeof(int));

    cnt = 0;
    head = 0;
    fl = 0;
}

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        clear();

        vector<vector<int>>ans(people.size(), vector<int>(2));

        std::sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) {//值相等  小的优先  也就是升序排列
                return a[1] < b[1];
            }
            return a[0] > b[0];//降序排列  高的在前
            });

        for (auto& v : people) {
            add(v[0], v[1]);
        }

        inOrder(ans, head);

        return ans;
    }
};