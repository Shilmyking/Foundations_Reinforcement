
// 并查集  如果后续出现 加入一条边  冲突===>环
// 记录答案

#if 0
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<climits>
using namespace std;

const int MAXN = 1e3 + 2;
int fa[MAXN];
vector<int>ans(2);
// 记录每一次 违反情况的时候 --->成环
//  然后继续操作

void build() {
    for (int i = 0; i < MAXN; i++)
    {
        fa[i] = i;
    }
}

int find(int i) {
    return fa[i] != i ? fa[i] = find(fa[i]) : fa[i];
}

bool isSameSet(int i, int j) {
    return find(i) == find(j);
}

void Union(int i, int j) {
    int fi = find(i), fj = find(j);
    if (fi != fj) {
        fa[fi] = fj;
    }
    else {
        //违规
        ans[0] = i;
        ans[1] = j;
    }
}

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        build();
        for (int i = 0; i < n; i++) {
            Union(edges[i][0], edges[i][1]);
        }
        return ans;
    }
};
#endif