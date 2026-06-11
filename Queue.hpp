/* Thư viện Queue. */

template <typename T>
struct QueueNode
{
    T data;
    QueueNode<T> *next;
    QueueNode(const T &value) : data(value), next(nullptr) {};
};

template <typename T>
struct Queue
{
    QueueNode<T> *front = nullptr;
    QueueNode<T> *back = nullptr;
    int size = 0;
};

template <typename T>
bool isEmpty(const Queue<T> &q)
{
    return q.front == nullptr;
}

template <typename T>
int size(const Queue<T> &q)
{
    return q.size;
}

/* Cần đảm bảo Queue khác rỗng trước khi gọi front(). */
template <typename T>
const T &front(const Queue<T> &q)
{
    return q.front->data;
}

template <typename T>
void enqueue(Queue<T> &q, const T &value)
{
    QueueNode<T> *p = new QueueNode<T>(value);
    if (q.front == nullptr)
    {
        q.front = p;
        q.back = p;
    }
    else // q.front != nullptr
    {
        q.back->next = p;
        q.back = p;
    }
    q.size++;
}

template <typename T>
void dequeue(Queue<T> &q)
{
    if (q.front == nullptr)
        return;
    QueueNode<T> *temp = q.front;
    q.front = q.front->next;
    delete temp;
    q.size--;
    if (q.front == nullptr)
        q.back = nullptr;
}

template <typename T>
void clear(Queue<T> &q)
{
    while (q.front != nullptr)
    {
        QueueNode<T> *temp = q.front;
        q.front = q.front->next;
        delete temp;
    }
    q.back = nullptr;
    q.size = 0;
}