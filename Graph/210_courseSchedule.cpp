
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<climits>
using namespace std;



class Solution {
public:
    int cnt;
    struct Edge {
        int next;
        int to;
    };

    // u->v
    void addEdge(vector<int>& head, vector<Edge>& edges, int u, int v) {
        edges[cnt].next = head[u]; // 新边的 next 指向旧的头
        edges[cnt].to = v;
        head[u] = cnt++;           // 更新头，指向新添加的边
    }
    //prerequisites[]  前一个数字依赖于后一个数字
    void directGraph(vector<int>& head, vector<Edge>& edges, vector<int>& indegree, const vector<vector<int>>& prerequisites) {
        for (const auto& edge : prerequisites) {
            addEdge(head, edges, edge[1], edge[0]);
            ++indegree[edge[0]];
        }
    }

    //这里的节点从0开始的
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        //prerequisites 二维数组  内部固定的两个元素  所以 边就是 prerequisites.size() + 1
        int N = numCourses;
        int M = prerequisites.size() + 1;
        cnt = 1;
        vector<int>head(N);
        vector<int>indegree(N);
        vector<Edge>edges(M);

        directGraph(head, edges, indegree, prerequisites);//建图

        //使用静态数组模拟队列
        vector<int>queue(numCourses);
        int l = 0, r = 0;
        for (int i = 0; i < numCourses; i++) {//最初indegree是0的都入队列
            if (indegree[i] == 0) {
                queue[r++] = i;
            }
        }
        int cnt = 0;//最后还需要判断一下能不能拓扑排序  也就是没有环的话  最后全部都能入队列
        while (l < r) {
            int cur = queue[l++];
            cnt++;
            //cur 就是节点的现在需要遍历一边所有边的那个节点
            for (int ei = head[cur]; ei > 0; ei = edges[ei].next) {
                if (--indegree[edges[ei].to] == 0) {
                    queue[r++] = edges[ei].to;//to入度到达0了
                }
            }
        }
        return cnt == numCourses ? queue : vector<int>();
    }
};

#if 0

static const int MAXN = 2e3 + 2;
static const int MAXM = MAXN * MAXN;
int head[MAXN];
int nexts[MAXM];
int to[MAXM];
int cnt = 0;
int indegree[MAXN];
int queue[MAXN];
int l = 0, r = 0;

void build() {
    memset(head, 0, sizeof(head));
    memset(indegree, 0, sizeof(indegree));
    cnt = 0;
    l = r = 0;
}

void addEdge(int u, int v) {
    nexts[++cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt;
}

class Solution {


    void prePare(const vector<vector<int>>& prerequisites) {
        build();
        for (auto& v : prerequisites) {
            addEdge(v[1], v[0]);
            indegree[v[0]]++;
        }
    }

    vector<int> tuopu(int numCourses) {
        vector<int>ans; ans.reserve(numCourses);
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                ans.push_back(i);
                queue[r++] = i;
            }
        }

        while (l < r) {
            int top = queue[l++];
            for (int ei = head[top]; ei > 0; ei = nexts[ei]) {
                int v = to[ei];
                if (--indegree[v] == 0) {
                    queue[r++] = v;
                    ans.push_back(v);
                }
            }
        }

        return ans.size() == numCourses ? ans : vector<int>();
    }

public:
    //还是一样的思路   一样的依赖关系      [0]<-----[1]
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        prePare(prerequisites);
        return tuopu(numCourses);
    }

};
#endif