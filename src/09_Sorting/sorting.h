#ifndef SORTING_H
#define SORTING_H

#include "src/utils/tool.h"

class Sorting
{
public:
    Sorting() = delete;

    /* 以下为时间复杂度为O(n2)的算法 */
    template <typename T>
    static void selectSort(T arr[], int low, int high);//简单选择排序

    template <typename T>
    static void bubbleSort(T arr[], int low, int high);//冒泡排序

    template <typename T>
    static void insertSort(T arr[], int low, int high);//直接插入排序

    /* 以下为时间复杂度为O(nlogn)的算法 */
    template <typename T>
    static void shellSort(T arr[], int low, int high);//希尔排序

    template <typename T>
    static void quickSort(T arr[], int low, int high);//快速排序

    template <typename T>
    static void merge(T arr[], int low, int mid, int high);//合并
    template <typename T>
    static void mergeSort(T arr[], int low, int high);//归并排序

    template <typename T>
    static void heapAdjust(T arr[], int i, int len);
    template <typename T>
    static void heapSort(T arr[], int low, int high);//堆排序

    /* 非比较排序算法 */
    template <typename T>
    static void countSort(T arr[], int low, int high);//计数排序

    template <typename T>
    static void bucketSort(T arr[], int low, int high);//桶排序

    template <typename T>
    static void radixSort(T arr[], int low, int high);//基数排序
    template <typename T>
    static void radixSort2(T arr[], int low, int high);//基数排序2

};

/*
简单选择排序：
    简单选择排序是不稳定的排序算法
    扫面整个序列选出一个最小值与第一个元素交换，序列规模减一，再重复上两步操作直到排序完成
*/
template <typename T>
void Sorting::selectSort(T arr[], int low, int high)
{
    int i, j, min;
    T tmp;
    for (i = low; i <= high; i++)
    {
        min = i;
        for (j = i + 1; j <= high; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }
        if (min != i)
        {
            tmp = arr[i];
            arr[i] = arr[min];
            arr[min] = tmp;
        }
    }
}

