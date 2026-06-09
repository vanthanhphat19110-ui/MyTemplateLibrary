/* Thư viện Priority Queue. */
/* Ghi chú:
- Priority Queue được xây dựng bằng Complete Binary Tree.
- getHeapNode(root, index):
+ Đánh chỉ số node như heap mảng, bắt đầu từ 01.
+ Sử dụng biểu diễn nhị phân của index để tìm đường đi từ root.
*/

#include "Stack.hpp"
#include <functional>

template <typename T>
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
struct HeapNode
{
    T data;
    HeapNode<T> *parent, *left, *right;
    HeapNode(const T &value) : data(value), parent(nullptr), left(nullptr), right(nullptr) {};
};

template <typename T, typename Comp = std::less<T>>
struct PriorityQueue
{
    HeapNode<T> *root;
    int size;
    Comp cmp;
};

template <typename T, typename Comp = std::less<T>>
void init(PriorityQueue<T, Comp> &pq)
{
    pq.root = nullptr;
    pq.size = 0;
}

template <typename T, typename Comp = std::less<T>>
bool isEmpty(const PriorityQueue<T, Comp> &pq)
{
    return pq.root == nullptr;
}

template <typename T, typename Comp = std::less<T>>
int size(const PriorityQueue<T, Comp> &pq)
{
    return pq.size;
}

/* Cần đảm bảo Priority Queue khác rỗng trước khi gọi top(). */
template <typename T, typename Comp = std::less<T>>
const T &top(const PriorityQueue<T, Comp> &pq)
{
    return pq.root->data;
}

template <typename T>
HeapNode<T> *getHeapNode(HeapNode<T> *root, int index)
{
    if (index == 1)
        return root;

    Stack<int> st;
    init(st);

    while (index > 0)
    {
        push(st, index % 2);
        index = index / 2;
    }
    pop(st);

    HeapNode<T> *curr = root;
    while (!isEmpty(st))
    {
        int bit = st.top->data;
        pop(st);

        if (curr == nullptr)
            return nullptr;

        if (bit == 0)
            curr = curr->left;
        else // bit == 1
            curr = curr->right;
    }

    return curr;
}

template <typename T, typename Comp = std::less<T>>
void heapifyUp(HeapNode<T> *node, const Comp &cmp = Comp())
{
    while (node->parent != nullptr && cmp(node->parent->data, node->data))
    {
        mySwap(node->parent->data, node->data);
        node = node->parent;
    }
}

template <typename T, typename Comp = std::less<T>>
void heapifyDown(HeapNode<T> *node, const Comp &cmp = Comp())
{
    while (node != nullptr)
    {
        HeapNode<T> *best = node;
        if (node->left != nullptr && cmp(best->data, node->left->data))
            best = node->left;
        if (node->right != nullptr && cmp(best->data, node->right->data))
            best = node->right;
        if (best == node)
            break;
        mySwap(node->data, best->data);
        node = best;
    }
}

template <typename T, typename Comp = std::less<T>>
void push(PriorityQueue<T, Comp> &pq, const T &value)
{
    if (pq.root == nullptr)
    {
        HeapNode<T> *newNode = new HeapNode<T>(value);
        pq.root = newNode;
        pq.size = 1;
        return;
    }
    pq.size++;
    int index = pq.size;
    int parentIndex = index / 2;
    HeapNode<T> *parentNode = getHeapNode(pq.root, parentIndex);
    HeapNode<T> *newNode = new HeapNode<T>(value);
    newNode->parent = parentNode;
    if (index % 2 == 0)
        parentNode->left = newNode;
    else // index % 2 == 1
        parentNode->right = newNode;
    heapifyUp(newNode, pq.cmp);
}

template <typename T, typename Comp = std::less<T>>
void pop(PriorityQueue<T, Comp> &pq)
{
    if (pq.root == nullptr)
        return;
    if (pq.size == 1)
    {
        delete pq.root;
        pq.root = nullptr;
        pq.size = 0;
        return;
    }
    HeapNode<T> *theLast = getHeapNode(pq.root, pq.size);
    pq.root->data = theLast->data;
    HeapNode<T> *parentTheLast = theLast->parent;
    if (parentTheLast->left == theLast)
        parentTheLast->left = nullptr;
    else // parentTheLast->right == theLast
        parentTheLast->right = nullptr;
    delete theLast;
    pq.size--;
    heapifyDown(pq.root, pq.cmp);
}

template <typename T>
void clear(HeapNode<T> *&root)
{
    if (root == nullptr)
        return;
    clear(root->left);
    clear(root->right);
    delete root;
    root = nullptr;
}

template <typename T, typename Comp = std::less<T>>
void clear(PriorityQueue<T, Comp> &pq)
{
    clear(pq.root);
    pq.size = 0;
}