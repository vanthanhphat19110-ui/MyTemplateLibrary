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
        arr[j + 1] = curr; // quan trọng.
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
        arr[j + 1] = curr; // quan trọng.
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
- Space complexity: O(log n) (best case), O(n) (worst case).
- Stability: No.
- In-place: Yes. */

/* Lomuto Partition. */

// Chọn pivot là phần tử cuối.

template <typename T, typename Comp = std::less<T>>
int LomutoPartitionLast(T arr[], int left, int right, const Comp &cmp = Comp())
{
    int i = left, pivot = right;
    for (int j = left; j < right; j++)
    {
        if (cmp(arr[j], arr[pivot]))
        {
            mySwap(arr[i], arr[j]);
            i++;
        }
    }
    mySwap(arr[i], arr[pivot]); // quan trọng.
    return i;
}

template <typename T, typename Comp = std::less<T>>
void LomutoQuickSortLast(T arr[], int left, int right, const Comp &cmp = Comp())
{
    if (left < right)
    {
        int pivot = LomutoPartitionLast(arr, left, right, cmp);
        LomutoQuickSortLast(arr, left, pivot - 1, cmp);  // chú ý.
        LomutoQuickSortLast(arr, pivot + 1, right, cmp); // chú ý.
    }
}

template <typename T, typename Comp = std::less<T>>
void LomutoQuickSortLast(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    LomutoQuickSortLast(arr, 0, sizeArr - 1, cmp);
}

// Chọn pivot là phần tử đầu.

template <typename T, typename Comp = std::less<T>>
int LomutoPartitionFirst(T arr[], int left, int right, const Comp &cmp = Comp())
{
    int pivot = left, i = left + 1;
    for (int j = left + 1; j <= right; j++)
    {
        if (cmp(arr[j], arr[pivot]))
        {
            mySwap(arr[i], arr[j]);
            i++;
        }
    }
    i--;                        // chú ý.
    mySwap(arr[i], arr[pivot]); // quan trọng.
    return i;
}

template <typename T, typename Comp = std::less<T>>
void LomutoQuickSortFirst(T arr[], int left, int right, const Comp &cmp = Comp())
{
    if (left < right)
    {
        int pivot = LomutoPartitionFirst(arr, left, right, cmp);
        LomutoQuickSortFirst(arr, left, pivot - 1, cmp);  // chú ý.
        LomutoQuickSortFirst(arr, pivot + 1, right, cmp); // chú ý.
    }
}

template <typename T, typename Comp = std::less<T>>
void LomutoQuickSortFirst(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    LomutoQuickSortFirst(arr, 0, sizeArr - 1, cmp);
}

/* Hoare Partition. */

// Chọn pivot là phần tử đầu.

