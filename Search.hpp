/* Thư viện Search. */
/* Chú ý kiểu dữ liệu:
01. const T& --> không copy (&) và không cho phép thay đổi (const).
02. T& --> không copy (&) và cho phép thay đổi (no const). */
// Chú ý điều kiện vòng lặp.

#include <functional> // Chứa std::less<> mặc định.

/* Linear search (Sequential search):
- Vietnamese: Tìm kiếm tuyến tính (Tìm kiếm tuần tự).
- Range: [left, right].
- Time complexity: O(n).
- Space complexity: O(1).
- Return: index of the first occurrence of value in array (if found), otherwise return -1. */

template <typename T>
int linearSearch(T arr[], int left, int right, const T &value)
{
    for (int i = left; i <= right; i++)
    {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

template <typename T>
int linearSearch(T arr[], int sizeArr, const T &value)
{
    return linearSearch(arr, 0, sizeArr - 1, value);
}

/* Binary search:
- Vietnamese: Tìm kiếm nhị phân.
- Condition: array must be sorted according to comparator
(mảng được sắp xếp, hay mảng là một dãy đơn điệu theo comparator).
- Range: [left, right].
- Time complexity: O(log n).
- Space complexity: O(1) (loop), O(log n) (recursion).
- Return: index of value in array (if found), otherwise return -1. */

// Loop version.

template <typename T, typename Comp = std::less<T>>
int binarySearch(T arr[], int left, int right, const T &value, const Comp &cmp = Comp())
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == value)
            return mid;
        else if (cmp(arr[mid], value))
            left = mid + 1;
        else // cmp(value, arr[mid])
            right = mid - 1;
    }
    return -1;
}

template <typename T, typename Comp = std::less<T>>
int binarySearch(T arr[], int sizeArr, const T &value, const Comp &cmp = Comp())
{
    return binarySearch(arr, 0, sizeArr - 1, value, cmp);
}

// Recursion version.

template <typename T, typename Comp = std::less<T>>
int binarySearchRecursion(T arr[], int left, int right, const T &value, const Comp &cmp = Comp())
{
    if (left > right)
        return -1;
    int mid = left + (right - left) / 2;
    if (arr[mid] == value)
        return mid;
    else if (cmp(arr[mid], value))
        return binarySearchRecursion(arr, mid + 1, right, value, cmp);
    else // cmp(value, arr[mid])
        return binarySearchRecursion(arr, left, mid - 1, value, cmp);
}

template <typename T, typename Comp = std::less<T>>
int binarySearchRecursion(T arr[], int sizeArr, const T &value, const Comp &cmp = Comp())
{
    return binarySearchRecursion(arr, 0, sizeArr - 1, value, cmp);
}

/* Binary search first occurrence:
- Vietnamese: Tìm kiếm nhị phân phần tử xuất hiện đầu tiên.
- Condition: array must be sorted according to comparator
(mảng được sắp xếp, hay mảng là một dãy đơn điệu theo comparator).
- Range: [left, right].
- Time complexity: O(log n).
- Space complexity: O(1) (loop), O(log n) (recursion).
- Return: index of the first occurrence of value in array (if found), otherwise return -1. */

// Loop version.

template <typename T, typename Comp = std::less<T>>
int binarySearchFirst(T arr[], int left, int right, const T &value, const Comp &cmp = Comp())
{
    int index = -1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == value)
        {
            index = mid;     // lưu vị trí tìm thấy.
            right = mid - 1; // tiếp tục tìm bên trái.
        }
        else if (cmp(arr[mid], value))
            left = mid + 1;
        else // cmp(value, arr[mid])
            right = mid - 1;
    }
    return index;
}

template <typename T, typename Comp = std::less<T>>
int binarySearchFirst(T arr[], int sizeArr, const T &value, const Comp &cmp = Comp())
{
    return binarySearchFirst(arr, 0, sizeArr - 1, value, cmp);
}

// Recursion version.

template <typename T, typename Comp = std::less<T>>
int binarySearchFirstRecursion(T arr[], int left, int right, const T &value, const Comp &cmp = Comp())
{
    if (left > right)
        return -1;
    int mid = left + (right - left) / 2;
    if (arr[mid] == value)
    {
        int leftResult = binarySearchFirstRecursion(arr, left, mid - 1, value, cmp);
        return (leftResult == -1) ? mid : leftResult;
    }
    else if (cmp(arr[mid], value))
        return binarySearchFirstRecursion(arr, mid + 1, right, value, cmp);
    else // cmp(value, arr[mid])
        return binarySearchFirstRecursion(arr, left, mid - 1, value, cmp);
}

template <typename T, typename Comp = std::less<T>>
int binarySearchFirstRecursion(T arr[], int sizeArr, const T &value, const Comp &cmp = Comp())
{
    return binarySearchFirstRecursion(arr, 0, sizeArr - 1, value, cmp);
}

/* Binary search last occurrence:
- Vietnamese: Tìm kiếm nhị phân phần tử xuất hiện cuối cùng.
- Condition: array must be sorted according to comparator
(mảng được sắp xếp, hay mảng là một dãy đơn điệu theo comparator).
- Range: [left, right].
- Time complexity: O(log n).
- Space complexity: O(1) (loop), O(log n) (recursion).
- Return: index of the last occurrence of value in array (if found), otherwise return -1. */

// Loop version.

template <typename T, typename Comp = std::less<T>>
int binarySearchLast(T arr[], int left, int right, const T &value, const Comp &cmp = Comp())
{
    int index = -1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == value)
        {
            index = mid;    // lưu vị trí tìm thấy.
            left = mid + 1; // tiếp tục tìm bên phải.
        }
        else if (cmp(arr[mid], value))
            left = mid + 1;
        else // cmp(value, arr[mid])
            right = mid - 1;
    }
    return index;
}

template <typename T, typename Comp = std::less<T>>
int binarySearchLast(T arr[], int sizeArr, const T &value, const Comp &cmp = Comp())
{
    return binarySearchLast(arr, 0, sizeArr - 1, value, cmp);
}

// Recursion version.

template <typename T, typename Comp = std::less<T>>
int binarySearchLastRecursion(T arr[], int left, int right, const T &value, const Comp &cmp = Comp())
{
    if (left > right)
        return -1;
    int mid = left + (right - left) / 2;
    if (arr[mid] == value)
    {
        int rightResult = binarySearchLastRecursion(arr, mid + 1, right, value, cmp);
        return (rightResult == -1) ? mid : rightResult;
    }
    else if (cmp(arr[mid], value))
        return binarySearchLastRecursion(arr, mid + 1, right, value, cmp);
    else // cmp(value, arr[mid])
        return binarySearchLastRecursion(arr, left, mid - 1, value, cmp);
}

template <typename T, typename Comp = std::less<T>>
int binarySearchLastRecursion(T arr[], int sizeArr, const T &value, const Comp &cmp = Comp())
{
    return binarySearchLastRecursion(arr, 0, sizeArr - 1, value, cmp);
}