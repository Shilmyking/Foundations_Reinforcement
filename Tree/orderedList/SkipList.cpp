
// 跳表的实现
// 实现一种结构，支持如下操作，要求单次调用的时间复杂度O(log n)
// 1，增加x，重复加入算多个词频
// 2，删除x，如果有多个，只删掉一个
// 3，查询x的排名，x的排名为，比x小的数的个数+1
// 4，查询数据中排名为x的数
// 5，查询x的前驱，x的前驱为，小于x的数中最大的数，不存在返回整数最小值
// 6，查询x的后继，x的后继为，大于x的数中最小的数，不存在返回整数最大值
// 所有操作的次数 <= 10^5
// -10^7 <= x <= +10^7
// 测试链接 : https://www.luogu.com.cn/problem/P3369

#if 0
#include<iostream>
#include<algorithm>
#include<cstring>
#include<climits>
#include<time.h>

using namespace std;

//使用 int 足够 long long 稍微拖慢时间  ...  内存用的也多
//#define int long long  
#define endl "\n"
const int MAXN = 1e5 + 5;
const int MAXL = 20;
const int INF = 0x3f3f3f3f;

int head = 1;//固定head  代码清晰点
int cnt = 1;//0代表跳表的最后一个节点   1是第一个节点
int key[MAXN];
int Count[MAXN];//词频
int level[MAXN];
int nexts[MAXN][MAXL + 1];
int len[MAXN][MAXL + 1];


//初始化
void build() {
    //初始化第一个节点 层数的 值
    cnt = 1;
    key[cnt] = -INF;
    level[cnt] = MAXL;
}

//清除脏数据
void clear() {
    memset(key, 0, sizeof(key));
    memset(Count, 0, sizeof(Count));
    memset(level, 0, sizeof(level));
    memset(nexts, 0, sizeof(nexts));
    memset(len, 0, sizeof(len));
    cnt = 1;
}

int randLevel() {
    int ans = 1;
    while ((rand() / double(RAND_MAX)) < 0.5) {
        ans++;
    }
    return std::min(ans, MAXL);
}

//查找num这个key是否存在
// i:当前到节点编号
// h:当前层的高度
// num：查询的键值
int find(int i, int h, int num) {
    //从最顶开始向右走
    //当前层下 不到到达最右  下一个节点的键值不要超过num
    while (nexts[i][h] != 0 && key[nexts[i][h]] < num) {
        i = nexts[i][h];
    }
    //当前层走不动了  可能到达0 or 就是无法继续往右了
    if (h == 1) {//来到最底层
        //如果还存在节点 而且值就是num 直接返回编号就是了
        if (nexts[i][h] != 0&&key[nexts[i][h]] == num) {
            return nexts[i][h];
        }
        else {
            //下一位数值不是num  说明不存在这个键值
            return 0;//不存在
        }
    }
    return find(i, h - 1, num);//继续去底下一层   
    //i当然还是这个i 高层都存在这个节点低层也肯定存在
}

//加词频 
// 确认了跳表内存在节点  那就直接加词频
void addCount(int i, int h, int num) {
    //还是继续在当前层往右深入  
    while (nexts[i][h] != 0 && key[nexts[i][h]] < num) {
        i = nexts[i][h];
    }//出循环 说明遇到0 or 更大的值
    if (h == 1) {
        //到达底层  一定能找到节点  Count
        Count[nexts[i][h]]++;//词频
    }
    else {
        //去下一层
        addCount(i, h - 1, num);
    }
    //只要跨过这个节点的指针都需要 len ++
    len[i][h]++;
}

//加节点
// 逻辑最复杂 需要每一层都调整 插入的位置的左右两侧的指针  
// 这个过程需要底层向上汇报 到底存在多少节点
// 需要直到 num的前驱结点 到 num的后继节点存在多少节点
// 然后  在最低层就是 插入的节点就管理后继节点的个数   前驱结点管理 (总结点数目-后继节点的数目)
// 其实在更上层的也是这个逻辑 只是不是前驱 or 后继 

// i:当前的节点编号   h：层高  j：插入节点的编号
// 返回值：从i号节点出发，直到把空间编号为j的节点插入，底层总共有多少数字比key[j]小
// 返回值很重要，因为上游需要这个信息来改动指针的长度信息
int addNode(int i, int h, int j) {
    int rightCnt = 0;//向右滑行遇到多少个节点
    //当前层还是向右滑行 不能往右为止
    while (nexts[i][h] != 0 && key[nexts[i][h]] < key[j]) {
        rightCnt += len[i][h];//这个指针滑过多少节点
        i = nexts[i][h];
    }
    if (h == 1) {
        //  在最底层 指针改向
        nexts[j][h] = nexts[i][h];
        nexts[i][h] = j;
        len[j][h] = Count[nexts[j][h]];
        len[i][h] = Count[nexts[i][h]];
        return rightCnt;//向上返回滑过多少节点
    }
    else {//还需要往下递归
        // 在当前层已经是无法往右滑了   
        // 收集数据 得到
        int downCnt = addNode(i, h - 1, j);
        if (h > level[j]) {
            len[i][h]++;// 当前层没有j节点 直接加指针的长度即可
        }
        else {
            nexts[j][h] = nexts[i][h];
            nexts[i][h] = j;
            
            // 其实下面两句顺序反一下 会好理解得多  不影响最终结果
            
            // 新插入的这个为止 后续的节点数目就是 总结点数目
            // 减去向右到 j 节点插入的为止 滑过多少个节点   也减去 Count[j]
            len[j][h] = (len[i][h] + 1) - downCnt - Count[j];
            len[i][h] = downCnt + Count[j];//滑过的节点数 + j的词频
        }
        //最后返回 当前层向右滑过的节点数目 + 下级所有滑过的节点数目和
        return rightCnt + downCnt;
    }
}

