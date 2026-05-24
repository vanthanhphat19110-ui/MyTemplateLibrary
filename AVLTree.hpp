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

template <typename T>
void init(AVLTree<T> &tree)
{
    tree.root = nullptr;
}

template <typename T>
int height(const AVLNode<T> *&root)
{
    if (root == nullptr)
        return 0;
    return root->height;
}

template <typename T>
int height(const AVLTree<T> &tree)
{
    return height(tree.root);
}

template <typename T>
void update(AVLNode<T> *&root)
{
    if (root == nullptr)
        return;
    root->height = 1 + max(height(root->left), height(root->right));
}

template <typename T>
void update(AVLTree<T> &tree)
{
    update(tree.root);
}