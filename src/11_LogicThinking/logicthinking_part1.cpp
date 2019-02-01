#include "logicthinking_part1.h"
#include "src/utils/virtualio.h"
#include "src/utils/tool.h"

/*
灯塔(LightHouse)：
描述
海上有许多灯塔，为过路船只照明。
（图一）
如图一所示，每个灯塔都配有一盏探照灯，照亮其东北、西南两个对顶的直角区域。探照灯的功率之大，足以覆盖任何距离。灯塔本身是如此之小，可以假定它们不会彼此遮挡。
（图二）
若灯塔A、B均在对方的照亮范围内，则称它们能够照亮彼此。比如在图二的实例中，蓝、红灯塔可照亮彼此，蓝、绿灯塔则不是，红、绿灯塔也不是。
现在，对于任何一组给定的灯塔，请计算出其中有多少对灯塔能够照亮彼此。

输入
共n+1行。
第1行为1个整数n，表示灯塔的总数。
第2到n+1行每行包含2个整数x, y，分别表示各灯塔的横、纵坐标。

输出
1个整数，表示可照亮彼此的灯塔对的数量。

样例
Input
3
2 2
4 3
5 1
Output
1

限制
对于90%的测例：1 ≤ n ≤ 3×10^5
对于95%的测例：1 ≤ n ≤ 10^6
全部测例：1 ≤ n ≤ 4×10^6
灯塔的坐标x, y是整数，且不同灯塔的x, y坐标均互异
1 ≤ x, y ≤ 10^8
时间：2 sec
内存：256 MB
提示
注意机器中整型变量的范围，C/C++中的int类型通常被编译成32位整数，其范围为[-231, 231 - 1]，不一定足够容纳本题的输出。

解题思路：
解题的关键是在x坐标有序的前提下，求y逆序对的数量，利用归并排序，顺便也能求得y逆序对的数量
*/
#define INT64 long long
typedef struct
{
    int x, y;
} p000_POINT;
INT64 p000_reverseCount;
//p000_POINT p000_tmp[4000001];
//p000_POINT p000_arr[4000001];
p000_POINT p000_tmp[100];//oj上使用上面的大小
p000_POINT p000_arr[100];
void p000_xmerge(p000_POINT arr[], int low, int mid, int high)
{
    if (low <= mid && mid < high)
    {
        int len = high - low + 1;
        int i = low, j = mid + 1, k = 0;

        while (i <= mid && j <= high)
        {
            if (arr[i].x <= arr[j].x)
            {
                p000_tmp[k++] = arr[i++];
            }
            else
            {
                p000_tmp[k++] = arr[j++];
            }
        }
        while (i <= mid)//剩余表元素插入 p000_tmp
            p000_tmp[k++] = arr[i++];
        while (j <= high)//剩余表元素插入 p000_tmp
            p000_tmp[k++] = arr[j++];

        memcpy(arr + low, p000_tmp, sizeof(p000_POINT) * len);
    }
}
void p000_xmergeSort(p000_POINT arr[], int low, int high)//归并排序
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        p000_xmergeSort(arr, low, mid);
        p000_xmergeSort(arr, mid + 1, high);
        p000_xmerge(arr, low, mid, high);//合并两个序列
    }
}
void p000_ymerge(p000_POINT arr[], int low, int mid, int high)
{
    if (low <= mid && mid < high)
    {
        int len = high - low + 1;
        int i = low, j = mid + 1, k = 0;
        int revLen = mid - low + 1;

        while (i <= mid && j <= high)
        {
            if (arr[i].y <= arr[j].y)
            {
                p000_tmp[k++] = arr[i++];
                --revLen;
            }
            else
            {
                p000_tmp[k++] = arr[j++];
                p000_reverseCount += revLen;
            }
        }
        while (i <= mid)//剩余表元素插入 p000_tmp
            p000_tmp[k++] = arr[i++];
        while (j <= high)//剩余表元素插入 p000_tmp
            p000_tmp[k++] = arr[j++];

        memcpy(arr + low, p000_tmp, sizeof(p000_POINT) * len);
    }
}
void p000_ymergeSort(p000_POINT arr[], int low, int high)//归并排序
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        p000_ymergeSort(arr, low, mid);
        p000_ymergeSort(arr, mid + 1, high);
        p000_ymerge(arr, low, mid, high);//合并两个序列
    }
}
void LogicThinking_Part1::practice_000()
{
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20); // 设置I/O缓冲区，加速读写
    int i;
    INT64 n;
    SCANF("%d", &n);

    for (i = 0; i < n; i++)
        SCANF("%d %d", &p000_arr[i].x, &p000_arr[i].y);

    p000_reverseCount = 0;
    p000_xmergeSort(p000_arr, 0, n - 1);
    p000_ymergeSort(p000_arr, 0, n - 1);

    PRINTF("%lld", n * (n - 1) / 2 - p000_reverseCount);
}

/*
用递归的方式判断一个数是否是2的指数，并输出指数的对数
*/
int power(int num, int lvl)
{
    if (num == 1)
        return lvl;
    return power(num >> 1, lvl + 1);
}
int getPower(int num)
{
    if (num <= 0 || (num & (num - 1)) != 0)
        return -1;
    return power(num, 0);
}
void LogicThinking_Part1::practice_050()
{
    int a = 128;
    DEBUG<<"a power:"<<getPower(a);
}
