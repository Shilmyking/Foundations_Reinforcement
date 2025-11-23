#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;

using ll = long long;

#if 0
template<typename K, typename V>
class SBTNode{
public:
    K key;
    V value;
    //没有parent版本的SBTree
    SBTNode<K,V>* left;
    SBTNode<K,V>* right;
    ll size;
    SBTNode(const K& k,const V&v) : key(k),value(v),left(nullptr), right(nullptr),size(1) {}
};

template<typename K, typename V>
class SizeBalancedTreeMap {
public:
    // 构造函数，确保 root 初始化
    SizeBalancedTreeMap() : root(nullptr) {}

    void remove(K key) {
        if (containsKey(key)) {//存在key才去删除
            root = Delete(root, key);
        }
    }

    //递归方案
    // 在cur这棵树上，删掉key所代表的节点
    // 返回cur这棵树的新头部
    SBTNode<K, V>* Delete(SBTNode<K, V>* cur, K key) {
        if (cur == nullptr) { 
            return nullptr;
        }

        cur->size--;
        if (key > cur->key) {
            cur->right = Delete(cur->right, key);
        }
        else if (key < cur->key) {
            cur->left = Delete(cur->left, key);
        }
        else {//删除当前节点  和BSTree的思路一样 分类
            if (cur->left == nullptr && cur->right == nullptr) {
                delete cur;
                return nullptr;
            }
            else if (cur->left == nullptr && cur->right != nullptr) {
                SBTNode<K, V>* tmp = cur;
                cur = cur->right;
                delete tmp;
            }
            else if (cur->left != nullptr && cur->right == nullptr) {
                SBTNode<K, V>* tmp = cur;
                cur = cur->left;
                delete tmp;
            }
            else {//找后继节点
                SBTNode<K, V>* pre = nullptr;
                SBTNode<K, V>* des = cur->right;//存储后继节点
                des->size--;
                while (des->left != nullptr) {
                    pre = des;
                    des = des->left;
                    des->size--;
                }//找到后继节点
                if (pre != nullptr) {
                    //pre不为nullptr  说明des不是要删除的节点的右孩子
                    //这里就是pre接管 des可能存在的右孩子
                    pre->left = des->right;
                    des->right = cur->right;//接管cur右侧
                }
                des->left = cur->left;
                //这里还是要检查 cur->left 是否为nullptr
                ll leftSize = (des->left != nullptr) ? des->left->size : 0;
                ll rightSize = (des->right != nullptr) ? des->right->size : 0;
                des->size = leftSize+rightSize + 1;
                SBTNode<K, V>* tmp = cur;
                cur = des;
                delete tmp;
            }
        }
        //cur = maintain(cur);//调整树的平衡
        return cur;//返回新head
    }

    // （key，value） put -> 有序表 新增、改value
    void put(K key, V value) {
        SBTNode<K, V>* lastNode = findLastIndex(key);//找到最近的不空节点
        if (lastNode != nullptr && key == lastNode->key) {//存在就是改val 否则就是新增
            lastNode->value = value;
        }
        else {//整棵树都是空的 or 确实是没有这个key添加过
            //root有可能会旋转  所以需要返回一个新Head
            root = add(root, key, value);//没有parent指针所以只能从root开始add
        }
    }
    // 现在，以cur为头的树上，新增，加(key, value)这样的记录
    // 加完之后，会对cur做检查，该调整调整
    // 返回，调整完之后，整棵树的新头部
    //返回找到的新key的结点的新节点   存在maintain的可能性
    //这里实现的版本是  一定不存在key才去add
    SBTNode<K, V>* add(SBTNode<K, V>* cur, K key, V value) {
        if (cur == nullptr) {
            return new SBTNode<K,V>(key, value);
        }
        else {//存在key or 递归寻找key
            cur->size++;
            if (key < cur->key) {
                //加完之后可能存在头部旋转 所以需要返回maintain之后的head
                cur->left = add(cur->left, key, value);
            }
            else {
                cur->right = add(cur->right, key, value);
            }
            //插入完节点之后 从底往上递归调整
            return maintain(cur);//每次递归回来之后都需要进行调整
        }
    }

    ll size() {
        return root != nullptr ? root->size : 0;
    }

    bool containsKey(K key) {//查找是否存在这个key
        SBTNode<K, V>* lastNode = findLastIndex(key);
        return lastNode != nullptr && key == lastNode->key;
    }

    V get(K key) {
        SBTNode<K, V>*lastNode = findLastIndex(key);
        if (lastNode != nullptr && key == lastNode->key) {
            return lastNode->value;
        }
        throw "invalid parameter";
    }

    //找到第 Kth大的结点
    SBTNode<K, V>* getIndex(SBTNode<K, V>* cur, ll kth) {
        if (kth == (cur->left != nullptr ? cur->left->size : 0) + 1) {
            return cur;
        }
        else if (kth <= (cur->left != nullptr ? cur->left->size : 0)) {
            return getIndex(cur->left, kth);
        }
        else {
            return getIndex(cur->right, kth - (cur->left != nullptr ? cur->left->size : 0) - 1);
        }
    }
    K getIndexKey(ll index) {
        if (index < 0 || index >= this->size()) {
            throw "error index";
        }
        return getIndex(root, index + 1)->key;
    }

    V getIndexValue(ll index) {
        if (index < 0 || index >= this->size()) {
            throw "error index";
        }
        return getIndex(root, index + 1)->value;
    }
    K firstKey() {
        if (root == nullptr) {
            throw "The tree is empty";
        }
        SBTNode<K, V>* cur = root;
        while (cur->left != nullptr) {
            cur = cur->left;
        }
        return cur->key;
    }

