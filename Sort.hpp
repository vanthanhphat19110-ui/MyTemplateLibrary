/* Thư viện Sort. */
/* Chú ý kiểu dữ liệu:
01. const T& --> không copy (&) và không cho phép thay đổi (const).
02. T& --> không copy (&) và cho phép thay đổi (no const). */
// Chú ý điều kiện vòng lặp.

#include <functional> // chứa std::less<> mặc định.

template <typename T>
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

/* Selection sort:
- Vietnamese: Sắp xếp chọn.
- Range: [left, right].
- Time complexity: O(n^2) (best case), O(n^2) (worst case).
- Space complexity: O(1) (worst case).
- Stability: No.
- In-place: Yes. */

template <typename T, typename Comp = std::less<T>>
void selectionSort(T arr[], int left, int right, const Comp &cmp = Comp())
{
    for (int i = left; i <= right; i++)
    {
        int selected = i;
        for (int j = i + 1; j <= right; j++)
        {
            if (cmp(arr[j], arr[selected]))
                selected = j;
        }
        if (selected != i)
            mySwap(arr[i], arr[selected]);
    }
}

template <typename T, typename Comp = std::less<T>>
void selectionSort(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    selectionSort(arr, 0, sizeArr - 1, cmp);
}

/* Insertion sort:
- Vietnamese: Sắp xếp chèn.
- Range: [left, right].
- Time complexity: O(n) (best case), O(n^2) (worst case).
- Space complexity: O(1) (worst case).
- Stability: Yes.
- In-place: Yes. */

// Swap version.

template <typename T, typename Comp = std::less<T>>
void insertionSortSwap(T arr[], int left, int right, const Comp &cmp = Comp())
{
    for (int i = left + 1; i <= right; i++)
    {
        int j = i;
        while (j > left && cmp(arr[j], arr[j - 1]))
        {
            mySwap(arr[j - 1], arr[j]);
            j--;
        }
    }
}

template <typename T, typename Comp = std::less<T>>
void insertionSortSwap(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    insertionSortSwap(arr, 0, sizeArr - 1, cmp);
}

// Shift version.

template <typename T, typename Comp = std::less<T>>
void insertionSortShift(T arr[], int left, int right, const Comp &cmp = Comp())
{
    for (int i = left + 1; i <= right; i++)
    {
        T curr = arr[i];
        int j = i - 1;
        while (j >= left && cmp(curr, arr[j]))
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = curr;
    }
}

template <typename T, typename Comp = std::less<T>>
void insertionSortShift(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    insertionSortShift(arr, 0, sizeArr - 1, cmp);
}

/* Binary insertion sort:
- Vietnamese: Sắp xếp chèn nhị phân.
- Range: [left, right].
- Time complexity: O(n^2) (best case), O(n^2) (worst case).
- Space complexity: O(1) (worst case).
- Stability: Yes.
- In-place: Yes. */

template <typename T, typename Comp = std::less<T>>
int upperBound(T arr[], int left, int right, const T &value, const Comp &cmp = Comp())
{
    int index = right + 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (cmp(value, arr[mid]))
        {
            index = mid;     // lưu vị trí hợp lệ hiện tại.
            right = mid - 1; // tiếp tục tìm bên trái.
        }
        else // !cmp(value, arr[mid])
            left = mid + 1;
    }
    return index;
}

// Swap version.

template <typename T, typename Comp = std::less<T>>
void binaryInsertionSortSwap(T arr[], int left, int right, const Comp &cmp = Comp())
{
    for (int i = left + 1; i <= right; i++)
    {
        int j = i;
        int pos = upperBound(arr, left, i - 1, arr[i], cmp);
        while (j > pos)
        {
            mySwap(arr[j - 1], arr[j]);
            j--;
        }
    }
}

template <typename T, typename Comp = std::less<T>>
void binaryInsertionSortSwap(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    binaryInsertionSortSwap(arr, 0, sizeArr - 1, cmp);
}

// Shift version.

template <typename T, typename Comp = std::less<T>>
void binaryInsertionSortShift(T arr[], int left, int right, const Comp &cmp = Comp())
{
    for (int i = left + 1; i <= right; i++)
    {
        T curr = arr[i];
        int j = i - 1;
        int pos = upperBound(arr, left, i - 1, curr, cmp);
        while (j >= pos)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = curr;
    }
}

template <typename T, typename Comp = std::less<T>>
void binaryInsertionSortShift(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    binaryInsertionSortShift(arr, 0, sizeArr - 1, cmp);
}

/* Bubble sort:
- Vietnamese: Sắp xếp nổi bọt.
- Range: [left, right].
- Time complexity: O(n) (best case), O(n^2) (worst case).
- Space complexity: O(1) (worst case).
- Stability: Yes.
- In-place: Yes. */

