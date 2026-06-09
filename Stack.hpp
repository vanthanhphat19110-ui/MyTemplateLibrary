/* Thư viện Stack. */

template <typename T>
struct StackNode
{
    T data;
    StackNode<T> *next;
    StackNode(const T &value) : data(value), next(nullptr) {};
};

template <typename T>
struct Stack
{
    StackNode<T> *top;
    int size;
};

template <typename T>
void init(Stack<T> &st)
{
    st.top = nullptr;
    st.size = 0;
}

template <typename T>
bool isEmpty(const Stack<T> &st)
{
    return st.top == nullptr;
}

template <typename T>
int size(const Stack<T> &st)
{
    return st.size;
}

/* Cần đảm bảo Stack khác rỗng trước khi gọi top. */
template <typename T>
const T &top(const Stack<T> &st)
{
    return st.top->data;
}

template <typename T>
void push(Stack<T> &st, const T &value)
{
    StackNode<T> *p = new StackNode<T>(value);
    p->next = st.top;
    st.top = p;
    st.size++;
}

template <typename T>
void pop(Stack<T> &st)
{
    if (st.top == nullptr)
        return;
    StackNode<T> *temp = st.top;
    st.top = st.top->next;
    delete temp;
    st.size--;
}

template <typename T>
void clear(Stack<T> &st)
{
    while (st.top != nullptr)
    {
        StackNode<T> *temp = st.top;
        st.top = st.top->next;
        delete temp;
    }
    st.size = 0;
}