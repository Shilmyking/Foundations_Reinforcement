
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<climits>
using namespace std;


class Solution {
public:
    bool ans = true;
    // 0--> a  z-->25
    int fa[27];

    void build() {
        for (int i = 0; i < 26;i++) {
            fa[i] = i;
        }
    }
    
    int find(int i) {
        return fa[i] == i ? fa[i] : fa[i] = find(fa[i]);
    }
    
    bool isSameSet(int i, int j) {
        return find(i) == find(j);
    }

    void Union(int i,int j) {
        int fi = find(i), fj = find(j);
        if (fi != fj) {
            fa[fi] = fj;
        }
    }
    // 都是小写字母
    bool equationsPossible(vector<string>& equations) {
        build();
        int n = equations.size();
        for (int i = 0; i < n; i++) {
            if (equations[i][1] == '=') {
                int u = equations[i][0] - 'a';
                int v = equations[i][3] - 'a';
                Union(u, v);
            }
        }
        for (int i = 0; i < n; i++) {
            if (equations[i][1] == '!') {
                int u = equations[i][0] - 'a';
                int v = equations[i][3] - 'a';
                if (isSameSet(u,v)) {
                    return false;
                }
            }
        }
        return true;
    }

};