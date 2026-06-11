/* Thư viện AVL Tree. */

/* Note: Duplicate values are ignored. */

#include <iostream>
#include <algorithm>
#include <functional>

template <typename T>
struct AVLNode
{
    T data;
    int height, size;
    AVLNode<T> *left, *right;
    AVLNode(const T &value) : data(value), height(1), size(1), left(nullptr), right(nullptr) {};
};

template <typename T, typename Comp = std::less<T>>
struct AVLTree
{
    AVLNode<T> *root = nullptr;
    Comp cmp{};
};

template <typename T, typename Comp = std::less<T>>
bool isEmpty(const AVLTree<T, Comp> &tree)
{
    return tree.root == nullptr;
}

template <typename T>
int height(AVLNode<T> *root)
{
    if (root == nullptr)
        return 0;
    return root->height;
}

template <typename T, typename Comp = std::less<T>>
int height(const AVLTree<T, Comp> &tree)
{
    return height(tree.root);
}

template <typename T>
int size(AVLNode<T> *root)
{
    if (root == nullptr)
        return 0;
    return root->size;
}

template <typename T, typename Comp = std::less<T>>
int size(const AVLTree<T, Comp> &tree)
{
    return size(tree.root);
}

template <typename T>
void preOrder(AVLNode<T> *root)
{
    if (root == nullptr)
        return;
    std::cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

template <typename T, typename Comp = std::less<T>>
void preOrder(const AVLTree<T, Comp> &tree)
{
    preOrder(tree.root);
}

template <typename T>
void inOrder(AVLNode<T> *root)
{
    if (root == nullptr)
        return;
    inOrder(root->left);
    std::cout << root->data << " ";
    inOrder(root->right);
}

template <typename T, typename Comp = std::less<T>>
void inOrder(const AVLTree<T, Comp> &tree)
{
    inOrder(tree.root);
}

template <typename T>
void postOrder(AVLNode<T> *root)
{
    if (root == nullptr)
        return;
    postOrder(root->left);
    postOrder(root->right);
    std::cout << root->data << " ";
}

template <typename T, typename Comp = std::less<T>>
void postOrder(const AVLTree<T, Comp> &tree)
{
    postOrder(tree.root);
}

template <typename T>
void update(AVLNode<T> *root)
{
    if (root == nullptr)
        return;
    root->height = 1 + std::max(height(root->left), height(root->right));
    root->size = 1 + size(root->left) + size(root->right);
}

template <typename T>
int calcBalance(AVLNode<T> *root)
{
    if (root == nullptr)
        return 0;
    return height(root->right) - height(root->left);
}

// Lệch trái-trái: xoay phải một lần.
template <typename T>
AVLNode<T> *rotateRight(AVLNode<T> *root)
{
    AVLNode<T> *leftChild = root->left;
    AVLNode<T> *temp = leftChild->right;
    leftChild->right = root;
    root->left = temp;
    update(root);
    update(leftChild);
    return leftChild;
}

// Lệch phải-phải: xoay trái một lần.
template <typename T>
AVLNode<T> *rotateLeft(AVLNode<T> *root)
{
    AVLNode<T> *rightChild = root->right;
    AVLNode<T> *temp = rightChild->left;
    rightChild->left = root;
    root->right = temp;
    update(root);
    update(rightChild);
    return rightChild;
}

// Lệch trái-phải: xoay trái rồi xoay phải.
template <typename T>
AVLNode<T> *rotateLeftRight(AVLNode<T> *root)
{
    root->left = rotateLeft(root->left);
    return rotateRight(root);
}

// Lệch phải-trái: xoay phải rồi xoay trái.
template <typename T>
AVLNode<T> *rotateRightLeft(AVLNode<T> *root)
{
    root->right = rotateRight(root->right);
    return rotateLeft(root);
}

template <typename T>
AVLNode<T> *rebalance(AVLNode<T> *root)
{
    if (root == nullptr)
        return nullptr;

    update(root);
    int balance = calcBalance(root);

    // Lệch trái-trái.
    if (balance < -1 && calcBalance(root->left) <= 0)
        return rotateRight(root);

    // Lệch phải-phải.
    if (balance > 1 && calcBalance(root->right) >= 0)
        return rotateLeft(root);

    // Lệch trái-phải.
    if (balance < -1 && calcBalance(root->left) > 0)
        return rotateLeftRight(root);

    // Lệch phải-trái.
    if (balance > 1 && calcBalance(root->right) < 0)
        return rotateRightLeft(root);

    return root;
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *insert(AVLNode<T> *root, const T &value, const Comp &cmp = Comp())
{
    if (root == nullptr)
    {
        AVLNode<T> *p = new AVLNode<T>(value);
        return p;
    }
    if (cmp(value, root->data))
        root->left = insert(root->left, value, cmp);
    else if (cmp(root->data, value))
        root->right = insert(root->right, value, cmp);
    else // root->data == value
        return root;
    return rebalance(root);
}

template <typename T, typename Comp = std::less<T>>
void insert(AVLTree<T, Comp> &tree, const T &value)
{
    tree.root = insert(tree.root, value, tree.cmp);
}

template <typename T>
AVLNode<T> *findLeftMost(AVLNode<T> *root)
{
    if (root == nullptr)
        return nullptr;
    while (root->left != nullptr)
        root = root->left;
    return root;
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *findLeftMost(const AVLTree<T, Comp> &tree)
{
    return findLeftMost(tree.root);
}

template <typename T>
AVLNode<T> *findRightMost(AVLNode<T> *root)
{
    if (root == nullptr)
        return nullptr;
    while (root->right != nullptr)
        root = root->right;
    return root;
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *findRightMost(const AVLTree<T, Comp> &tree)
{
    return findRightMost(tree.root);
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *remove(AVLNode<T> *root, const T &value, const Comp &cmp = Comp())
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
            AVLNode<T> *child = (root->left != nullptr) ? root->left : root->right;
            delete root;
            return child; // có thể là nullptr.
        }
        else // root->left != nullptr && root->right != nullptr
        {
            AVLNode<T> *temp = findRightMost(root->left);
            root->data = temp->data;
            root->left = remove(root->left, temp->data, cmp);
        }
    }
    return rebalance(root);
}

template <typename T, typename Comp = std::less<T>>
void remove(AVLTree<T, Comp> &tree, const T &value)
{
    tree.root = remove(tree.root, value, tree.cmp);
}

template <typename T, typename Comp = std::less<T>>
bool contains(AVLNode<T> *root, const T &value, const Comp &cmp = Comp())
{
    AVLNode<T> *curr = root;
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
bool contains(const AVLTree<T, Comp> &tree, const T &value)
{
    return contains(tree.root, value, tree.cmp);
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *find(AVLNode<T> *root, const T &value, const Comp &cmp = Comp())
{
    AVLNode<T> *curr = root;
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
AVLNode<T> *find(const AVLTree<T, Comp> &tree, const T &value)
{
    return find(tree.root, value, tree.cmp);
}

template <typename T>
AVLNode<T> *kthSmallest(AVLNode<T> *root, int k)
{
    if (root == nullptr || k <= 0 || k > size(root))
        return nullptr;
    AVLNode<T> *curr = root;
    while (curr != nullptr)
    {
        int leftSize = size(curr->left);
        if (k == leftSize + 1)
            return curr;
        else if (k <= leftSize)
            curr = curr->left;
        else
        {
            curr = curr->right;
            k -= leftSize + 1;
        }
    }
    return nullptr;
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *kthSmallest(const AVLTree<T, Comp> &tree, int k)
{
    return kthSmallest(tree.root, k);
}

template <typename T>
AVLNode<T> *kthBiggest(AVLNode<T> *root, int k)
{
    if (root == nullptr || k <= 0 || k > size(root))
        return nullptr;
    return kthSmallest(root, size(root) - k + 1);
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *kthBiggest(const AVLTree<T, Comp> &tree, int k)
{
    return kthBiggest(tree.root, k);
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *lowerBound(AVLNode<T> *root, const T &value, const Comp &cmp = Comp())
{
    AVLNode<T> *ans = nullptr, *curr = root;
    while (curr != nullptr)
    {
        if (!cmp(curr->data, value))
        {
            ans = curr;        // lưu node hợp lệ hiện tại.
            curr = curr->left; // tiếp tục tìm bên cây con trái.
        }
        else // cmp(curr->data, value)
            curr = curr->right;
    }
    return ans;
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *lowerBound(const AVLTree<T, Comp> &tree, const T &value)
{
    return lowerBound(tree.root, value, tree.cmp);
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *upperBound(AVLNode<T> *root, const T &value, const Comp &cmp = Comp())
{
    AVLNode<T> *ans = nullptr, *curr = root;
    while (curr != nullptr)
    {
        if (cmp(value, curr->data))
        {
            ans = curr;        // lưu node hợp lệ hiện tại.
            curr = curr->left; // tiếp tục tìm bên cây con trái.
        }
        else // !cmp(value, curr->data)
            curr = curr->right;
    }
    return ans;
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *upperBound(const AVLTree<T, Comp> &tree, const T &value)
{
    return upperBound(tree.root, value, tree.cmp);
}

template <typename T, typename Comp = std::less<T>>
int rank(AVLNode<T> *root, const T &value, const Comp &cmp = Comp())
{
    AVLNode<T> *curr = root;
    int count = 0;
    while (curr != nullptr)
    {
        if (cmp(curr->data, value))
        {
            count += 1 + size(curr->left);
            curr = curr->right;
        }
        else // !cmp(curr->data, value)
            curr = curr->left;
    }
    return count;
}

template <typename T, typename Comp = std::less<T>>
int rank(const AVLTree<T, Comp> &tree, const T &value)
{
    return rank(tree.root, value, tree.cmp);
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *predecessor(AVLNode<T> *root, const T &value, const Comp &cmp = Comp())
{
    AVLNode<T> *ans = nullptr, *curr = root;
    while (curr != nullptr)
    {
        if (cmp(curr->data, value))
        {
            ans = curr;         // lưu node hợp lệ hiện tại.
            curr = curr->right; // tiếp tục tìm bên cây con phải.
        }
        else // !cmp(curr->data, value)
            curr = curr->left;
    }
    return ans;
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *predecessor(const AVLTree<T, Comp> &tree, const T &value)
{
    return predecessor(tree.root, value, tree.cmp);
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *successor(AVLNode<T> *root, const T &value, const Comp &cmp = Comp())
{
    AVLNode<T> *ans = nullptr, *curr = root;
    while (curr != nullptr)
    {
        if (cmp(value, curr->data))
        {
            ans = curr;        // lưu node hợp lệ hiện tại.
            curr = curr->left; // tiếp tục tìm bên cây con trái.
        }
        else // !cmp(value, curr->data)
            curr = curr->right;
    }
    return ans;
}

template <typename T, typename Comp = std::less<T>>
AVLNode<T> *successor(const AVLTree<T, Comp> &tree, const T &value)
{
    return successor(tree.root, value, tree.cmp);
}

template <typename T>
void clear(AVLNode<T> *&root)
{
    if (root == nullptr)
        return;
    clear(root->left);
    clear(root->right);
    delete root;
    root = nullptr;
}

template <typename T, typename Comp = std::less<T>>
void clear(AVLTree<T, Comp> &tree)
{
    clear(tree.root);
}