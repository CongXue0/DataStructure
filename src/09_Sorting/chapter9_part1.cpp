#include "chapter9_part1.h"
#include "src/09_Sorting/sorting.h"
#include "src/utils/tool.h"
#include <QDateTime>

/*
排序demo
*/
void Chapter9_Part1::practice_000(QString input, QString &result)
{
    const int len = 10000000;
    int *arr = new int[len];
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Tool::createRandArr(arr, len, 0, 10000);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
//    DEBUG<<Tool::printArr<int>(arr, 0, len - 1);

//    Sorting::selectSort<int>(arr, 0, len - 1);
//    Sorting::bubbleSort<int>(arr, 0, len - 1);
//    Sorting::mergeSort<int>(arr, 0, len - 1);
//    Sorting::shellSort<int>(arr, len);
    Sorting::quickSort<int>(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
//    DEBUG<<Tool::printArr<int>(arr, 0, len - 1);

    delete arr;

    //    DEBUG<<Tool::printArr<int>(arr, 0, 9);
}

/*
描述
    数轴上有n个点，对于任一闭区间 [a, b]，试计算落在其内的点数。

输入
    第一行包括两个整数：点的总数n，查询的次数m。
    第二行包含n个数，为各个点的坐标。
    以下m行，各包含两个整数：查询区间的左、右边界a和b。

输出
对每次查询，输出落在闭区间[a, b]内点的个数。

样例
Input
    5 2
    1 3 7 9 11
    4 6
    7 12
Output
    0
    3

限制
    0 ≤ n, m ≤ 5×105
    对于每次查询的区间[a, b]，都有a ≤ b
    各点的坐标互异
    各点的坐标、查询区间的边界a、b，均为不超过10^7的非负整数
    时间：2 sec
    内存：256 MB
*/
int searchLeft(int arr[], int low, int high,  const int &key)//二分之左
{
    if (key <= arr[low])
    {
        return low;
    }
    else if (key == arr[high])
    {
        return high;
    }
    else if (key > arr[high])
    {
        return high + 1;
    }
    int mid;
    while (low < high)
    {
        mid = (low + high) / 2;
        if (key > arr[mid])
        {
            low = mid + 1;
        }
        else if (key < arr[mid])
        {
            high = mid;
        }
        else
        {
            return mid;
        }
    }
    return low;
}
int searchRight(int arr[], int low, int high,  const int &key)//二分之右
{
    if (key < arr[low])
    {
        return low;
    }
    else if (key == arr[low])
    {
        return low + 1;
    }
    else if (key >= arr[high])
    {
        return high + 1;
    }
    int mid;
    while (low < high)
    {
        mid = (low + high) / 2;
        if (key > arr[mid])
        {
            low = mid + 1;
        }
        else if (key < arr[mid])
        {
            high = mid;
        }
        else
        {
            return mid + 1;
        }
    }
    return high;
}
void Chapter9_Part1::practice_100(QString input, QString &result)
{
    int i, j;
    int size, count, left, right;
    int *arr = NULL;
    scanf("%d %d", &size, &count);
    if (size > 0)
        arr = new int[size];

    for (i = 0; i < size; i++)
    {
        scanf("%d", arr + i);
    }

    if (arr != NULL)
//        mergeSort(arr, 0, size - 1);
        Sorting::mergeSort<int>(arr, 0, size - 1);
    for (i = 0; i < count; i++)
    {
        scanf("%d %d", &left, &right);
        if (size <= 0)
            printf("0\n");
        else
        {
            //i1 = searchLeft(arr, 0, size - 1, left);
            //i2 = searchRight(arr, 0, size - 1, right);
            //printf("%d\n", i2 - i1);
            printf("%d\n", searchRight(arr, 0, size - 1, right) - searchLeft(arr, 0, size - 1, left));
        }
    }
    if (arr != NULL)
        delete[] arr;
}