template <typename T, typename Comp = std::less<T>>
int HoarePartitionFirst(T arr[], int left, int right, const Comp &cmp = Comp())
{
    int i = left - 1, j = right + 1;
    T pivot = arr[left];
    while (true)
    {
        do
        {
            i++;
        } while (cmp(arr[i], pivot));
        do
        {
            j--;
        } while (cmp(pivot, arr[j]));
        if (i >= j)
            break;
        mySwap(arr[i], arr[j]);
    }
    return j; // quan trọng.
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortFirst(T arr[], int left, int right, const Comp &cmp = Comp())
{
    if (left < right)
    {
        int pivot = HoarePartitionFirst(arr, left, right, cmp);
        HoareQuickSortFirst(arr, left, pivot, cmp);      // chú ý.
        HoareQuickSortFirst(arr, pivot + 1, right, cmp); // chú ý.
    }
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortFirst(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    HoareQuickSortFirst(arr, 0, sizeArr - 1, cmp);
}

// Chọn pivot là phần tử cuối.

template <typename T, typename Comp = std::less<T>>
int HoarePartitionLast(T arr[], int left, int right, const Comp &cmp = Comp())
{
    int i = left - 1, j = right + 1;
    T pivot = arr[right];
    while (true)
    {
        do
        {
            i++;
        } while (cmp(arr[i], pivot));
        do
        {
            j--;
        } while (cmp(pivot, arr[j]));
        if (i >= j)
            break;
        mySwap(arr[i], arr[j]);
    }
    return j; // quan trọng.
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortLast(T arr[], int left, int right, const Comp &cmp = Comp())
{
    if (left < right)
    {
        int pivot = HoarePartitionLast(arr, left, right, cmp);
        HoareQuickSortLast(arr, left, pivot, cmp);      // chú ý.
        HoareQuickSortLast(arr, pivot + 1, right, cmp); // chú ý.
    }
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortLast(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    HoareQuickSortLast(arr, 0, sizeArr - 1, cmp);
}

// Chọn pivot là phần tử giữa.

template <typename T, typename Comp = std::less<T>>
int HoarePartitionMid(T arr[], int left, int right, const Comp &cmp = Comp())
{
    int i = left - 1, j = right + 1;
    int mid = left + (right - left) / 2;
    T pivot = arr[mid];
    while (true)
    {
        do
        {
            i++;
        } while (cmp(arr[i], pivot));
        do
        {
            j--;
        } while (cmp(pivot, arr[j]));
        if (i >= j)
            break;
        mySwap(arr[i], arr[j]);
    }
    return j; // quan trọng.
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortMid(T arr[], int left, int right, const Comp &cmp = Comp())
{
    if (left < right)
    {
        int pivot = HoarePartitionMid(arr, left, right, cmp);
        HoareQuickSortMid(arr, left, pivot, cmp);      // chú ý.
        HoareQuickSortMid(arr, pivot + 1, right, cmp); // chú ý.
    }
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortMid(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    HoareQuickSortMid(arr, 0, sizeArr - 1, cmp);
}

// Chọn pivot là trung vị của phần tử đầu, phần tử giữa, phần tử cuối.

template <typename T, typename Comp = std::less<T>>
int getMedian(T arr[], int i, int j, int k, const Comp &cmp = Comp())
{
    if ((cmp(arr[j], arr[i]) && cmp(arr[i], arr[k])) || (cmp(arr[k], arr[i]) && cmp(arr[i], arr[j])))
        return i;
    if ((cmp(arr[i], arr[j]) && cmp(arr[j], arr[k])) || (cmp(arr[k], arr[j]) && cmp(arr[j], arr[i])))
        return j;
    return k;
}

template <typename T, typename Comp = std::less<T>>
int HoarePartitionMedian(T arr[], int left, int right, const Comp &cmp = Comp())
{
    int i = left - 1, j = right + 1;
    int mid = left + (right - left) / 2;
    int median = getMedian(arr, left, mid, right, cmp);
    T pivot = arr[median];
    while (true)
    {
        do
        {
            i++;
        } while (cmp(arr[i], pivot));
        do
        {
            j--;
        } while (cmp(pivot, arr[j]));
        if (i >= j)
            break;
        mySwap(arr[i], arr[j]);
    }
    return j; // quan trọng.
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortMedian(T arr[], int left, int right, const Comp &cmp = Comp())
{
    if (left < right)
    {
        int pivot = HoarePartitionMedian(arr, left, right, cmp);
        HoareQuickSortMedian(arr, left, pivot, cmp);      // chú ý.
        HoareQuickSortMedian(arr, pivot + 1, right, cmp); // chú ý.
    }
}

template <typename T, typename Comp = std::less<T>>
void HoareQuickSortMedian(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    HoareQuickSortMedian(arr, 0, sizeArr - 1, cmp);
}

/* Dutch National Flag Partition (Three Way Partition). */

// Chọn pivot là phần tử đầu.

template <typename T, typename Comp = std::less<T>>
void ThreeWayQuickSortFirst(T arr[], int left, int right, const Comp &cmp = Comp())
{
    if (left >= right)
        return;
    int i = left, low = left, high = right;
    T pivot = arr[left];
    while (i <= high)
    {
        if (cmp(arr[i], pivot))
            mySwap(arr[low++], arr[i++]);
        else if (cmp(pivot, arr[i]))
            mySwap(arr[i], arr[high--]);
        else // arr[i] == pivot
            i++;
    }
    ThreeWayQuickSortFirst(arr, left, low - 1, cmp);   // chú ý.
    ThreeWayQuickSortFirst(arr, high + 1, right, cmp); // chú ý.
}

template <typename T, typename Comp = std::less<T>>
void ThreeWayQuickSortFirst(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    ThreeWayQuickSortFirst(arr, 0, sizeArr - 1, cmp);
}

// Chọn pivot là phần tử cuối.

template <typename T, typename Comp = std::less<T>>
void ThreeWayQuickSortLast(T arr[], int left, int right, const Comp &cmp = Comp())
{
    if (left >= right)
        return;
    int i = left, low = left, high = right;
    T pivot = arr[right];
    while (i <= high)
    {
        if (cmp(arr[i], pivot))
            mySwap(arr[low++], arr[i++]);
        else if (cmp(pivot, arr[i]))
            mySwap(arr[i], arr[high--]);
        else // arr[i] == pivot
            i++;
    }
    ThreeWayQuickSortLast(arr, left, low - 1, cmp);   // chú ý.
    ThreeWayQuickSortLast(arr, high + 1, right, cmp); // chú ý.
}

template <typename T, typename Comp = std::less<T>>
void ThreeWayQuickSortLast(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    ThreeWayQuickSortLast(arr, 0, sizeArr - 1, cmp);
}

// Chọn pivot là phần tử giữa.

template <typename T, typename Comp = std::less<T>>
void ThreeWayQuickSortMid(T arr[], int left, int right, const Comp &cmp = Comp())
{
    if (left >= right)
        return;
    int i = left, low = left, high = right;
    int mid = left + (right - left) / 2;
    T pivot = arr[mid];
    while (i <= high)
    {
        if (cmp(arr[i], pivot))
            mySwap(arr[low++], arr[i++]);
        else if (cmp(pivot, arr[i]))
            mySwap(arr[i], arr[high--]);
        else // arr[i] == pivot
            i++;
    }
    ThreeWayQuickSortMid(arr, left, low - 1, cmp);   // chú ý.
    ThreeWayQuickSortMid(arr, high + 1, right, cmp); // chú ý.
}

template <typename T, typename Comp = std::less<T>>
void ThreeWayQuickSortMid(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    ThreeWayQuickSortMid(arr, 0, sizeArr - 1, cmp);
}

// Chọn pivot là trung vị của phần tử đầu, phần tử giữa, phần tử cuối.

template <typename T, typename Comp = std::less<T>>
void ThreeWayQuickSortMedian(T arr[], int left, int right, const Comp &cmp = Comp())
{
    if (left >= right)
        return;
    int i = left, low = left, high = right;
    int mid = left + (right - left) / 2;
    int median = getMedian(arr, left, mid, right, cmp);
    T pivot = arr[median];
    while (i <= high)
    {
        if (cmp(arr[i], pivot))
            mySwap(arr[low++], arr[i++]);
        else if (cmp(pivot, arr[i]))
            mySwap(arr[i], arr[high--]);
        else // arr[i] == pivot
            i++;
    }
    ThreeWayQuickSortMedian(arr, left, low - 1, cmp);   // chú ý.
    ThreeWayQuickSortMedian(arr, high + 1, right, cmp); // chú ý.
}

template <typename T, typename Comp = std::less<T>>
void ThreeWayQuickSortMedian(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    ThreeWayQuickSortMedian(arr, 0, sizeArr - 1, cmp);
}

/* Heap sort:
- Vietnamese: Sắp xếp đống.
- Range: [0, sizeArr - 1].
- Time complexity: O(n log n) (best case), O(n log n) (worst case).
- Space complexity: O(1) (worst case).
- Stability: No.
- In-place: Yes. */

template <typename T, typename Comp = std::less<T>>
void heapify(T arr[], int sizeArr, int node, const Comp &cmp = Comp())
{
    while (2 * node + 1 < sizeArr)
    {
        int best = node, left = 2 * node + 1, right = 2 * node + 2;
        if (left < sizeArr && cmp(arr[best], arr[left]))
            best = left;
        if (right < sizeArr && cmp(arr[best], arr[right]))
            best = right;
        if (best == node)
            break;
        mySwap(arr[node], arr[best]);
        node = best;
    }
}

template <typename T, typename Comp = std::less<T>>
void heapSort(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    for (int i = sizeArr / 2 - 1; i >= 0; i--)
        heapify(arr, sizeArr, i, cmp);
    for (int i = sizeArr - 1; i > 0; i--)
    {
        mySwap(arr[0], arr[i]);
        heapify(arr, i, 0, cmp);
    }
}

/* Merge sort:
- Vietnamese: Sắp xếp trộn.
- Range: [left, right].
- Time complexity: O(n log n) (best case), O(n log n) (worst case).
- Space complexity: O(n) (worst case).
- Stability: Yes.
- In-place: No. */

template <typename T, typename Comp = std::less<T>>
void merge(T arr[], T temp[], int left, int mid, int right, const Comp &cmp = Comp())
{
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right)
    {
        if (cmp(arr[j], arr[i]))
            temp[k++] = arr[j++];
        else
            temp[k++] = arr[i++];
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];
    for (int t = left; t <= right; t++)
        arr[t] = temp[t];
}

template <typename T, typename Comp = std::less<T>>
void mergeSort(T arr[], T temp[], int left, int right, const Comp &cmp = Comp())
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, temp, left, mid, cmp);      // chú ý.
    mergeSort(arr, temp, mid + 1, right, cmp); // chú ý.
    merge(arr, temp, left, mid, right, cmp);   // chú ý.
}

template <typename T, typename Comp = std::less<T>>
void mergeSort(T arr[], int sizeArr, const Comp &cmp = Comp())
{
    T *temp = new T[sizeArr];
    mergeSort(arr, temp, 0, sizeArr - 1, cmp);
    delete[] temp;
}