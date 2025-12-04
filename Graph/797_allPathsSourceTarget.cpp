
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
#define endl "\n"

vector<vector<int>>ans;

class Solution {
public:

    // graph  邻接表 
    vector<int>path;
    //有向图  当前到next
    void dfs(vector<vector<int>>& graph, int u) {
        path.push_back(u);

        if (u == graph.size() - 1) {
            ans.push_back(path);
        }
        else {
            for (auto& nexts : graph[u]) {
                dfs(graph, nexts);
            }
        }
        path.pop_back();

    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        path.clear();
        ans.clear();
        //从0开始
        dfs(graph, 0);
        return ans;
    }

};