/*
冒泡排序是稳定的排序算法
*/
template <typename T>
void Sorting::bubbleSort(T arr[], int low, int high)
{
    int i, j;
    bool exchange = true;
    T tmp;
    for (i = high; i > low && exchange; i--)
    {
        exchange = false;
        for (j = low; j < i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                exchange = true;
                j++;
                break;
            }
        }
        for (; j < i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

/*
直接插入排序：
    直接插入排序是稳定的排序算法
    将第一个元素视为一个已排序好的线性表，线性表之后的一个元素作为要插入的元素，将元素保持顺序插入线性表，
        线性表规模加1，重复之前步骤，直到排序完成
*/
template <typename T>
void Sorting::insertSort(T arr[], int low, int high)
{
    int i, j;
    T tmp;
    for (i = low + 1; i <= high; i++)
    {
        if (arr[i] < arr[i - 1])//如果下一个元素大于当前元素，则插入，因为当前元素是已排序好的元素中最大的
        {
            tmp = arr[i];
            for (j = i - 1; j >= 0 && arr[j] > tmp; j--)//寻找要插入的位置，并且之后的元素后移
                arr[j + 1] = arr[j];
            arr[j + 1] = tmp;
        }
    }
}

/*
希尔排序是最早的突破O(n2)算法复杂度限制的排序算法
希尔排序是不稳定的排序算法
增量序列的最后一个增量值得是1才行
希尔排序过程：
    将相差increment个增量的所有元素，视为一个子序列，对所有的子序列做插入排序，之后increment增量缩减，
        重新对所有子序列做插入排序，直到增量缩减为0
*/
template <typename T>
void Sorting::shellSort(T arr[], int low, int high)
{
    int i, j, a, increment;
    T tmp;
    for (increment = (high - low + 1) / 2; increment >= 1; increment /= 2) //选取增量
    {
        for (i = 0; i < increment; i++) //分成 increment 个组
        {
            for (j = low + i; j <= high - increment; j += increment) //对组插入排序
            {
                tmp = arr[j + increment];
                for (a = j; a >= low && arr[a] > tmp; a -= increment)
                    arr[a + increment] = arr[a];
                arr[a + increment] = tmp;
            }
        }
    }
}

/*
快速排序：
    快速排序是不稳定的排序算法
快速排序过程：
    选取第一个有元素值作为中间值tmp，不断的将小于中间值tmp的元素移入左边，大于中间值tmp的元素移入右边，
        直到中间值左边的元素都小于等于tmp，中间值右边的元素都大于等于tmp，这样一个序列就被分为了两个子序列，
        对两个子序列再重复上述步骤，直到排序完成
*/
template <typename T>
void Sorting::quickSort(T arr[], int low, int high)
{
    if (low >= high)
        return;
    int lo = low, hi = high;
    T tmp = arr[lo]; //选出中间值
    while (lo != hi)
    {
        while (lo < hi && arr[hi] >= tmp)//从右往左找到第一个小于中间值的元素移入lo位置
            hi--;
        arr[lo] = arr[hi];
        while (lo < hi && arr[lo] <= tmp)//从左往右找到第一个大于中间值的元素移入hi位置
            lo++;
        arr[hi] = arr[lo];
    }
    arr[lo] = tmp;//将中间数填入
    quickSort(arr, low, lo - 1);//左子序列做快排
    quickSort(arr, lo + 1, high);//右子序列做快排
}

/*
归并排序：
    归并排序是稳定的排序算法
*/
template <typename T>
void Sorting::merge(T arr[], int low, int mid, int high)
{
    if (low <= mid && mid < high)
    {
        int len = high - low + 1;
        T *tmp = new T[len];
        int i = low, j = mid + 1, k = 0;

        while (i <= mid && j <= high)
        {
            if (arr[i] <= arr[j])
            {
                tmp[k] = arr[i];
                k++;
                i++;
            }
            else
            {
                tmp[k] = arr[j];
                k++;
                j++;
            }
        }
        for (; i <= mid; i++, k++)//剩余表元素插入 tmp
        {
            tmp[k] = arr[i];
        }
        for (; j <= high; j++, k++)//剩余表元素插入 tmp
        {
            tmp[k] = arr[j];
        }

        for (i = 0; i < len; i++)
        {
            arr[low + i] = tmp[i];
        }
        delete[] tmp;
    }
}

template <typename T>
void Sorting::mergeSort(T arr[], int low, int high)//归并排序
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);//合并两个序列
    }
}

/*
堆排序：
    堆排序是不稳定的排序算法
    堆排序是利用堆数据结构进行排序的算法，堆是一颗完全二叉树，结点的标号是连续的
大顶堆：
    所有节点均大于等于两颗子树中的最大值
大顶堆：
    所有节点均小于等于两颗子树中的最小值
排序步骤：
    1. 先选取堆的最后一个结点的父结点作为初始位置，假设数组从0下标开始，则初始下标的计算方式为 len / 2 - 1
    2. 从初始下标 i 开始构建大顶堆，将 i 结点与左右子树做比较，如果左右子树中较大者大于i结点，则将其值交换，
        i指向交换的子树标号，重新比较，否则停止交换
    3. 每一次交换完成 i--
    4. 大顶堆构造完成后，接着就是输出元素，将大顶堆堆顶arr[0] 与 堆尾arr[len - 1] 元素交换，最大值已经产生，
        数组长度减一，从堆顶重新调整大顶堆
    5. 调整完成后，再次输出最大元素，调整大顶堆，循环往复，直到输出所有元素，数组排序完成
*/
template <typename T>
void Sorting::heapAdjust(T arr[], int i, int len)//i 为待排序的堆的堆顶，len 为堆的元素个数
{
    int j;
    T tmp;
    tmp = arr[i];//将 i 视为要排序的堆顶序号，将堆顶结点备份出来
    for (j = 2 * i + 1; j < len; j = 2 * j + 1)
    {
        if (j + 1 < len && arr[j] < arr[j + 1])//从左右子树中选取较大的结点
            j++;
        if (arr[j] > tmp)//如果子树的值大于父结点，则将子树赋给父结点，更新备份结点的插入位置，否则跳出循环
        {
            arr[i] = arr[j];
            i = j;
        }
        else
            break;
    }
    arr[i] = tmp;//将初始堆顶结点插入到第一个>=的位置（将比较路径上的结点视为一个顺序表）
}