//插入一个数字
void add(int num) {
    if (find(head, MAXL, num) > 0) {
        //加词频
        addCount(head,MAXL,num);
    }
    else {
        key[++cnt] = num;
        Count[cnt] = 1;
        level[cnt] = randLevel();
        addNode(head, MAXL, cnt);
    }
}

//减词频
//一定存在这个节点才去调用
void removeCount(int i, int h, int num) {
    while (nexts[i][h] != 0 && key[nexts[i][h]] < num) {
        i = nexts[i][h];
    }
    if (h == 1) {
        Count[nexts[i][h]]--;
    }
    else {
        removeCount(i, h - 1, num);
    }
    len[i][h]--;//底下 or 指向的下一位 减少了一位词频
}

//删除节点
// 一定存在节点才去调用
void removeNode(int i, int h, int j) {
    if (h < 1) { return; }//递归basecase
    while (nexts[i][h] != 0 && key[nexts[i][h]] < key[j]) {
        i = nexts[i][h];
    }

    //这一层不存在 j节点的话
    if (h > level[j]) {
        len[i][h]--;//底下跨过的
    }
    else {//只要这一层存在这个节点  到达这里 下一位一定是j
        //next[i][h]一定是 j
        //设置为找不到了  +  修正 len
        nexts[i][h] = nexts[j][h];
        len[i][h] += len[j][h] - 1;
    }
    //到更底层修改
    removeNode(i, h - 1, j);
}

//删除
void remove(int num) {
    int j = find(head, MAXL, num);
    if (j > 0) {
        //说明存在
        if (Count[j] > 1) {
            removeCount(head, MAXL, num);
        }
        else {
            removeNode(head, MAXL, j);
        }
    }
}

// 小于num的数字存在多少个
int small(int i, int h, int num) {
    int curLevelCount = 0;
    while (nexts[i][h] != 0 && key[nexts[i][h] ]< num) {
        curLevelCount += len[i][h];
        i = nexts[i][h];
    }//当前层滑过的有多少
    if (h == 1) {
        return curLevelCount;
    }
    else {
        return curLevelCount + small(i, h - 1, num);
    }
}

// num排第几大
int getRank(int num) {
    return small(head, MAXL, num) + 1;
}

// 在当前节点 当前层数下 往右找 第x大的数字是谁
int index(int i, int h, int x) {
    int curLevelCount = 0;
    while (nexts[i][h] != 0 && curLevelCount + len[i][h] < x) {
        curLevelCount += len[i][h];
        i = nexts[i][h];
    }
    if (h == 1) {
        return key[nexts[i][h]];
    }
    else {
        return index(i, h - 1, x - curLevelCount);
    }
}

//查询整体第x大
int index(int x) {
    return index(head, MAXL, x);
}

//查询 pre的前驱 小于num的 最大的那个数
int pre(int i, int h, int num) {
    while (nexts[i][h] != 0 && key[nexts[i][h]] < num) {
        i = nexts[i][h];
    }
    //将尽可能得往右侧找
    if (h == 1) {
        //根本没有往右的机会
        return i == head ? -INF : key[i];
    }
    else {
        return pre(i, h - 1, num);
    }
}

//查询num的前驱
int pre(int num) {
    return pre(head, MAXL, num);
}

//查询num的后继节点 比num大的最小的
int post(int i, int h, int num) {
    while (nexts[i][h] != 0 && key[nexts[i][h]] < num) {
        i = nexts[i][h];
    }
    if (h == 1) {
        //如果真能找到 那下一个数字注定是 num
        if (nexts[i][h] == 0) {
            return INF;//不存在   根本没有比
        }
        // 如果下一个数字就是大于 num的 说明根本不存在 num  返回就是了 
        // 如果存在num这个数  如果还存在下一个返回就是了  不存在就返回INF
        if (key[nexts[i][h]] > num) {
            return key[nexts[i][h]];
        }
        //存在 num  下一个就是
        i = nexts[i][h];
        return nexts[i][h] == 0 ? INF : key[nexts[i][h]];
    }
    else {
        return post(i, h - 1, num);
    }
}

int post(int num) {
    return post(head, MAXL, num);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(nullptr));
    build();

    int n;
    cin >> n;
    for (int i = 0, op, num; i < n; i++) {
        cin >> op >> num;
        if (op == 1) {
            add(num);
        }
        else if (op == 2) {
            remove(num);
        }
        else if (op == 3) {
            cout << getRank(num) << endl;
        }
        else if (op == 4) {
            cout << index(num) << endl;
        }
        else if (op == 5) {
            cout << pre(num) << endl;
        }
        else {
            cout << post(num) << endl;
        }
    }
    clear();
}
#endif