    K lastKey() {
        if (root == nullptr) {
            throw "The tree is empty";
        }
        SBTNode<K, V>* cur = root;
        while (cur->right != nullptr) {
            cur = cur->right;
        }
        return cur->key;
    }

    // 检查是否存在小于等于key的最大键
    bool hasFloorKey(K key) {
        return findLastNoBigIndex(key) != nullptr;
    }

    K floorKey(K key) {
        SBTNode<K, V>* lastNoBigNode = findLastNoBigIndex(key);
        if (lastNoBigNode == nullptr) {
            throw "invaild parameter";
        }
        return  lastNoBigNode->key;
    }
    
    // 检查是否存在大于等于key的最小键
    bool hasCeilingKey(K key) {
        return findLastNoSmallIndex(key) != nullptr;
    }

    K ceilingKey(K key) {
        SBTNode<K, V>* lastNoSmallNode = findLastNoSmallIndex(key);
        if (lastNoSmallNode == nullptr) {
            throw "invaild parameter";
        }
        return  lastNoSmallNode->key;
    }

    SBTNode<K, V>* getRoot() {
        return root;
    }
private:

    //Key为可比较的
    //找到key的Node就返回 	如果没找到就返回最近的不为空的节点
    SBTNode<K, V>* findLastIndex(K key) {
        SBTNode<K, V>* pre = root;
        SBTNode<K, V>* cur = root;
        while (cur != nullptr) {
            pre = cur;//一直抓cur这个节点 且不让这个节点为空
            if (key == cur->key) {//存在原始key
                break;
            }
            else if (key < cur->key) {
                cur = cur->left;
            }
            else {
                cur = cur->right;
            }
        }
        return pre;
    }

    SBTNode<K, V>* findLastNoSmallIndex(K key) {
        SBTNode<K, V>* ans = nullptr;
        SBTNode<K, V>* cur = root;
        while (cur != nullptr) {
            if (key == cur->key) {
                ans = cur;
                break;
            }
            else if (key < cur->key) {
                ans = cur;
                cur = cur->left;
            }
            else {
                cur = cur->right;
            }
        }
        return ans;
    }

    SBTNode<K, V>* findLastNoBigIndex(K key) {
        SBTNode<K, V>* ans = nullptr;
        SBTNode<K, V>* cur = root;
        while (cur != nullptr) {
            if (key == cur->key) {
                ans = cur;
                break;
            }
            else if (key < cur->key) {
                cur = cur->left;
            }
            else {
                ans = cur;
                cur = cur->right;
            }
        }
        return ans;
    }

    SBTNode<K, V>* maintain(SBTNode<K, V>* cur) {
        if (cur == nullptr)return nullptr;

        ll leftSize = cur->left != nullptr ? cur->left->size : 0;
        ll leftLeftSize = cur->left != nullptr && cur->left->left != nullptr ? cur->left->left->size : 0;
        ll leftRightSize = cur->left != nullptr && cur->left->right != nullptr ? cur->left->right->size : 0;
        ll rightSize = cur->right != nullptr ? cur->right->size : 0;
        ll rightLeftSize = cur->right != nullptr && cur->right->left != nullptr ? cur->right->left->size : 0;
        ll rightRightSize = cur->right != nullptr && cur->right->right != nullptr ? cur->right->right->size : 0;
        //LL  LR  RL  RR
        if (leftLeftSize > rightSize) { //LL 型一次右旋
            cur = rightRotate(cur);
            cur->right = maintain(cur->right);
            cur = maintain(cur);
        }
        else if (leftRightSize > rightSize) {//LR型 Root结点的左孩子左旋 然后Root右旋
            cur->left = leftRotate(cur->left);
            cur = rightRotate(cur);
            cur->left = maintain(cur->left);
            cur->right = maintain(cur->right);
            cur = maintain(cur);//需要最后maintain Root结点
        }
        else if (rightLeftSize > leftSize) {//RL型  Root 结点右孩子右旋 Root左旋
            cur->right = rightRotate(cur->right);
            cur = leftRotate(cur);
            cur->right = maintain(cur->right);
            cur->left = maintain(cur->left);
            cur = maintain(cur);
        }
        else if (rightRightSize > leftSize) {//RR型 一次左旋
            cur = leftRotate(cur);
            cur->left = maintain(cur->left);
            cur = maintain(cur);
        }
        return cur;
    }

    SBTNode<K, V>* leftRotate(SBTNode<K, V>* cur) {
        // 左旋 cur->left 是可以为 nullptr 的
        if (cur == nullptr || cur->right == nullptr) {
            printf("error LeftRotate\n");
            throw "error LeftRotate";
        }
        SBTNode<K, V>* rightNode = cur->right;
        cur->right = rightNode->left;
        rightNode->left = cur;
        //size 调整
        rightNode->size = cur->size;
        cur->size = (cur->left != nullptr ? cur->left->size : 0) + (cur->right != nullptr ? cur->right->size : 0) + 1;
        return rightNode;
    }

    SBTNode<K, V>* rightRotate(SBTNode<K, V>* cur) {
        // 右旋 cur->right 是可以为 nullptr 的
        if (cur == nullptr || cur->left == nullptr ) {
            printf("error RightRotate\n");
            throw "error RightRotate"; //提前抛异常/返回避免崩溃
        }
        SBTNode<K, V>* leftNode = cur->left;
        cur->left = leftNode->right;
        leftNode->right = cur;
        //size 调整
        leftNode->size = cur->size;
        cur->size = (cur->left != nullptr ? cur->left->size : 0) + (cur->right != nullptr ? cur->right->size : 0) + 1;
        return leftNode;
    }

private:
    SBTNode<K, V>* root;
};

#endif