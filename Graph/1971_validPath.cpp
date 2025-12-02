
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<climits>
using namespace std;

const int MAXN = 2e5 + 5;
int fa[MAXN];
int N;

void build() {
    for (int i = 0; i < N; i++) {
        fa[i] = i;
    }
}

int find(int i) {
    return fa[i] == i ? fa[i] : fa[i] = find(fa[i]);
}

bool isSameSet(int l, int r) {
    return find(l) == find(r);
}

void Union(int l, int r) {
    fa[find(l)] = find(r);
}

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        N = n;
        build();
        for (auto& edge : edges) {
            Union(edge[0], edge[1]);
        }
        return isSameSet(source, destination);
    }
};