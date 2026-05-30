/* Thư viện Hash Table. */

#include "AVLTree.hpp"
/* T = Pair<K, V> */

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

template <typename K, typename V>
struct HashTable
{
    AVLTree<Pair<K, V>> *buckets;
    int tableSize;
    int currSize;
};

// Mặc định, hash table có 101 buckets nếu không truyền tham số cụ thể.
template <typename K, typename V>
void init(HashTable<K, V> &ht, int bucketCount = 101)
{
    ht.tableSize = bucketCount;
    ht.currSize = 0;
    ht.buckets = new AVLTree<Pair<K, V>>[bucketCount];
    for (int i = 0; i < bucketCount; i++)
        init(ht.buckets[i]);
}

template <typename K, typename V>
int size(const HashTable<K, V> &ht)
{
    return ht.currSize;
}

template <typename K, typename V, typename HashFunc>
int getBucketIndex(const HashTable<K, V> &ht, const K &key, const HashFunc &hash)
{
    size_t h = static_cast<size_t>(hash(key));
    return static_cast<int>(h % ht.tableSize);
}

template <typename K, typename V, typename HashFunc, typename Comp = ComparePair<K, V>>
bool isExisted(const HashTable<K, V> &ht, const K &key, const HashFunc &hash, const Comp &cmp = Comp())
{
    int index = getBucketIndex(ht, key, hash);
    Pair<K, V> node(key, V());
    return isExisted(ht.buckets[index], node, cmp);
}

template <typename K, typename V, typename HashFunc, typename Comp = ComparePair<K, V>>
const AVLNode<Pair<K, V>> *find(const HashTable<K, V> &ht, const K &key, const HashFunc &hash, const Comp &cmp = Comp())
{
    int index = getBucketIndex(ht, key, hash);
    Pair<K, V> node(key, V());
    return find(ht.buckets[index], node, cmp);
}

template <typename K, typename V, typename HashFunc, typename Comp = ComparePair<K, V>>
void insert(HashTable<K, V> &ht, const K &key, const V &value, const HashFunc &hash, const Comp &cmp = Comp())
{
    int index = getBucketIndex(ht, key, hash);
    Pair<K, V> node(key, value);
    if (!isExisted(ht.buckets[index], node, cmp))
    {
        insert(ht.buckets[index], node, cmp);
        ht.currSize++;
    }
}

template <typename K, typename V, typename HashFunc, typename Comp = ComparePair<K, V>>
void remove(HashTable<K, V> &ht, const K &key, const HashFunc &hash, const Comp &cmp = Comp())
{
    int index = getBucketIndex(ht, key, hash);
    Pair<K, V> node(key, V());
    if (isExisted(ht.buckets[index], node, cmp))
    {
        remove(ht.buckets[index], node, cmp);
        ht.currSize--;
    }
}

template <typename K, typename V>
void clear(HashTable<K, V> &ht)
{
    for (int i = 0; i < ht.tableSize; i++)
        clear(ht.buckets[i]);
    delete[] ht.buckets;
    ht.buckets = nullptr;
    ht.tableSize = 0;
    ht.currSize = 0;
}
