

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<climits>
using namespace std;


class Solution {
private:
    static const int MAXN = 2e3 + 3;
    static const int MAXM = 5e3 + 2;
    int head[MAXN];
    int nexts[MAXM];
    int to[MAXM];
    int cnt = 0;
    
    int queue[MAXN];
    int l=0, r = 0;
    
    int indergee[MAXN];
    void build() {
        memset(head, 0,  sizeof(head));
        memset(indergee, 0, sizeof(indergee));
        cnt = 0;
        l = r = 0;
    }
    void addEdge(int u, int v) {
        nexts[++cnt] = head[u];
        to[cnt] = v;
        head[u] = cnt;
    }
public:

    void prepare(const vector<vector<int>>& prerequisites) {
        build();
        for (auto& v : prerequisites) {
            addEdge(v[1], v[0]);//  后一个指向前一个
            indergee[v[0]]++;
        }
    }
    bool tuopu(int numCourses) {
        for (int i = 0; i < numCourses; i++) {
            if (indergee[i] == 0) {
                queue[r++] = i;
            }
        }
        //拓扑
        while (l < r) {
            int top = queue[l++];
            for (int ei = head[top]; ei > 0; ei = nexts[ei]) {
                int v = to[ei];
                if (--indergee[v] == 0) {
                    queue[r++] = v;
                }
            }
        }
        return r == numCourses;
    }

    // 总课程数  0~numCourses-1   
    //  边应该是 prerequisites[i][0] <--- prerequisites[i][1] 这样表示
    // 要修 0 必须先修 1
    bool canFinish1(int numCourses, vector<vector<int>>& prerequisites) {
        prepare(prerequisites);
        return tuopu(numCourses);
    }


public:

    void prepare1(const vector<vector<int>>& prerequisites, vector<vector<int>>&matrix,vector<int>&degree) {
        // 邻接表
        // 下标就是对应节点  里面存储的内容就是 可以到达的节点  
        for (auto& v : prerequisites) {
            matrix[v[1]].push_back(v[0]);//v[1]位置存储 到达的节点v[0]
            degree[v[0]]++;
        }
    }

    bool tuopu1(int numCourses, vector<vector<int>>& matrix, vector<int>& degree) {
        int now = 0;
        vector<int>que;
        for (int i = 0; i < numCourses; i++) {
            if (degree[i] == 0) {
                que.push_back(i);
                now++;
            }
        }
        while (!que.empty()) {
            int top = que.back();
            que.pop_back();
            for (int i = 0; i < matrix[top].size(); i++) {
                int v = matrix[top][i];
                if (--degree[v] == 0) {
                    que.push_back(v);
                    now++;
                }
            }
        }
        return now == numCourses;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>>matrix(numCourses);
        vector<int>degree(numCourses);
        prepare1(prerequisites, matrix, degree);
        return tuopu1(numCourses, matrix, degree);
    }

};