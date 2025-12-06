
#if 0
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

/*
给你一个 n 个点的带权无向连通图，节点编号为 0 到 n-1 ，同时还有一个数组 edges ，其中 edges[i] = [fromi, toi, weighti] 表示
在 fromi 和 toi 节点之间有一条带权无向边。最小生成树 (MST) 是给定图中边的一个子集，它连接了所有节点且没有环，而且这些边的权值和最小

请你找到给定图中最小生成树的所有关键边和伪关键边。如果从图中删去某条边，会导致最小生成树的权值和增加，那么我们就说它是一条关键边。
伪关键边则是可能会出现在某些最小生成树中但不会出现在所有最小生成树中的边。
请注意，你可以分别以任意顺序返回关键边的下标和伪关键边的下标。
*/

// 不能简单界定 还未生成整颗MST 前加入的就是关键边..
// 并查集判环

const int MAXN = 101;
const int MAXM = 203;
struct Edge {
    int start;
    int end;
    int dis;
    int id;//标识是第几条边
    Edge(int s = -1, int e = -1, int d = -1, int i = -1) :start(s), end(e), dis(d), id(i) {}
    bool operator<(const Edge& e) {
        return dis < e.dis;
    }
};
const int INF = 0x3f3f3f3f;
int fa[MAXN];
int sets;

Edge Edges[MAXM];
int ei = 0;


int find(int i) {
    return fa[i] == i ? fa[i] : fa[i] = find(fa[i]);
}

bool isSameSet(int i, int j) {
    return find(i) == find(j);
}

void Union(int i,int j) {
    fa[find(i)] = find(j);
    sets--;
}

void build(int n) {
    for (int i = 0; i < n; i++) {
        fa[i] = i;
    }
    sets = n;
}

// ban是一定不选择的原始下标
// force是一定需要选择的下标
//如果上面是 -1 的话就是没有这个设定
int MST(int n, int ban, int force) {
    build(n);
    int cost = 0;
    if (force >= 0) {
        //加入
        Union(Edges[force].start, Edges[force].end);
        cost += Edges[force].dis;
    }

    //遍历其他边 都是有序的 按照权值
    for (int i = 0; i < ei; i++) {
        if (i == force || i == ban) {
            continue;
        }
        int u = Edges[i].start, v = Edges[i].end;
        if (!isSameSet(u, v)) {
            Union(u, v);
            cost += Edges[i].dis;
            if (sets == 1) {
                return cost;
            }
        }
    }
    return sets > 1 ? INF : cost;
}

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        //建边
        ei = 0;
        for (int i = 0; i < edges.size(); i++) {
            Edges[ei++] = Edge(edges[i][0], edges[i][1], edges[i][2], i);
        }
        sort(Edges, Edges + ei);//排序
        int smallestCost = MST(n, -1, -1);
        vector<int> key;
        vector<int> must;
        //枚举 每一条边
        for (int i = 0; i < ei; i++) {
            //不包括当前边会如何
            int costWithout = MST(n, i, -1);
            //不选择 i 权值变大
            if (costWithout > smallestCost) {
                key.push_back(Edges[i].id);
            }
            else if(costWithout == smallestCost) {// 权值小 or 相等？？ 只可能相等的
                //如果它不是关键边，但我们强制先选它，最终权值依然等于smallestCost
                int costWith = MST(n, -1, i);
                if (costWith == smallestCost) {
                    must.push_back(Edges[i].id);
                }
            }
        }
        return { key,must };
    }
};

#endif