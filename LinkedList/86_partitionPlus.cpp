
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

/*
将链表划分为  小、中、大的形式
Node*head int pivot
return 新head

4->2->3->5->6->1->3->0
*/

ListNode* listPartition(ListNode* head, int pivot) {
	ListNode* sH = nullptr; ListNode* sT = nullptr;
	ListNode* eH = nullptr; ListNode* eT = nullptr;
	ListNode* bH = nullptr; ListNode* bT = nullptr;
	ListNode* cur = head;
	ListNode* nexts = nullptr;
	//遍历链表  串起来
	while (cur != nullptr) {
		nexts = cur->next;
		cur->next = nullptr;
		if (cur->val > pivot) {
			if (bH == nullptr) {
				bH = cur;
				bT = bH;
			}
			else {
				bT->next = cur;
				bT = bT->next;
			}
		}
		else if (cur->val == pivot) {
			if (eH == nullptr) {
				eH = cur;
				eT = eH;
			}
			else {
				eT->next = cur;
				eT = eT->next;
			}
		}
		else {//小  cur->val < pivot
			if (sH == nullptr) {
				sH = cur;
				sT = sH;
			}
			else {
				sT->next = cur;
				sT = sT->next;
			}
		}
		cur = nexts;
	}
	//三部分串起来
	//small部分存在节点 就链接eH
	if (sT != nullptr) {
		sT->next = eH;
	}
	//equal部分存在节点 eT链接bH
	//如果你中间没有节点 那最开始的sT链接bH去
	if (eT != nullptr) {
		eT->next = bH;
	}
	else if (sT != nullptr) {
		sT->next = bH;
	}

	//有节点你就返回  因为从小到大 前面连接好了
	if (sH != nullptr) {
		return sH;
	}
	else if (eH != nullptr) {
		return eH;
	}
	else {
		return bH;
	}

}


/*
AIGC 对数器

 // 辅助函数：根据数组创建链表
ListNode* createList(const std::vector<int>& arr) {
    if (arr.empty()) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* cur = head;
    for (size_t i = 1; i < arr.size(); ++i) {
        cur->next = new ListNode(arr[i]);
        cur = cur->next;
    }
    return head;
}

// 辅助函数：打印链表 (用于调试)
void printList(const std::string& msg, ListNode* head) {
    std::cout << msg;
    while (head != nullptr) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "nullptr" << std::endl;
}

// 1. 生成随机链表
ListNode* generateRandomLinkedList(int maxLen, int maxVal) {
    int len = rand() % (maxLen + 1);
    if (len == 0) return nullptr;
    std::vector<int> arr(len);
    for (int i = 0; i < len; ++i) {
        arr[i] = rand() % (maxVal + 1);
    }
    return createList(arr);
}

// 2. 对比器 (绝对正确的方法)
// 思路：将所有值存入三个vector，然后重新构建链表
ListNode* comparator(ListNode* head, int pivot) {
    if (head == nullptr) return nullptr;

    std::vector<int> less, equal, greater;
    ListNode* cur = head;
    while (cur != nullptr) {
        if (cur->val < pivot) {
            less.push_back(cur->val);
        }
        else if (cur->val == pivot) {
            equal.push_back(cur->val);
        }
        else {
            greater.push_back(cur->val);
        }
        cur = cur->next;
    }

    // 合并三个vector
    std::vector<int> result;
    result.insert(result.end(), less.begin(), less.end());
    result.insert(result.end(), equal.begin(), equal.end());
    result.insert(result.end(), greater.begin(), greater.end());

    return createList(result);
}

// 3. 复制链表
ListNode* copyLinkedList(ListNode* head) {
    if (head == nullptr) return nullptr;
    ListNode* newHead = new ListNode(head->val);
    ListNode* curNew = newHead;
    ListNode* curOld = head->next;
    while (curOld != nullptr) {
        curNew->next = new ListNode(curOld->val);
        curNew = curNew->next;
        curOld = curOld->next;
    }
    return newHead;
}

// 4. 比较两个链表是否相等
bool areListsEqual(ListNode* l1, ListNode* l2) {
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val != l2->val) {
            return false;
        }
        l1 = l1->next;
        l2 = l2->next;
    }
    // 必须同时为 nullptr 才算相等
    return (l1 == nullptr) && (l2 == nullptr);
}

// 5. 对数器主函数
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int testTimes = 10000; // 测试次数
    int maxLen = 20;       // 链表最大长度
    int maxVal = 30;       // 链表最大值

    std::cout << "Starting tests..." << std::endl;

    for (int i = 0; i < testTimes; ++i) {
        // 随机生成链表和 pivot
        ListNode* head1 = generateRandomLinkedList(maxLen, maxVal);
        ListNode* head2 = copyLinkedList(head1); // 必须复制
        int pivot = rand() % (maxVal + 1);

        // 运行你的方法 (修正后)
        ListNode* result1 = listPartition(head1, pivot);

        // 运行对比器 (绝对正确的方法)
        ListNode* result2 = comparator(head2, pivot);

        if (!areListsEqual(result1, result2)) {
            std::cout << "=================" << std::endl;
            std::cout << "Test Failed!" << std::endl;
            std::cout << "Pivot: " << pivot << std::endl;
            // 打印原始链表 (需要再次复制，因为 head2 被 comparator 遍历过了)
            printList("Original: ", copyLinkedList(head2));
            printList("Your_Func:  ", result1);
            printList("Comparator: ", result2);
            std::cout << "=================" << std::endl;
            break; // 出现错误，停止测试
        }

        // 释放内存 (防止内存泄漏)
        // ... (在实际工程中需要delete, 此处为演示省略)
        // ...

        if ((i + 1) % 1000 == 0) {
            std::cout << "Passed " << (i + 1) << " tests..." << std::endl;
        }
    }

    std::cout << "All tests finished." << std::endl;

    // --- 演示您提供的例子 ---
    std::cout << "\n--- Demo with your example (4->2->3->5->6->1->3->0) ---" << std::endl;
    std::vector<int> arr = { 4, 2, 3, 5, 6, 1, 3, 0 };
    ListNode* demoHead = createList(arr);
    printList("Original: ", demoHead);
    int demoPivot = 3;
    ListNode* demoResult = listPartition(demoHead, demoPivot);
    printList("Partitioned: ", demoResult);

    return 0;
}

*/