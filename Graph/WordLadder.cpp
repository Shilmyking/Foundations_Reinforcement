
// 单词接龙
// 字典 wordList 中从单词 beginWord 和 endWord 的 转换序列
// 是一个按下述规格形成的序列 beginWord -> s1 -> s2 -> ... -> sk ：
// 每一对相邻的单词只差一个字母。
// 对于 1 <= i <= k 时，每个 si 都在 wordList 中
// 注意， beginWord 不需要在 wordList 中。sk == endWord
// 给你两个单词 beginWord 和 endWord 和一个字典 wordList
// 返回 从 beginWord 到 endWord 的 最短转换序列 中的 单词数目
// 如果不存在这样的转换序列，返回 0 。
// 测试链接 : https://leetcode.cn/problems/word-ladder/

#if 0

#include<iostream>
#include<vector>
#include<queue>
#include<functional>
#include<list>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>

using namespace std;

class Solution {
public:

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string>dict;
        for (auto& v : wordList) {
            dict.insert(v);
        }
        if (dict.find(endWord) == dict.end()) {
            return 0;
        }
        unordered_set<string>smallLevel;
        unordered_set<string>bigLevel;
        unordered_set<string>nextLevel;
        smallLevel.insert(beginWord);
        bigLevel.insert(endWord);
        for (int len = 2; !smallLevel.empty(); len++) {
            for (auto& word : smallLevel) {
                // 每个在smallLevel内的单词 继续去展开
                string Copy = word;
                for (int j = 0; j < word.size(); j++) {
                    char old = word[j];
                    // 不要漏掉 z  change<=z!!
                    for (char change = 'a'; change <= 'z'; change++) {

                        // 每个位置 每个字符都换一次 但是不要和原来的重复
                        if (old != change) {

                            //无法修改？？  const 修饰了
                            Copy[j] = change;
                            if (bigLevel.find(Copy) != bigLevel.end()) {
                                //找到了这个Copy单词
                                return len;
                            }

                            //dict 内存在这个单词  不要多次展开 + 放到nextLevel 用于后续继续展开
                            if (dict.find(Copy) != dict.end()) {
                                dict.erase(Copy);
                                nextLevel.insert(Copy);
                            }

                        }

                    }
                    Copy[j] = old;//需要换回原本的样子
                }
                
            }
            // smallLevel展开完了
            if (nextLevel.size() <= bigLevel.size()) {
                smallLevel = nextLevel;//继续展开更小的一方
            }
            else {
                smallLevel = bigLevel;
                bigLevel = nextLevel;
            }
            nextLevel.clear();
        }
        return 0;
    }
};

#endif