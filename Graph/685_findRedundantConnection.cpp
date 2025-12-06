
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

const int MAXN = 1e3 + 4;
const int INF = 0x3f3f3f3f;
int fa[MAXN];
int sets;

int parent[MAXN];

int find(int i) {
    return fa[i] == i ? fa[i] : fa[i] = find(fa[i]);
}

bool isSameSet(int i, int j) {
    return find(i) == find(j);
}

void Union(int i, int j) {
    fa[find(i)] = find(j);
    sets--;
}

void build(int n) {
    // 1-based
    for (int i = 0; i <= n; i++) {
        fa[i] = i;
    }
    sets = n;
}


class Solution {
public:
    /*
   该图由一个有着 N 个节点 (节点值不重复 1, 2, ..., N) 的树及一条附加的边构成。
    附加的边的两个顶点包含在 1 到 N 中间，这条附加的边不属于树中已存在的边。
    这说明题目中的图原本是是一棵树，只不过在不增加节点的情况下多加了一条边！
    还有 若有多个答案，返回最后出现在给定二维数组的答案。这说明在两天边都可以删除的情况下，要删顺序靠后的！
    */
    // 作图 画出三种情况 ！！！
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        memset(parent, 0, sizeof(parent));
        vector<int>edge1;//冲突的第一条边  parent[v] + v
        vector<int>edge2;//冲突的第二条边
        bool hasDual = false;
        for (auto& e : edges) {
            int u = e[0],v = e[1];
            //找到入度为2的节点
            if (parent[v] != 0) {
                //当前边和 parent[v]->v 让v节点入度为2 
                edge1 = { parent[v],v };
                edge2 = e;
                hasDual = true;
                break;//只存在一条多余的边 ，这里找到了
            }
            else {
                parent[v] = u;
            }
        }
        //UnionFind 判环
        build(n);
        for (auto& edge : edges) {
            //删除edge2
            // 如果删除edge2还存在环证明 edge2 没问题 edge1有问题
            if (hasDual && edge == edge2) {
                continue;
            }
            int u = edge[0], v = edge[1];
            if (isSameSet(u, v)) {
                // 既有入度为2，又有环 (且删了 edge2 后环依然存在)
                // 说明 edge2 不是导致环的原因，edge1 才是同时构成环且导致冲突的边
                return hasDual ? edge1 : edge;
                //存在环 没有入度为2的节点
            }
            Union(u, v);
        }
        // 存在入度为2  删除之后无环 --->edge2作祟 
        return edge2;
    }
};