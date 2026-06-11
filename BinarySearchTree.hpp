/* Thư viện Binary Search Tree. */

/* Note: Duplicate values are ignored. */

#include <iostream>
#include <algorithm>
#include <functional>

template <typename T>
struct BSTNode
{
    T data;
    BSTNode<T> *left, *right;
    BSTNode(const T &value) : data(value), left(nullptr), right(nullptr) {};
};

template <typename T, typename Comp = std::less<T>>
struct BinarySearchTree
{
    BSTNode<T> *root = nullptr;
    Comp cmp{};
};

template <typename T, typename Comp = std::less<T>>
bool isEmpty(const BinarySearchTree<T, Comp> &tree)
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

template <typename T, typename Comp = std::less<T>>
int height(const BinarySearchTree<T, Comp> &tree)
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

template <typename T, typename Comp = std::less<T>>
int size(const BinarySearchTree<T, Comp> &tree)
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

template <typename T, typename Comp = std::less<T>>
void preOrder(const BinarySearchTree<T, Comp> &tree)
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

template <typename T, typename Comp = std::less<T>>
void inOrder(const BinarySearchTree<T, Comp> &tree)
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

template <typename T, typename Comp = std::less<T>>
void postOrder(const BinarySearchTree<T, Comp> &tree)
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
void insert(BinarySearchTree<T, Comp> &tree, const T &value)
{
    tree.root = insert(tree.root, value, tree.cmp);
}

template <typename T>
BSTNode<T> *findLeftMost(BSTNode<T> *root)
{
    if (root == nullptr)
        return nullptr;
    while (root->left != nullptr)
        root = root->left;
    return root;
}

template <typename T, typename Comp = std::less<T>>
BSTNode<T> *findLeftMost(BinarySearchTree<T, Comp> &tree)
{
    return findLeftMost(tree.root);
}

template <typename T, typename Comp = std::less<T>>
const BSTNode<T> *findLeftMost(const BinarySearchTree<T, Comp> &tree)
{
    return findLeftMost(tree.root);
}

template <typename T>
BSTNode<T> *findRightMost(BSTNode<T> *root)
{
    if (root == nullptr)
        return nullptr;
    while (root->right != nullptr)
        root = root->right;
    return root;
}

template <typename T, typename Comp = std::less<T>>
BSTNode<T> *findRightMost(BinarySearchTree<T, Comp> &tree)
{
    return findRightMost(tree.root);
}

template <typename T, typename Comp = std::less<T>>
const BSTNode<T> *findRightMost(const BinarySearchTree<T, Comp> &tree)
{
    return findRightMost(tree.root);
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
            BSTNode<T> *temp = findRightMost(root->left);
            root->data = temp->data;
            root->left = remove(root->left, temp->data, cmp);
        }
    }
    return root;
}

template <typename T, typename Comp = std::less<T>>
void remove(BinarySearchTree<T, Comp> &tree, const T &value)
{
    tree.root = remove(tree.root, value, tree.cmp);
}

template <typename T, typename Comp = std::less<T>>
bool contains(BSTNode<T> *root, const T &value, const Comp &cmp = Comp())
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
bool contains(const BinarySearchTree<T, Comp> &tree, const T &value)
{
    return contains(tree.root, value, tree.cmp);
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
BSTNode<T> *find(BinarySearchTree<T, Comp> &tree, const T &value)
{
    return find(tree.root, value, tree.cmp);
}

template <typename T, typename Comp = std::less<T>>
const BSTNode<T> *find(const BinarySearchTree<T, Comp> &tree, const T &value)
{
    return find(tree.root, value, tree.cmp);
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

template <typename T, typename Comp = std::less<T>>
void clear(BinarySearchTree<T, Comp> &tree)
{
    clear(tree.root);
}