#include "logicthinking_part1.h"
#include "src/utils/virtualio.h"
#include "src/utils/tool.h"
#include "src/02_StackAndQueue/seqstack.h"

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
#if OJ_TEST == 1
p000_POINT p000_tmp[4000001];
p000_POINT p000_arr[4000001];
#else
p000_POINT p000_tmp[100];
p000_POINT p000_arr[100];
#endif
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

/*
罗马数字转整数
oman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
Symbol      Value
I           1
V           5
X           10
L           50
C           100
D           500
M           1000
For example, two is written as II in Roman numeral, just two one's added together. Twelve is written as, XII, which is simply X+ II. The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X(10) to make 4 and 9.
X can be placed before L (50) and C (100) to make 40 and 90.
C can be placed before D (500) and M (1000) to make 400 and 900.
Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: "III"
Output: 3
Example 2:

Input: "IV"
Output: 4
Example 3:

Input: "IX"
Output: 9
Example 4:

Input: "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
Example 5:

Input: "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*/
int p051_romainToInt(const char *str)
{
    static std::map<char, int> romainMap{{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
    int i, result = 0, len = strlen(str);
    for (i = len - 1; i >= 0; i--)
    {
        if (i == len - 1 || romainMap[str[i]] >= romainMap[str[i + 1]])
            result += romainMap[str[i]];
        else
            result -= romainMap[str[i]];
    }
    return result;
}
void LogicThinking_Part1::practice_051()
{
    DEBUG<<p051_romainToInt("LVIII");
    DEBUG<<p051_romainToInt("IV");
}

/*
罗马数字转化成整数
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, two is written as II in Roman numeral, just two one's added together. Twelve is written as, XII, which is simply X + II. The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9.
X can be placed before L (50) and C (100) to make 40 and 90.
C can be placed before D (500) and M(1000) to make 400 and 900.
Given an integer, convert it to a roman numeral. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: 3
Output: "III"
Example 2:

Input: 4
Output: "IV"
Example 3:

Input: 9
Output: "IX"
Example 4:

Input: 58
Output: "LVIII"
Explanation: L = 50, V = 5, III = 3.
Example 5:

Input: 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*/
char *p052_intToRomain(int num)
{
    static std::map<int, char> romainMap{{1, 'I'}, {5, 'V'}, {10, 'X'}, {50, 'L'}, {100, 'C'}, {500, 'D'}, {1000, 'M'}};
    static char retStr[30];
    int i = 0, exp, n;
    for (exp = 1000; exp > 0; exp /= 10)
    {
        n = (num / exp) % 10;
        switch (n)
        {
        case 1:
            retStr[i++] = romainMap[exp];
            break;
        case 2:
            retStr[i++] = romainMap[exp];
            retStr[i++] = romainMap[exp];
            break;
        case 3:
            retStr[i++] = romainMap[exp];
            retStr[i++] = romainMap[exp];
            retStr[i++] = romainMap[exp];
            break;
        case 4:
            retStr[i++] = romainMap[exp];
            retStr[i++] = romainMap[5 * exp];
            break;
        case 5:
            retStr[i++] = romainMap[5 * exp];
            break;
        case 6:
            retStr[i++] = romainMap[5 * exp];
            retStr[i++] = romainMap[exp];
            break;
        case 7:
            retStr[i++] = romainMap[5 * exp];
            retStr[i++] = romainMap[exp];
            retStr[i++] = romainMap[exp];
            break;
        case 8:
            retStr[i++] = romainMap[5 * exp];
            retStr[i++] = romainMap[exp];
            retStr[i++] = romainMap[exp];
            break;
        case 9:
            retStr[i++] = romainMap[exp];
            retStr[i++] = romainMap[10 * exp];
            break;
        }
    }
    retStr[i] = '\0';
    return retStr;
}
void LogicThinking_Part1::practice_052()
{
    DEBUG<<p052_intToRomain(1994);
}

/*
给定一个数组，找出这个数组中每一个数右边的第一个比它大的数，如果不存在填入-1
思路：
一个数arr[i]如果右边第一个数arr[i + 1]大于arr[i]，retArr[i]存的一定是arr[i + 1]，
    利用一个栈存连续递减的arr[i]~arr[i + k]，直到arr[i + k + 1] > arr[i + k]，从栈顶往下从栈中消除值，
    最后剩余的位置填入-1
*/
void p053_buildArr(int arr[], int len, int retArr[])
{
    int i = 0;
    SeqStack<int> stack;
    while (i < len)
    {
        if (stack.getSize() == 0 || arr[stack.top()] >= arr[i])//栈为空，或者小于上一个值，入栈
        {
            stack.push(i++);
        }
        else
        {
            while (stack.getSize() > 0 && arr[i] > arr[stack.top()])//遇到第一个大于左边的数，从栈中连续消除，直到栈为空或者栈顶值大于当前值
            {
                retArr[stack.pop()] = arr[i];
            }
        }
    }
    while (stack.getSize() > 0)//剩余位置填-1
    {
        retArr[stack.pop()] = -1;
    }
}
void LogicThinking_Part1::practice_053()
{
    int arr1[7] = {10, 50, 30, 20, 12, 40, 90};//50 90 40 40 40 90 -1
    int arr2[7];
    p053_buildArr(arr1, 7, arr2);
    DEBUG<<Tool::printArr<int>(arr2, 0, 6);
}
