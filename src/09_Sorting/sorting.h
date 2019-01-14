#ifndef SORTING_H
#define SORTING_H

#include "src/utils/tool.h"

class Sorting
{
public:
    Sorting() = delete;

    template <typename T>
    static void selectSort(T arr[], int low, int high);//简单选择排序
    template <typename T>
    static void bubbleSort(T arr[], int low, int high);//冒泡排序
    template <typename T>
    static void insertSort(T arr[], int low, int high);//直接插入排序

    template <typename T>
    static void shellSort(T arr[], int low, int high);//希尔排序
    template <typename T>
    static void quickSort(T arr[], int low, int high);//快速排序
    template <typename T>
    static void merge(T arr[], int low, int mid, int high);//合并
    template <typename T>
    static void mergeSort(T arr[], int low, int high);//归并排序

    template <typename T>
    static void heapAdjust(T arr[], int s, int m);
    template <typename T>
    static void heapSort(T arr[], int low, int high);//堆排序

};

/*
简单选择排序：
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

template <typename T>
void Sorting::bubbleSort(T arr[], int low, int high)//冒泡排序
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

template <typename T>
void Sorting::quickSort(T arr[], int low, int high)
{
    if (low >= high)
        return;
    int lo = low, hi = high;
    T tmp = arr[lo];				//选出中间值
    while (lo != hi)
    {
        while (lo < hi && arr[hi] >= tmp)
            hi--;
        arr[lo] = arr[hi];
        while (lo < hi && arr[lo] <= tmp)
            lo++;
        arr[hi] = arr[lo];
    }
    arr[lo] = tmp;
    quickSort(arr, low, lo - 1);
    quickSort(arr, lo + 1, high);
}


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
    堆排序是利用堆数据结构进行排序的算法，堆是一颗完全二叉树，结点的标号是连续的
大顶堆：
    所有节点均大于等于两颗子树中的最大值
大顶堆：
    所有节点均小于等于两颗子树中的最小值
排序步骤：
    1. 先选取堆的最后一个结点的父结点最为初始位置，假设数组从0下标开始，则初始下标的计算方式为 len / 2 - 1
    2. 从初始下标 i 开始构建大顶堆，将 i 结点与左右子树做比较，如果左右子树中较大者大于i结点，则将其值交换，
        i指向交换的子树标号，重新比较，否则停止交换
    3. 每一次交换完成 i--
    4. 大顶堆构造完成后，接着就是输出元素，将大顶堆堆顶arr[0] 与 堆尾arr[len - 1] 元素交换，最大值已经产生，
        数组长度减一，从堆顶重新调整大顶堆
    5. 调整完成后，再次输出最大元素，调整大顶堆，循环往复，直到输出所有元素，数组排序完成
*/
template <typename T>
void Sorting::heapAdjust(T arr[], int i, int len)
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

#endif // SORTING_H
