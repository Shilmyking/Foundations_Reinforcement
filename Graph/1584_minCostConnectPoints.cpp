

/// 贪心  +  MST？
// 数据量小 O(n^2)也能过

#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;

const int MAXN = 1e3 + 2;
int fa[MAXN];
int sets;

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

int dist(int a, int b, int c, int d) {
    return std::abs(a - c) + std::abs(b - d);
}

// k算法
struct Edge {
    int start;
    int end;
    int dis;
    Edge(int s=-1,int e=-1,int d=-1):start(s),end(e),dis(d){}
    //小根堆
    bool operator<(const Edge& e)const {
        return dis < e.dis;
    }
};
const int MAXM = MAXN * MAXN;
Edge edges[MAXM];
int filled = 0;

void build() {
    for (int i = 0; i < MAXN; i++) {
        fa[i] = i;
    }
    filled = 0;
    //fill(edges, edges + MAXM, Edge());
}


class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int ans = 0;
        int n = points.size();//点的个数
        build(); sets = n;
 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    edges[filled++] = Edge(i, j,
                        dist(points[i][0], points[i][1], points[j][0], points[j][1]));
                }
            }
        }

        sort(edges, edges + filled);

        for (int i = 0; i < filled; i++) {
            Edge top = edges[i];
            int start = top.start, end = top.end, dis = top.dis;
            if (!isSameSet(start, end)) {
                Union(start, end);
                ans += dis;
                if (sets == 1) {
                    break;
                }
            }

        }
        return ans;
    }
};