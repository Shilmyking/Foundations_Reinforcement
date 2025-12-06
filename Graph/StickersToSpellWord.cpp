
// 贴纸拼词
// 我们有 n 种不同的贴纸。每个贴纸上都有一个小写的英文单词。
// 您想要拼写出给定的字符串 target ，方法是从收集的贴纸中切割单个字母并重新排列它们
// 如果你愿意，你可以多次使用每个贴纸，每个贴纸的数量是无限的。
// 返回你需要拼出 target 的最小贴纸数量。如果任务不可能，则返回 -1
// 注意：在所有的测试用例中，所有的单词都是从 1000 个最常见的美国英语单词中随机选择的
// 并且 target 被选择为两个随机单词的连接。
// 测试链接 : https://leetcode.cn/problems/stickers-to-spell-word/

#if 0
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include<unordered_map>
using namespace std;

// 很妙  bfs 就像是 最短路径问题 只是 路径代价恰好都是1

const int MAXN = 402;
static vector<vector<string>>graph(26, vector<string>());
unordered_set<string>visited;//保证这个str 从未被访问过 不再重复入队列
string que[MAXN];
int l = 0, r = 0;

void build() {
    for (int i = 0; i < 26; i++) {
        graph[i].clear();
    }
    visited.clear();
    l = r = 0;
}

class Solution {
public:

    int minStickers(vector<string>& stickers, string target) {
        build();
        std::sort(target.begin(), target.end());
        // 当前建立邻接表 +排序
        for (string& str : stickers) {
            //排好序  贪心
            sort(str.begin(), str.end());

            for (int i = 0; i < str.size(); i++) {
                //不要重复添加
                if (i == 0 || str[i] != str[i - 1]) {
                    graph[str[i] - 'a'].push_back(str);
                }
            }
        }
        //放的都是target or 后续削减到的程度
        que[r++] = target;
        visited.insert(target);

        int level = 1;//初始为1
        //层序遍历
        while (l < r) {
            //必须这样做 层序遍历
            int size = r - l;//这一层做 r-l次 
            for (int i = 0; i < size; i++) {
                // 每一层根据前缀考虑最优筛选  贪心
                string cur = que[l++];

                for (auto& word : graph[cur[0] - 'a']) {
                    //都去减完 然后 入队列(没进入队列的话)
                    string after = minus(cur, word);
                    if (after == "") {
                        return level;
                    }
                    if (visited.find(after) == visited.end()) {
                        que[r++] = after;
                        visited.insert(after);
                    }
                }
            }
            level++;
        }
        return -1;

    }

    //targte - now
    string minus(string& target, string& now) {
        string after;
        int n = target.size(), m = now.size();
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (target[i] == now[j]) {
                i++, j++;//一样就抵消了
            }
            else if (target[i] > now[j]) {
                j++;
            }
            else {//tagget[i]<now[j]
                after += target[i++];
            }
        }
        while (i < n) {
            after += target[i++];
        }
        return after;
    }
};
#endif