template <typename T, typename Comp = std::less<T>>
void bubbleSort(T arr[], int left, int right, const Comp &cmp = Comp())
{
    int size = right - left + 1;
    for (int i = 0; i < size - 1; i++)
    {
        bool swapped = false;
        for (int j = left; j < right - i; j++)
        {
            if (cmp(arr[j + 1], arr[j]))
            {
                mySwap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

template <typename T, typename Comp = std::less<T>>
void bubbleSort(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    bubbleSort(arr, 0, sizeArr - 1, cmp);
}

/* Cocktail shaker sort (bidirectional bubble sort):
- Vietnamese: Sắp xếp kiểu pha cocktail (Sắp xếp nổi bọt hai chiều).
- Range: [left, right].
- Time complexity: O(n) (best case), O(n^2) (worst case).
- Space complexity: O(1) (worst case).
- Stability: Yes.
- In-place: Yes. */

template <typename T, typename Comp = std::less<T>>
void cocktailShakerSort(T arr[], int left, int right, const Comp &cmp = Comp())
{
    while (left < right)
    {
        bool swapped = false;
        for (int i = left; i < right; i++)
        {
            if (cmp(arr[i + 1], arr[i]))
            {
                mySwap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        right--;
        if (!swapped)
            break;

        swapped = false;
        for (int i = right; i > left; i--)
        {
            if (cmp(arr[i], arr[i - 1]))
            {
                mySwap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        left++;
        if (!swapped)
            break;
    }
}

template <typename T, typename Comp = std::less<T>>
void cocktailShakerSort(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    cocktailShakerSort(arr, 0, sizeArr - 1, cmp);
}

/* Quick sort:
- Vietnamese: Sắp xếp nhanh.
- Range: [left, right].
- Time complexity: O(n log n) (best case), O(n^2) (worst case).
- Space complexity: O(n log n) (best case), O(n^2) (worst case).
- Stability: No.
- In-place: Yes. */

/* Lomuto Partition. */

// Chọn pivot là phần tử cuối.

template <typename T, typename Comp = std::less<T>>
void LomutoPartitionLast(T arr[], int left, int right, const Comp &cmp = Comp())
{
}

template <typename T, typename Comp = std::less<T>>
void LomutoQuickSortLast(T arr[], int left, int right, const Comp &cmp = Comp())
{
}

template <typename T, typename Comp = std::less<T>>
void LomutoQuickSortLast(T arr[], int sizeArr, const Comp &cmp = Comp())
{
}

// Chọn pivot là phần tử đầu.

template <typename T, typename Comp = std::less<T>>
void LomutoPartitionFirst(T arr[], int left, int right, const Comp &cmp = Comp())
{
}

template <typename T, typename Comp = std::less<T>>
void LomutoQuickSortFirst(T arr[], int left, int right, const Comp &cmp = Comp())
{
}

template <typename T, typename Comp = std::less<T>>
void LomutoQuickSortFirst(T arr[], int sizeArr, const Comp &cmp = Comp())
{
}

/* Hoare Partition. */

// Chọn pivot là phần tử đầu.

template <typename T, typename Comp = std::less<T>>
void HoarePartitionFirst(T arr[], int left, int right, const Comp &cmp = Comp())
{
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortFirst(T arr[], int left, int right, const Comp &cmp = Comp())
{
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortFirst(T arr[], int sizeArr, const Comp &cmp = Comp())
{
}

// Chọn pivot là phần tử cuối.

template <typename T, typename Comp = std::less<T>>
void HoarePartitionLast(T arr[], int left, int right, const Comp &cmp = Comp())
{
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortLast(T arr[], int left, int right, const Comp &cmp = Comp())
{
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortLast(T arr[], int sizeArr, const Comp &cmp = Comp())
{
}

// Chọn pivot là phần tử giữa.

template <typename T, typename Comp = std::less<T>>
void HoarePartitionMid(T arr[], int left, int right, const Comp &cmp = Comp())
{
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortMid(T arr[], int left, int right, const Comp &cmp = Comp())
{
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortMid(T arr[], int sizeArr, const Comp &cmp = Comp())
{
}

// Chọn pivot là trung vị của phần tử đầu, phần tử giữa, phần tử cuối.

template <typename T, typename Comp = std::less<T>>
void HoarePartitionMedian(T arr[], int left, int right, const Comp &cmp = Comp())
{
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortMedian(T arr[], int left, int right, const Comp &cmp = Comp())
{
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortMedian(T arr[], int sizeArr, const Comp &cmp = Comp())
{
}