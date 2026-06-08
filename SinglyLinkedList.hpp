/* Singly Linked List. */

#include <iostream>
#include <functional>

// SLL = Singly Linked List.
template <typename T>
struct SLLNode
{
    T data;
    SLLNode<T> *next;
    SLLNode() : data(), next(nullptr) {};
    SLLNode(const T &value) : data(value), next(nullptr) {};
};

template <typename T>
struct SinglyLinkedList
{
    SLLNode<T> *head;
    SLLNode<T> *tail;
    int size;
};

template <typename T>
void init(SinglyLinkedList<T> &list)
{
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

template <typename T>
bool isEmpty(const SinglyLinkedList<T> &list)
{
    return list.head == nullptr;
}

template <typename T>
int size(const SinglyLinkedList<T> &list)
{
    return list.size;
}

template <typename T>
void insertAtFront(SinglyLinkedList<T> &list, const T &value)
{
    SLLNode<T> *p = new SLLNode<T>(value);
    if (list.head == nullptr)
    {
        list.head = p;
        list.tail = p;
    }
    else // list.head != nullptr
    {
        p->next = list.head;
        list.head = p;
    }
    list.size++;
}

template <typename T>
void insertAtBack(SinglyLinkedList<T> &list, const T &value)
{
    SLLNode<T> *p = new SLLNode<T>(value);
    if (list.head == nullptr)
    {
        list.head = p;
        list.tail = p;
    }
    else // list.head != nullptr
    {
        list.tail->next = p;
        list.tail = p;
    }
    list.size++;
}

// Index starts at 01.
template <typename T>
void insertAtIndex(SinglyLinkedList<T> &list, int index, const T &value)
{
    if (index < 1 || index > list.size + 1)
        return;
    if (index == 1)
    {
        insertAtFront(list, value);
        return;
    }
    if (index == list.size + 1)
    {
        insertAtBack(list, value);
        return;
    }
    SLLNode<T> *curr = list.head;
    for (int i = 1; i < index - 1; i++)
        curr = curr->next;
    SLLNode<T> *p = new SLLNode<T>(value);
    p->next = curr->next;
    curr->next = p;
    list.size++;
}

template <typename T>
void removeAtFront(SinglyLinkedList<T> &list)
{
    if (list.head == nullptr)
        return;
    SLLNode<T> *temp = list.head;
    list.head = list.head->next;
    delete temp;
    if (list.head == nullptr)
        list.tail = nullptr;
    list.size--;
}

template <typename T>
void removeAtBack(SinglyLinkedList<T> &list)
{
    if (list.head == nullptr)
        return;
    if (list.head->next == nullptr)
    {
        delete list.head;
        list.head = nullptr;
        list.tail = nullptr;
        list.size = 0;
        return;
    }
    SLLNode<T> *curr = list.head;
    while (curr->next != list.tail)
        curr = curr->next;
    delete list.tail;
    curr->next = nullptr;
    list.tail = curr;
    list.size--;
}

// Index starts at 01.
template <typename T>
void removeAtIndex(SinglyLinkedList<T> &list, int index)
{
    if (list.head == nullptr || index < 1 || index > list.size)
        return;
    if (index == 1)
    {
        removeAtFront(list);
        return;
    }
    if (index == list.size)
    {
        removeAtBack(list);
        return;
    }
    SLLNode<T> *prev = nullptr, *curr = list.head;
    for (int i = 1; i < index; i++)
    {
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
    delete curr;
    list.size--;
}

template <typename T>
void removeAllValues(SinglyLinkedList<T> &list, const T &value)
{
    SLLNode<T> *dummy = new SLLNode<T>(value);
    dummy->next = list.head;
    SLLNode<T> *prev = dummy, *curr = list.head;
    while (curr != nullptr)
    {
        if (curr->data == value)
        {
            prev->next = curr->next;
            delete curr;
            list.size--;
            curr = prev->next;
        }
        else // curr->data != value
        {
            prev = curr;
            curr = curr->next;
        }
    }
    list.head = dummy->next;
    delete dummy;
    if (list.head == nullptr)
        list.tail = nullptr;
    else // list.head != nullptr
    {
        SLLNode<T> *temp = list.head;
        while (temp->next != nullptr)
            temp = temp->next;
        list.tail = temp;
    }
}

/* Xóa tất cả các node trùng nhau trong một list đã sắp xếp, giữ lại node đầu tiên. */
template <typename T>
void removeDuplicateNodes(SinglyLinkedList<T> &list)
{
    if (list.head == nullptr || list.head->next == nullptr)
        return;
    SLLNode<T> *curr = list.head;
    while (curr != nullptr && curr->next != nullptr)
    {
        if (curr->data == curr->next->data)
        {
            SLLNode<T> *temp = curr->next;
            curr->next = temp->next;
            delete temp;
            list.size--;
        }
        else
            curr = curr->next;
    }
    list.tail = curr;
}

/* Xóa tất cả các node trùng nhau trong một list đã sắp xếp. */
template <typename T>
void removeAllDuplicateNodes(SinglyLinkedList<T> &list)
{
    if (list.head == nullptr || list.head->next == nullptr)
        return;
    SLLNode<T> *dummy = new SLLNode<T>();
    dummy->next = list.head;
    SLLNode<T> *prev = dummy, *curr = list.head;
    while (curr != nullptr)
    {
        bool isDuplicated = false;
        while (curr->next != nullptr && curr->data == curr->next->data)
        {
            isDuplicated = true;
            prev->next = curr->next;
            delete curr;
            list.size--;
            curr = prev->next;
        }

        if (isDuplicated)
        {
            prev->next = curr->next;
            delete curr;
            list.size--;
            curr = prev->next;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
    list.head = dummy->next;
    delete dummy;

    if (list.head == nullptr)
        list.tail = nullptr;
    else
    {
        SLLNode<T> *temp = list.head;
        while (temp->next != nullptr)
            temp = temp->next;
        list.tail = temp;
    }
}

template <typename T>
void clear(SinglyLinkedList<T> &list)
{
    while (list.head != nullptr)
    {
        SLLNode<T> *temp = list.head;
        list.head = list.head->next;
        delete temp;
    }
    list.tail = nullptr;
    list.size = 0;
}

template <typename T>
bool isExisted(const SinglyLinkedList<T> &list, const T &value)
{
    SLLNode<T> *curr = list.head;
    while (curr != nullptr)
    {
        if (curr->data == value)
            return true;
        curr = curr->next;
    }
    return false;
}

template <typename T>
SLLNode<T> *findValue(SinglyLinkedList<T> &list, const T &value)
{
    SLLNode<T> *curr = list.head;
    while (curr != nullptr)
    {
        if (curr->data == value)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

template <typename T>
int countValue(const SinglyLinkedList<T> &list, const T &value)
{
    int frequency = 0;
    SLLNode<T> *curr = list.head;
    while (curr != nullptr)
    {
        if (curr->data == value)
            frequency++;
        curr = curr->next;
    }
    return frequency;
}

template <typename T>
void printForward(const SinglyLinkedList<T> &list)
{
    SLLNode<T> *curr = list.head;
    while (curr != nullptr)
    {
        std::cout << curr->data;
        if (curr->next != nullptr)
            std::cout << " ";
        curr = curr->next;
    }
}

template <typename T>
void reverse(SinglyLinkedList<T> &list)
{
    list.tail = list.head;
    SLLNode<T> *prev = nullptr, *curr = list.head;
    while (curr != nullptr)
    {
        SLLNode<T> *temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    list.head = prev;
}

template <typename T>
void printBackward(SinglyLinkedList<T> &list)
{
    reverse(list);
    printForward(list);
    reverse(list);
}

template <typename T>
SLLNode<T> *findMiddle(const SinglyLinkedList<T> &list)
{
    SLLNode<T> *slow = list.head, *fast = list.head;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

template <typename T>
bool isSymmetric(SinglyLinkedList<T> &list)
{
    // Tìm node giữa của list.
    SLLNode<T> *slow = list.head, *fast = list.head;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Đảo chiều nửa sau.
    SLLNode<T> *prev = nullptr, *curr = slow;
    while (curr != nullptr)
    {
        SLLNode<T> *temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }

    // Kiểm tra tính đối xứng.
    bool isSymmetric = true;
    SLLNode<T> *left = list.head, *right = prev;
    while (right != nullptr)
    {
        if (left->data != right->data)
        {
            isSymmetric = false;
            break;
        }
        left = left->next;
        right = right->next;
    }

    // Đảo chiều nửa sau để khôi phục list.
    curr = prev, prev = nullptr;
    while (curr != nullptr)
    {
        SLLNode<T> *temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }

    return isSymmetric;
}

template <typename T>
SLLNode<T> *kthFromTail(SinglyLinkedList<T> &list, int k)
{
    if (list.head == nullptr || k < 1 || k > list.size)
        return nullptr;
    SLLNode<T> *slow = list.head, *fast = list.head;
    for (int i = 1; i <= k; i++)
        fast = fast->next;
    while (fast != nullptr)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

template <typename T>
void rotateRight(SinglyLinkedList<T> &list, int k)
{
    if (list.head == nullptr || list.head->next == nullptr || k < 0)
        return;
    k = k % list.size;
    if (k == 0)
        return;
    SLLNode<T> *newTail = kthFromTail(list, k + 1);
    SLLNode<T> *newHead = newTail->next;
    list.tail->next = list.head;
    newTail->next = nullptr;
    list.head = newHead;
    list.tail = newTail;
}

/*
- Merge two sorted lists: tạo list mới để lưu kết quả.
- Điều kiện: list1 và list2 đều đã được sắp xếp theo cmp.
- Sau khi merge, không làm thay đổi list1 và list2. */
template <typename T, typename Comp = std::less<T>>
SinglyLinkedList<T> mergeTwoSortedLists(const SinglyLinkedList<T> &list1, const SinglyLinkedList<T> &list2, const Comp &cmp = Comp())
{
    SinglyLinkedList<T> ans;
    init(ans);

    SLLNode<T> *p1 = list1.head, *p2 = list2.head;
    while (p1 != nullptr && p2 != nullptr)
    {
        if (cmp(p2->data, p1->data))
        {
            insertAtBack(ans, p2->data);
            p2 = p2->next;
        }
        else
        {
            insertAtBack(ans, p1->data);
            p1 = p1->next;
        }
    }

    while (p1 != nullptr)
    {
        insertAtBack(ans, p1->data);
        p1 = p1->next;
    }

    while (p2 != nullptr)
    {
        insertAtBack(ans, p2->data);
        p2 = p2->next;
    }

    return ans;
}

/*
- Merge two sorted lists: thực hiện tại chỗ (không tạo list mới để lưu kết quả).
- Điều kiện: list1 và list2 đã được sắp xếp theo cmp.
- Sau khi merge, gộp list1 và list2 thành list ans. */
template <typename T, typename Comp = std::less<T>>
void mergeTwoSortedListsInPlace(SinglyLinkedList<T> &list1, SinglyLinkedList<T> &list2, SinglyLinkedList<T> &ans, const Comp &cmp = Comp())
{
    clear(ans);
    ans.size = list1.size + list2.size;

    SLLNode<T> *dummy = new SLLNode<T>();
    SLLNode<T> *tail = dummy, *p1 = list1.head, *p2 = list2.head;

    while (p1 != nullptr && p2 != nullptr)
    {
        if (cmp(p2->data, p1->data))
        {
            tail->next = p2;
            p2 = p2->next;
        }
        else
        {
            tail->next = p1;
            p1 = p1->next;
        }
        tail = tail->next;
    }

    if (p1 != nullptr)
    {
        tail->next = p1;
        tail = list1.tail;
    }
    else
    {
        tail->next = p2;
        tail = list2.tail;
    }

    ans.head = dummy->next;
    ans.tail = tail;
    delete dummy;

    list1.head = nullptr;
    list1.tail = nullptr;
    list1.size = 0;

    list2.head = nullptr;
    list2.tail = nullptr;
    list2.size = 0;
}

template <typename T>
void splitList(SinglyLinkedList<T> &list, SinglyLinkedList<T> &leftHalf, SinglyLinkedList<T> &rightHalf)
{
    if (list.head == nullptr || list.head->next == nullptr)
    {
        leftHalf.head = list.head;
        leftHalf.tail = list.tail;
        leftHalf.size = list.size;

        rightHalf.head = nullptr;
        rightHalf.tail = nullptr;
        rightHalf.size = 0;
    }
    else // list.head != nullptr && list.head->next != nullptr
    {
        SLLNode<T> *slow = list.head, *fast = list.head->next;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        int leftSize = (list.size + 1) / 2;
        int rightSize = list.size - leftSize;

        leftHalf.head = list.head;
        leftHalf.tail = slow;
        leftHalf.size = leftSize;

        rightHalf.head = slow->next;
        rightHalf.tail = list.tail;
        rightHalf.size = rightSize;

        slow->next = nullptr; // split
    }

    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

template <typename T, typename Comp = std::less<T>>
void mergeSortList(SinglyLinkedList<T> &list, const Comp &cmp = Comp())
{
    if (list.head == nullptr || list.head->next == nullptr)
        return;

    SinglyLinkedList<T> leftHalf, rightHalf;
    init(leftHalf);
    init(rightHalf);

    splitList(list, leftHalf, rightHalf);
    mergeSortList(leftHalf, cmp);
    mergeSortList(rightHalf, cmp);
    mergeTwoSortedListsInPlace(leftHalf, rightHalf, list, cmp);
}

template <typename T>
void swapNodesInPairs(SinglyLinkedList<T> &list)
{
    if (list.head == nullptr || list.head->next == nullptr)
        return;
    SLLNode<T> *dummy = new SLLNode<T>();
    dummy->next = list.head;
    SLLNode<T> *prev = dummy;
    while (prev->next != nullptr && prev->next->next != nullptr)
    {
        SLLNode<T> *first = prev->next;
        SLLNode<T> *second = first->next;
        first->next = second->next;
        second->next = first;
        prev->next = second;
        prev = first;
    }

    list.head = dummy->next;
    delete dummy;

    SLLNode<T> *curr = list.head;
    while (curr->next != nullptr)
        curr = curr->next;
    list.tail = curr;
}

template <typename T>
bool hasCycle(const SinglyLinkedList<T> &list)
{
    SLLNode<T> *slow = list.head, *fast = list.head;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return true;
    }
    return false;
}

template <typename T>
SLLNode<T> *findCycleStart(const SinglyLinkedList<T> &list)
{
    bool hasCycle = false;
    SLLNode<T> *slow = list.head, *fast = list.head;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            hasCycle = true;
            break;
        }
    }

    if (!hasCycle)
        return nullptr;

    SLLNode<T> *p1 = list.head, *p2 = slow;
    while (p1 != p2)
    {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}