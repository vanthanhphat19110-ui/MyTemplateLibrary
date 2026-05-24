/* Thư viện AVL Tree. */

template <typename T>
struct AVLNode
{
    T data;
    int height;
    AVLNode<T> *left, *right;
    AVLNode(const T &value) : data(value), height(1), left(nullptr), right(nullptr) {};
};

template <typename T>
struct AVLTree
{
    AVLNode<T> *root;
};
