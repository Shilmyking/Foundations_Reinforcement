#if 0
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<climits>
using namespace std;

static const int MAXN = 205;
int fa[MAXN];
int ans;

void build() {
    for (int i = 0; i < MAXN; i++) {
        fa[i] = i;
    }
}
int find(int i) {
    if (i != fa[i]) {
        fa[i] = find(fa[i]);
        i = fa[i];
       
    }
    return fa[i];
}

void Union(int i, int j) {
    int fi = find(i), fj = find(j);
    if (fi != fj) {
        fa[fi] = fj;
        ans--;
    }
}

class Solution {
public:

    //并查集
    int findCircleNum(vector<vector<int>>& isConnected) {
        build();
        int n = isConnected.size();
        ans = n;
        //看一侧就行  矩阵的右上角部分
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i;j++) {
                if (isConnected[i][j] == 1) {
                    Union(i, j);
                }
            }
        }
        return ans;
    }
};
#endif