/* Thư viện Hash Table. */

#include "AVLTree.hpp"
/* T = Pair<K, V>, Comp = ComparePair<K, V> */

template <typename K, typename V>
struct Pair
{
    K key;
    V value;
    Pair() = default;
    Pair(const K &key, const V &value) : key(key), value(value) {};
};

template <typename K, typename V>
struct ComparePair
{
    bool operator()(const Pair<K, V> &A, const Pair<K, V> &B) const
    {
        return A.key < B.key;
    }
};

template <typename K, typename V, typename HashFunc>
struct HashTable
{
    AVLTree<Pair<K, V>, ComparePair<K, V>> *buckets = nullptr;
    int tableSize = 0;
    int currSize = 0;
    HashFunc hash{};
};

// Mặc định, hash table có 101 buckets nếu không truyền tham số cụ thể.
template <typename K, typename V, typename HashFunc>
void init(HashTable<K, V, HashFunc> &ht, int bucketCount = 101)
{
    if (bucketCount <= 0)
        bucketCount = 101;
    ht.buckets = new AVLTree<Pair<K, V>, ComparePair<K, V>>[bucketCount];
    ht.tableSize = bucketCount;
    ht.currSize = 0;
}

template <typename K, typename V, typename HashFunc>
int size(const HashTable<K, V, HashFunc> &ht)
{
    return ht.currSize;
}

template <typename K, typename V, typename HashFunc>
int getBucketIndex(const HashTable<K, V, HashFunc> &ht, const K &key)
{
    size_t h = static_cast<size_t>(ht.hash(key));
    return static_cast<int>(h % ht.tableSize);
}

template <typename K, typename V, typename HashFunc>
bool contains(const HashTable<K, V, HashFunc> &ht, const K &key)
{
    int index = getBucketIndex(ht, key);
    Pair<K, V> node(key, V());
    return contains(ht.buckets[index], node);
}

template <typename K, typename V, typename HashFunc>
AVLNode<Pair<K, V>> *find(HashTable<K, V, HashFunc> &ht, const K &key)
{
    int index = getBucketIndex(ht, key);
    Pair<K, V> node(key, V());
    return find(ht.buckets[index], node);
}

template <typename K, typename V, typename HashFunc>
const AVLNode<Pair<K, V>> *find(const HashTable<K, V, HashFunc> &ht, const K &key)
{
    int index = getBucketIndex(ht, key);
    Pair<K, V> node(key, V());
    return find(ht.buckets[index], node);
}

template <typename K, typename V, typename HashFunc>
void insert(HashTable<K, V, HashFunc> &ht, const K &key, const V &value)
{
    int index = getBucketIndex(ht, key);
    Pair<K, V> node(key, value);
    if (!contains(ht.buckets[index], node))
    {
        insert(ht.buckets[index], node);
        ht.currSize++;
    }
}

template <typename K, typename V, typename HashFunc>
void remove(HashTable<K, V, HashFunc> &ht, const K &key)
{
    int index = getBucketIndex(ht, key);
    Pair<K, V> node(key, V());
    if (contains(ht.buckets[index], node))
    {
        remove(ht.buckets[index], node);
        ht.currSize--;
    }
}

template <typename K, typename V, typename HashFunc>
void clear(HashTable<K, V, HashFunc> &ht)
{
    for (int i = 0; i < ht.tableSize; i++)
        clear(ht.buckets[i]);
    delete[] ht.buckets;
    ht.buckets = nullptr;
    ht.tableSize = 0;
    ht.currSize = 0;
}