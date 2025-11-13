
#include<string>
using namespace std;

//https://leetcode.cn/problems/simplify-path


class Solution {
public:
    static const int N = 3e3 + 5;
    char Stack[N];
    int Size = 0;
    string simplifyPath(string path) {
        //第一个字符一定为/
        Stack[Size++] = '/';//要你去初始化一下
        int i = 1;
        int n = path.size();
        while (i < n) {
            while (i < n && path[i] == '/') {
                i++;
            }//跳过开头的所有 /
            if (i == n)break;

            //提取 '/'和'/'之间的所有内容
            string component;
            while (i < n && path[i] != '/') {
                component += path[i];
                i++;
            }
            //讨论 component的内容
            if (component == "..") {
                //弹出上一项
                if (Size > 0) {
                    while (Size > 0 && Stack[Size - 1] != '/') {
                        Size--;
                    }
                    if (Size > 1) {
                        //还需要弹出 /  但是保留根目录的 /
                        Size--;
                    }
                }
            }
            else if (component == "." || component == "") {
                continue;
            }
            else {
                if (Size == 0) {
                    Stack[Size++] = '/';
                }
                else if (Stack[Size - 1] != '/') {
                    //栈顶不是 '/'加上分隔符
                    Stack[Size++] = '/';
                }
                for (char& c : component) {
                    Stack[Size++] = c;
                }
            }

        }
        string ans;
        for (int i = 0; i < Size; i++) {
            ans += Stack[i];
        }
        return ans != "" ? ans : "/";
    }
};

#if 0
istringstream 类 
getline 分割字符
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stk;
        istringstream ss(path);
        string s;
        while (getline(ss, s, '/')) {
            if (s.empty() || s == ".") {
                continue;
            }
            if (s != "..") {
                stk.push_back(s);
            }
            else if (!stk.empty()) {
                stk.pop_back();
            }
        }
        string ans;
        for (string& s : stk) {
            ans += '/';
            ans += s;
        }
        return stk.empty() ? "/" : ans;
    }
};

#endif

#if 0
class Solution {
public:
    static const int N = 3e3 + 5;
    char Stack[N];
    int Size = 0;
    string simplifyPath(string path) {
        Stack[Size++] = '/';//要你去初始化一下
        //第一个字符一定为/
        int n = path.size();
        for (int i = 1; i < n; i++) {
            if (path[i] != '/' && path[i] != '.') {
                Stack[Size++] = path[i];
            }
            //如果遇到  / 
            // 1）栈顶也是 /  忽略
            // 2）栈顶
            if (path[i] == '/' && Stack[Size - 1] == '/') {
                continue;
            }
            if (path[i] == '/' && Stack[Size - 1] != '/') {
                Stack[Size++] = '/';
            }

            if (path[i] == '.') {
                //当前为 .
                
                // 栈顶不为 .  下一个也不是.  那就是当前文件夹  直接跳过
                if (Stack[Size - 1] != '.' && i + 1 < n && path[i + 1] == '/') {
                    continue;//跳过 不入栈
                }
                // 如果栈顶为 . 而且下一个也是.  也就是三个.  直接入栈两次
                if (Stack[Size - 1] == '.' && i + 1 < n && path[i + 1] == '.') {
                    Stack[Size++] = '.';
                    continue;
                }

                //如果栈顶为 . 当前为 .  
                // 下一个是'/' 或者说没有下一个了 就需要pop了  pop到下一次的 '/' 
                if (Stack[Size - 1] == '.' && ((i + 1 < n && path[i + 1] == '/') || (i + 1 == n))) {
                    Size--;//弹出栈顶的.
                    Size--; // 弹出'/'
                    while (Size > 0 && Stack[Size - 1] != '/') {
                        Size--;
                    }
                }
            }

        }
        string ans;
        for (int i = 0; i < Size; i++) {
            ans += Stack[i];
        }
        return ans;
    }
};
#endif 