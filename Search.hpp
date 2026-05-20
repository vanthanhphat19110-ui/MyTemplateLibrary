/* Thư viện Search. */
/* Chú ý kiểu dữ liệu:
01. const T& --> không copy (&) và không cho phép thay đổi (const).
02. T& --> không copy (&) và cho phép thay đổi (no const).
03. bool (*comp)(const T&, const T&) --> comparator so sánh a và b, cái nào nên đứng trước. */
// Chú ý điều kiện vòng lặp.

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
template <typename T>
int binarySearch(T arr[], int left, int right, const T &value, bool (*comp)(const T &, const T &))
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == value)
            return mid;
        else if (comp(arr[mid], value))
            left = mid + 1;
        else // comp(value, arr[mid])
            right = mid - 1;
    }
    return -1;
}

template <typename T>
int binarySearch(T arr[], int sizeArr, const T &value, bool (*comp)(const T &, const T &))
{
    return binarySearch(arr, 0, sizeArr - 1, value, comp);
}

// Recursion version.
template <typename T>
int binarySearchRecursion(T arr[], int left, int right, const T &value, bool (*comp)(const T &, const T &))
{
    if (left > right)
        return -1;
    int mid = left + (right - left) / 2;
    if (arr[mid] == value)
        return mid;
    else if (comp(arr[mid], value))
        return binarySearchRecursion(arr, mid + 1, right, value, comp);
    else // comp(value, arr[mid])
        return binarySearchRecursion(arr, left, mid - 1, value, comp);
}

template <typename T>
int binarySearchRecursion(T arr[], int sizeArr, const T &value, bool (*comp)(const T &, const T &))
{
    return binarySearchRecursion(arr, 0, sizeArr - 1, value, comp);
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
template <typename T>
int binarySearchFirst(T arr[], int left, int right, const T &value, bool (*comp)(const T &, const T &))
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
        else if (comp(arr[mid], value))
            left = mid + 1;
        else // comp(value, arr[mid])
            right = mid - 1;
    }
    return index;
}

template <typename T>
int binarySearchFirst(T arr[], int sizeArr, const T &value, bool (*comp)(const T &, const T &))
{
    return binarySearchFirst(arr, 0, sizeArr - 1, value, comp);
}

// Recursion version.
template <typename T>
int binarySearchFirstRecursion(T arr[], int left, int right, const T &value, bool (*comp)(const T &, const T &))
{
    if (left > right)
        return -1;
    int mid = left + (right - left) / 2;
    if (arr[mid] == value)
    {
        int leftResult = binarySearchFirstRecursion(arr, left, mid - 1, value, comp);
        return (leftResult == -1) ? mid : leftResult;
    }
    else if (comp(arr[mid], value))
        return binarySearchFirstRecursion(arr, mid + 1, right, value, comp);
    else // comp(value, arr[mid])
        return binarySearchFirstRecursion(arr, left, mid - 1, value, comp);
}

template <typename T>
int binarySearchFirstRecursion(T arr[], int sizeArr, const T &value, bool (*comp)(const T &, const T &))
{
    return binarySearchFirstRecursion(arr, 0, sizeArr - 1, value, comp);
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
template <typename T>
int binarySearchLast(T arr[], int left, int right, const T &value, bool (*comp)(const T &, const T &))
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
        else if (comp(arr[mid], value))
            left = mid + 1;
        else // comp(value, arr[mid])
            right = mid - 1;
    }
    return index;
}

template <typename T>
int binarySearchLast(T arr[], int sizeArr, const T &value, bool (*comp)(const T &, const T &))
{
    return binarySearchLast(arr, 0, sizeArr - 1, value, comp);
}

// Recursion version.
template <typename T>
int binarySearchLastRecursion(T arr[], int left, int right, const T &value, bool (*comp)(const T &, const T &))
{
    if (left > right)
        return -1;
    int mid = left + (right - left) / 2;
    if (arr[mid] == value)
    {
        int rightResult = binarySearchLastRecursion(arr, mid + 1, right, value, comp);
        return (rightResult == -1) ? mid : rightResult;
    }
    else if (comp(arr[mid], value))
        return binarySearchLastRecursion(arr, mid + 1, right, value, comp);
    else // comp(value, arr[mid])
        return binarySearchLastRecursion(arr, left, mid - 1, value, comp);
}

template <typename T>
int binarySearchLastRecursion(T arr[], int sizeArr, const T &value, bool (*comp)(const T &, const T &))
{
    return binarySearchLastRecursion(arr, 0, sizeArr - 1, value, comp);
}