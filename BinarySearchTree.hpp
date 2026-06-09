/* Thư viện Binary Search Tree. */
/* Binary Search Tree:
- Duplicate values are ignored.
- All operations on Binary Search Tree must use the same comparator. */

#include <iostream>
#include <functional>

template <typename T>
struct BSTNode
{
    T data;
    BSTNode<T> *left, *right;
    BSTNode(const T &value) : data(value), left(nullptr), right(nullptr) {};
};

template <typename T>
struct BinarySearchTree
{
    BSTNode<T> *root;
};

template <typename T>
void init(BinarySearchTree<T> &tree)
{
    tree.root = nullptr;
}

template <typename T>
bool isEmpty(const BinarySearchTree<T> &tree)
{
    return tree.root == nullptr;
}

template <typename T>
int height(BSTNode<T> *root)
{
    if (root == nullptr)
        return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

template <typename T>
int height(const BinarySearchTree<T> &tree)
{
    return height(tree.root);
}

template <typename T>
int size(BSTNode<T> *root)
{
    if (root == nullptr)
        return 0;
    return 1 + size(root->left) + size(root->right);
}

template <typename T>
int size(const BinarySearchTree<T> &tree)
{
    return size(tree.root);
}

template <typename T>
void preOrder(BSTNode<T> *root)
{
    if (root == nullptr)
        return;
    std::cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

template <typename T>
void preOrder(const BinarySearchTree<T> &tree)
{
    preOrder(tree.root);
}

template <typename T>
void inOrder(BSTNode<T> *root)
{
    if (root == nullptr)
        return;
    inOrder(root->left);
    std::cout << root->data << " ";
    inOrder(root->right);
}

template <typename T>
void inOrder(const BinarySearchTree<T> &tree)
{
    inOrder(tree.root);
}

template <typename T>
void postOrder(BSTNode<T> *root)
{
    if (root == nullptr)
        return;
    postOrder(root->left);
    postOrder(root->right);
    std::cout << root->data << " ";
}

template <typename T>
void postOrder(const BinarySearchTree<T> &tree)
{
    postOrder(tree.root);
}

template <typename T, typename Comp = std::less<T>>
BSTNode<T> *insert(BSTNode<T> *root, const T &value, const Comp &cmp = Comp())
{
    if (root == nullptr)
    {
        BSTNode<T> *p = new BSTNode<T>(value);
        return p;
    }
    if (cmp(value, root->data))
        root->left = insert(root->left, value, cmp);
    else if (cmp(root->data, value))
        root->right = insert(root->right, value, cmp);
    else // root->data == value (trùng giá trị, không chèn)
        return root;
    return root;
}

template <typename T, typename Comp = std::less<T>>
void insert(BinarySearchTree<T> &tree, const T &value, const Comp &cmp = Comp())
{
    tree.root = insert(tree.root, value, cmp);
}

template <typename T>
BSTNode<T> *findMin(BSTNode<T> *root)
{
    if (root == nullptr)
        return nullptr;
    while (root->left != nullptr)
        root = root->left;
    return root;
}

template <typename T>
BSTNode<T> *findMin(const BinarySearchTree<T> &tree)
{
    return findMin(tree.root);
}

template <typename T>
BSTNode<T> *findMax(BSTNode<T> *root)
{
    if (root == nullptr)
        return nullptr;
    while (root->right != nullptr)
        root = root->right;
    return root;
}

template <typename T>
BSTNode<T> *findMax(const BinarySearchTree<T> &tree)
{
    return findMax(tree.root);
}

template <typename T, typename Comp = std::less<T>>
BSTNode<T> *remove(BSTNode<T> *root, const T &value, const Comp &cmp = Comp())
{
    if (root == nullptr)
        return nullptr;
    if (cmp(value, root->data))
        root->left = remove(root->left, value, cmp);
    else if (cmp(root->data, value))
        root->right = remove(root->right, value, cmp);
    else // root->data == value
    {
        if (root->left == nullptr || root->right == nullptr)
        {
            BSTNode<T> *child = (root->left != nullptr) ? root->left : root->right;
            delete root;
            return child;
        }
        else // root->left != nullptr && root->right != nullptr
        {
            BSTNode<T> *temp = findMax(root->left);
            root->data = temp->data;
            root->left = remove(root->left, temp->data, cmp);
        }
    }
    return root;
}

template <typename T, typename Comp = std::less<T>>
void remove(BinarySearchTree<T> &tree, const T &value, const Comp &cmp = Comp())
{
    tree.root = remove(tree.root, value, cmp);
}

template <typename T, typename Comp = std::less<T>>
bool isExisted(BSTNode<T> *root, const T &value, const Comp &cmp = Comp())
{
    BSTNode<T> *curr = root;
    while (curr != nullptr)
    {
        if (cmp(value, curr->data))
            curr = curr->left;
        else if (cmp(curr->data, value))
            curr = curr->right;
        else // curr->data == value
            return true;
    }
    return false;
}

template <typename T, typename Comp = std::less<T>>
bool isExisted(const BinarySearchTree<T> &tree, const T &value, const Comp &cmp = Comp())
{
    return isExisted(tree.root, value, cmp);
}

template <typename T, typename Comp = std::less<T>>
BSTNode<T> *find(BSTNode<T> *root, const T &value, const Comp &cmp = Comp())
{
    BSTNode<T> *curr = root;
    while (curr != nullptr)
    {
        if (cmp(value, curr->data))
            curr = curr->left;
        else if (cmp(curr->data, value))
            curr = curr->right;
        else // curr->data == value
            return curr;
    }
    return nullptr;
}

template <typename T, typename Comp = std::less<T>>
BSTNode<T> *find(const BinarySearchTree<T> &tree, const T &value, const Comp &cmp = Comp())
{
    return find(tree.root, value, cmp);
}

template <typename T>
void clear(BSTNode<T> *&root)
{
    if (root == nullptr)
        return;
    clear(root->left);
    clear(root->right);
    delete root;
    root = nullptr;
}

template <typename T>
void clear(BinarySearchTree<T> &tree)
{
    clear(tree.root);
}