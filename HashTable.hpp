/* Thư viện Hash Table. */

#include <functional>

template <typename T>
struct AVLNode
{
    T data;
    int height;
    AVLNode<T> *left, *right;
    AVLNode(const T &value) : data(value), height(1), left(nullptr), right(nullptr) {};
};

template <typename T>
int height(AVLNode<T> *root)
{
    if (root == nullptr)
        return 0;
    return root->height;
}

template <typename T>
void update(AVLNode<T> *root)
{
    if (root == nullptr)
        return;
    root->height = 1 + std::max(height(root->left), height(root->right));
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

template <typename T>
AVLNode<T> *findMax(AVLNode<T> *root)
{
    if (root == nullptr)
        return nullptr;
    while (root->right != nullptr)
        root = root->right;
    return root;
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
            AVLNode<T> *temp = findMax(root->left);
            root->data = temp->data;
            root->left = remove(root->left, temp->data, cmp);
        }
    }
    return rebalance(root);
}

template <typename T, typename Comp = std::less<T>>
bool isExisted(AVLNode<T> *root, const T &value, const Comp &cmp = Comp())
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

template <typename T>
struct HashTable
{
    AVLNode<T> **bucket;
    int bucketCount;
    int currSize;
};