template <typename T>
void Sorting::heapSort(T arr[], int low, int high)//堆排序
{
    T *pArr = arr + low;
    int len = high - low + 1, i;
    T tmp;
    for (i = len / 2 - 1; i >= 0; i--)
        heapAdjust(pArr, i, len);//构建大顶堆

    for (i = len - 1; i > 0; i--)
    {
        tmp = pArr[0];//堆顶元素与末尾元素交换，
        pArr[0] = pArr[i];
        pArr[i] = tmp;

        heapAdjust(pArr, 0, i);
    }
}

/*
计数排序：
    计数排序是稳定的排序算法
    计数排序的输入为 n 个 0 到 k 之间的整数，时间复杂度为O(n + k)，
        计数排序的输入数据的最大值不易过大，一般应小于1000000，过大会导致占用大量内存
计数排序过程：
    1. 备份排序数组到copyArr，并查找到最大元素maxElem
    2. 创建统计数组countArr，元素个数为maxElem + 1，并初始化为0
    3. 以元素的值作为索引在统计数组对应的位置使值加一 countArr[copyArr[i]]++; ，从位置1开始，
        每一个统计数组的值都加上前一个值，用来表示当前位置的元素（包含自身）有多少个<=的元素。
    4. 从末尾向前遍历拷贝数组，通过数组的值和统计数组来计算元素排序后的位置 tmp = copyArr[i]; index = countArr[tmp] - 1; ，
        之后将元素存入排序数组 pArr[index] = tmp; ，统计数组对应的位置的值减一 countArr[tmp]--;
        这一步是为了使相同值的元素排在当前元素的左边，由于元素是从右向左遍历，相同值之间的顺序不会改变，使得算法稳定。
*/
template <typename T>
void Sorting::countSort(T arr[], int low, int high)
{
    T *pArr = arr + low;
    int len = high - low + 1, i, j;
    T /*tmp, */maxElem;
    T *copyArr = new T[len];//备份数组
    T *countArr;//统计数组
    for (i = 0; i < len; i++)//备份数组
        copyArr[i] = pArr[i];
    for (i = 1, j = 0; i < len; i++)//查找最大值
    {
        if (copyArr[i] > copyArr[j])
            j = i;
    }
    maxElem = pArr[j];
    countArr = new T[maxElem + 1];
    for (i = 0; i <= maxElem; i++)//初始化统计数组
        countArr[i] = 0;

    //统计每个元素出现的次数，再统计元素值到0之间的元素个数
    for (i = 0; i < len; i++)
        countArr[copyArr[i]]++;
    for (i = 1; i <= maxElem; i++)
        countArr[i] += countArr[i - 1];

    for (i = len - 1; i >= 0; i--)//从后往前遍历是为了排序的稳定性
    {
//        tmp = copyArr[i];//当前待排序的元素
//        j = countArr[tmp] - 1;//根据统计数组，计算得元素排序后位置
//        pArr[j] = tmp;//元素填入排序数组
//        countArr[tmp]--;//待排序的元素的统计次数减一，用于将重复元素放在其左边

        //简便写法
        pArr[(countArr[copyArr[i]]--) - 1] = copyArr[i];
    }

    delete[] copyArr;
    delete[] countArr;
}

/*
桶排序：
    桶排序是稳定的排序算法
    桶排序的输入为 n 个 0 到 k 之间的整数，时间复杂度为O(n + k)，和计数排序一样，输入数据的最大值也不能过大
    由于操作次数比计数排序少，效率要比计数排序更高，所占空间也比计数排序少
计数排序过程：
    1. 在排序数组查找到最大元素maxElem，创建桶数组buckets，元素个数为maxElem + 1，并初始化为0
    2. 以元素的值作为索引在桶数组对应的位置使值加一 buckets[arr[i]]++; ，用来表示当前位置的元素的个数
    3. 遍历桶，根据桶的序号输出元素的值
*/
template <typename T>
void Sorting::bucketSort(T arr[], int low, int high)
{
    int i, j;
    T *buckets;//桶数组
    T maxElem;
    for (i = low + 1, j = low; i <= high; i++)
    {
        if (arr[i] > arr[j])
            j = i;
    }
    maxElem = arr[j];
    buckets = new T[maxElem + 1];
    for (i = 0; i <= maxElem; i++)//初始化桶
        buckets[i] = 0;

    for (i = low; i <= high; i++)//对所有元素做计数
        buckets[arr[i]]++;

    for (i = 0, j = low; i <= maxElem; i++)//遍历整个桶数组
    {
//        while (buckets[i] > 0)//桶内个数大于0表示该元素的个数
//        {
//            buckets[i]--;
//            arr[j] = i;
//            j++;
//        }

        //简便写法
        while ((buckets[i]--) > 0)//桶内个数大于0表示该元素的个数
            arr[j++] = i;
    }
    delete[] buckets;
}

