/* Thư viện Priority Queue. */

#include <vector>
#include <functional>

template <typename T>
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
struct PriorityQueue
{
    vector<T> heap;
};

template <typename T>
void init(PriorityQueue<T> &pq)
{
    pq.heap.clear();
}

template <typename T>
bool isEmpty(const PriorityQueue<T> &pq)
{
    return pq.heap.empty();
}

template <typename T>
int size(const PriorityQueue<T> &pq)
{
    return pq.heap.size();
}

template <typename T>
const T &peek(const PriorityQueue<T> &pq)
{
    return pq.heap[0];
}

template <typename T, typename Comp = std::less<T>>
void heapifyUp(PriorityQueue<T> &pq, int index, const Comp &cmp = Comp())
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (cmp(pq.heap[parent], pq.heap[index]))
        {
            mySwap(pq.heap[index], pq.heap[parent]);
            index = parent;
        }
        else
            break;
    }
}

template <typename T, typename Comp = std::less<T>>
void heapifyDown(PriorityQueue<T> &pq, int index, const Comp &cmp = Comp())
{
    int sizeHeap = pq.heap.size();
    while (2 * index + 1 < sizeHeap)
    {
        int best = index, left = 2 * index + 1, right = 2 * index + 2;
        if (left < sizeHeap && cmp(pq.heap[best], pq.heap[left]))
            best = left;
        if (right < sizeHeap && cmp(pq.heap[best], pq.heap[right]))
            best = right;
        if (best == index)
            break;
        mySwap(pq.heap[index], pq.heap[best]);
        index = best;
    }
}

template <typename T, typename Comp = std::less<T>>
void push(PriorityQueue<T> &pq, const T &value, const Comp &cmp = Comp())
{
    pq.heap.push_back(value);
    int sizeHeap = pq.heap.size();
    heapifyUp(pq, sizeHeap - 1, cmp);
}

template <typename T, typename Comp = std::less<T>>
void pop(PriorityQueue<T> &pq, const Comp &cmp = Comp())
{
    if (pq.heap.empty())
        return;
    mySwap(pq.heap[0], pq.heap.back());
    pq.heap.pop_back();
    if (!pq.heap.empty())
        heapifyDown(pq, 0, cmp);
}