/*
基数排序：
    基数排序是稳定的排序算法
    基数排序结合了计数排序和桶排序各自的优点，桶排序的输入为 n 个 0 到 k 之间的整数，时间复杂度为O(r * n)，r为k的最高位位数，
        和计数排序 桶排序不同，输入数据的最大值可以很大
基数排序过程：
    1. 基数排序的桶数组的大小和选取的进制数有关，这里选用的是10进制排序，所以桶的大小是10
    2. 从个位到最高位，将所有元素按照当前的位数上的对应的值放入对应的桶中，然后对桶数组进行计数排序，
        这样就算出了根据位上的值进行排序后的结果，直到排序完最高位为止，排序完成
*/
template <typename T>
void Sorting::radixSort(T arr[], int low, int high)
{
    T *pArr = arr + low;
    int len = high - low + 1, exp, i, j;
    T /*tmp, */maxElem;
    T buckets[10];//桶数组
    T *copyArr = new T[len];//备份数组

    for (i = 1, j = 0; i < len; i++)//查找最大值
    {
        if (pArr[i] > pArr[j])
            j = i;
    }
    maxElem = arr[j];

    for (exp = 1; maxElem / exp > 0; exp *= 10)
    {
        for (i = 0; i < 10; i++)//桶数组初始化
            buckets[i] = 0;
        for (i = 0; i < len; i++)//排序数组备份
            copyArr[i] = pArr[i];

        //统计每个元素出现的次数，再统计元素值到0之间的元素个数
        for (i = 0; i < len; i++)
            buckets[(copyArr[i] / exp) % 10]++;
        for (i = 1; i < 10; i++)
            buckets[i] += buckets[i - 1];

        for (i = len - 1; i >= 0; i--)
        {
//            tmp = copyArr[i];
//            j = buckets[(tmp / exp) % 10] - 1;
//            pArr[j] = tmp;
//            buckets[(tmp / exp) % 10]--;

            //简便写法
            pArr[(buckets[(copyArr[i] / exp) % 10]--) - 1] = copyArr[i];
        }
    }

    delete[] copyArr;
}

template <typename T>
void Sorting::radixSort2(T arr[], int low, int high)//以1024作为进制
{
    T *pArr = arr + low;
    int len = high - low + 1, exp, i, j;
    T /*tmp, */maxElem;
    T buckets[1024];//桶数组
    T *copyArr = new T[len];//备份数组

    for (i = 1, j = 0; i < len; i++)//查找最大值
    {
        if (pArr[i] > pArr[j])
            j = i;
    }
    maxElem = arr[j];

    for (exp = 1; maxElem / exp > 0; exp *= 1024)
    {
        for (i = 0; i < 1024; i++)//桶数组初始化
            buckets[i] = 0;
        for (i = 0; i < len; i++)//排序数组备份
            copyArr[i] = pArr[i];

        //统计每个元素出现的次数，再统计元素值到0之间的元素个数
        for (i = 0; i < len; i++)
            buckets[(copyArr[i] / exp) % 1024]++;
        for (i = 1; i < 1024; i++)
            buckets[i] += buckets[i - 1];

        for (i = len - 1; i >= 0; i--)
        {
//            tmp = copyArr[i];
//            j = buckets[(tmp / exp) % 10] - 1;
//            pArr[j] = tmp;
//            buckets[(tmp / exp) % 10]--;

            //简便写法
            pArr[(buckets[(copyArr[i] / exp) % 1024]--) - 1] = copyArr[i];
        }
    }

    delete[] copyArr;
}

#endif // SORTING_H
