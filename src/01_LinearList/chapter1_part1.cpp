#include "chapter1_part1.h"
#include "src/utils/tool.h"
#include "src/01_LinearList/seqlist.h"
#include "src/01_LinearList/linklist.h"
#include "src/01_LinearList/doublelinklist.h"
#include "src/utils/virtualio.h"

/*
链表demo
*/
void Chapter1_Part1::practice_000()
{
//    SeqList<int> list;
//    list.insert(0, 1);
//    list.insert(0, -1);
//    list.insert(2, 3);
//    list.append(23);
//    list.append(1);
//    list.append(1);
//    list.append(3);
//    list.append(6);
//    DEBUG<<Tool::printSeqList(list);
//    list.clear();
//    DEBUG<<Tool::printSeqList(list);
}

/*
双向链表demo
*/
void Chapter1_Part1::practice_001()
{
    DoubleLinkList<int> list;
    list.append(-1);
    list.append(-2);
    list.append(0);
    list.append(4);
    list.append(99);
    list.append(200);
    list.append(134);
    DEBUG<<list.print();

    list.insert(4, -87);
    DEBUG<<list.print();

    list.removeAt(6);
    DEBUG<<list.print();

    list.clear();
    DEBUG<<list.print();
}

/*
顺序表的逆置
*/
void reverseArr(int arr[], int low, int high)
{
    int tmp;
    while (low < high)
    {
        tmp = arr[low];
        arr[low] = arr[high];
        arr[high] = tmp;
        low++, high--;
    }
}
void Chapter1_Part1::practice_002()
{
    int arr[20];
    Tool::createRandArr(arr, 20, 0, 200);
    DEBUG<<Tool::printArr(arr, 0, 19);
    reverseArr(arr, 0, 19);
    DEBUG<<Tool::printArr(arr, 0, 19);
}

/*
删除顺序表中给定区间内值在[s,t]之间的元素，要求时间复杂度为O(n)，空间复杂度为O(1)
*/
void removeAllFromArr(int arr[], int low, int high, int s, int t, int &len)
{
    int tmp1 = low, tmp2 = low;
    int num = 0;
    while (tmp2 <= high)
    {
        if (arr[tmp2] >= s && arr[tmp2] <= t)
        {
            tmp2++;
            num++;
        }
        else
        {
            arr[tmp1] = arr[tmp2];
            tmp1++, tmp2++;
        }
    }
    while (tmp2 < len)
    {
        arr[tmp1] = arr[tmp2];
        tmp1++, tmp2++;
    }
    len -= num;
}
void Chapter1_Part1::practice_003()
{
    int len = 20;
    int arr[20];
    Tool::createRandArr(arr, len, 0, 100);
    DEBUG<<Tool::printArr(arr, 0, len - 1);
    removeAllFromArr(arr, 0, len - 1, 0, 50, len);
    DEBUG<<"len:"<<len;
    DEBUG<<Tool::printArr(arr, 0, len - 1);
}

/*
已知在一维数组中依次存放着两个线性表(a1,...,am)和(b1,...,bn)，将两个线性表位置互换，要求时间复杂度O(n)，空间复杂度O(1)
*/
void exchangeArr(int arr[], int low, int mid, int high)//交换[low,mid-1] [mid,high]区间
{
    if (low >= high || mid > high || mid <= low)
        return;
    int t;
    int tmp1 = low, tmp2 = high;
    while (tmp1 < tmp2) //先逆置整个区间
    {
        t = arr[tmp1];
        arr[tmp1] = arr[tmp2];
        arr[tmp2] = t;
        tmp1++, tmp2--;
    }
    tmp1 = low, tmp2 = low + high - mid;
    while (tmp1 < tmp2) //逆置左边区间
    {
        t = arr[tmp1];
        arr[tmp1] = arr[tmp2];
        arr[tmp2] = t;
        tmp1++, tmp2--;
    }
    tmp1 = low + high - mid + 1, tmp2 = high;
    while (tmp1 < tmp2) //逆置右边区间
    {
        t = arr[tmp1];
        arr[tmp1] = arr[tmp2];
        arr[tmp2] = t;
        tmp1++, tmp2--;
    }
}
void Chapter1_Part1::practice_004()
{
    const int len = 20;
    int arr[len];
    Tool::createRandArr(arr, len, 0, 100);
    DEBUG<<Tool::printArr(arr, 0, len - 1);
    exchangeArr(arr, 0, 13, 19);
    DEBUG<<Tool::printArr(arr, 0, len - 1);
}

/*
已知一个线性表A，其拥有n个元素，如果存在一个元素x，A中存在x的个数大于n/2，则称这个x为A的主元素，请设计一个算法找出一个数组的主元素，若存在输出主元素，不存在输出-1
*/
int searchMainElem(int arr[], int low, int high)
{
    if (low >= high || high - low < 1)
        return -1;
    int x = arr[0], count = 1, i;
    for (i = low + 1; i <= high; i++) //先找出可能的主元素
    {
        if (arr[i] == x)
        {
            count++;
        }
        else
        {
            count--;
        }
        if (count == 0)
        {
            x = arr[i];
            count = 1;
        }
    }
    count = 0;
    for (i = low; i <= high; i++)
    {
        if (arr[i] == x)
            count++;
    }
    if (count > (high - low + 1) / 2)
        return x;
    else
        return -1;
}
void Chapter1_Part1::practice_005()
{
    int arr[11] = {1, 5, 5, 0, 10, 5, 5, 99, 4, 5, 5};
    DEBUG<<"main elem:"<<searchMainElem(arr, 0, 10);
}

/*
逆位序输入n个元素的值，建立单链表list
*/
void Chapter1_Part1::practice_050()
{
    QString input = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10";
    QStringList strList = input.split('\n');

    LinkList<int> list;
    for (int i = 0; i < strList.count(); i++)
    {
        list.insert(0, strList.at(i).toInt());
    }
    DEBUG<<list.print();
}

/*
已知顺序表 La 和 Lb 的元素递增排列，归并 La 和 Lb 到 Lc，使其也为递增排列
*/
void Chapter1_Part1::practice_051()
{
    SeqList<int> lista;
    lista.append(-20);
    lista.append(30);
    lista.append(100);
    SeqList<int> listb;
    listb.append(-1);
    listb.append(0);
    listb.append(1);
    listb.append(100);
    listb.append(133);
    listb.append(500);

    SeqList<int> listc;
    int ia = 0;
    int ib = 0;
    while (ia < lista.getLength() && ib < listb.getLength())//把 a b 表排序插入 c
    {
        if (lista.at(ia) <= listb.at(ib))
        {
            listc.append(lista.at(ia));
            ia++;
        }
        else
        {
            listc.append(listb.at(ib));
            ib++;
        }
    }
    for (; ia < lista.getLength(); ia++)//剩余表元素插入 c
    {
        listc.append(lista.at(ia));
    }
    for (; ib < listb.getLength(); ib++)//剩余表元素插入 c
    {
        listc.append(listb.at(ib));
    }
    DEBUG<<listc.print();
}

/*
描述
祖玛是一款曾经风靡全球的游戏，其玩法是：在一条轨道上初始排列着若干个彩色珠子，其中任意三个相邻的珠子不会完全同色。此后，你可以发射珠子到轨道上并加入原有序列中。一旦有三个或更多同色的珠子变成相邻，它们就会立即消失。这类消除现象可能会连锁式发生，其间你将暂时不能发射珠子。
开发商最近准备为玩家写一个游戏过程的回放工具。他们已经在游戏内完成了过程记录的功能，而回放功能的实现则委托你来完成。
游戏过程的记录中，首先是轨道上初始的珠子序列，然后是玩家接下来所做的一系列操作。你的任务是，在各次操作之后及时计算出新的珠子序列。

输入
    第一行是一个由大写字母'A'~'Z'组成的字符串，表示轨道上初始的珠子序列，不同的字母表示不同的颜色。
    第二行是一个数字n，表示整个回放过程共有n次操作。
    接下来的n行依次对应于各次操作。每次操作由一个数字k和一个大写字母Σ描述，以空格分隔。其中，Σ为新珠子的颜色。若插入前共有m颗珠子，则k ∈ [0, m]表示新珠子嵌入之后（尚未发生消除之前）在轨道上的位序。

输出
    输出共n行，依次给出各次操作（及可能随即发生的消除现象）之后轨道上的珠子序列。
    如果轨道上已没有珠子，则以“-”表示。

样例
Input
    ACCBA
    5
    1 B
    0 A
    2 B
    4 C
    0 A
Output
    ABCCBA
    AABCCBA
    AABBCCBA
    -
    A

限制
    0 ≤ n ≤ 10^4
    0 ≤ 初始珠子数量 ≤ 10^4
    时间：2 sec
    内存：256 MB
*/
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#define ZUMA_REMOVE_NUM 3

int zumaLen;
char zumaStr[1000001] = {0};

void printZumaStr()
{
    for (int i = 0; i < zumaLen; i++)
    {
//        VIO::printf("%c", str[i]);
        VIO::putchar(zumaStr[i]);
    }
    VIO::putchar('\n');
}
inline void zumaMemcpy(void *dst, void *src, int size)
{
    static unsigned char tmp[1000001];
    memcpy(tmp, src, size);
    memcpy(dst, tmp, size);
}
void expandRemove(int &left, int &right)//扩大删除区间
{
    int tmpLeft = left, tmpRight = right;
    char ch;
    int num;
    while (true)
    {
        ch = zumaStr[tmpRight];
        if (ch == '\0')
            break;
        num = 1;
        tmpRight++;
        while (tmpLeft > 0 && zumaStr[tmpLeft - 1] == ch)
        {
            tmpLeft--;
            num++;
        }
        while (tmpRight < zumaLen && zumaStr[tmpRight] == ch)
        {
            tmpRight++;
            num++;
        }
        if (num >= ZUMA_REMOVE_NUM)
        {
            left = tmpLeft, right = tmpRight;
        }
        else
            break;
    }
}
void shootBead(int pos, char ch)//射击珠子
{
    int left = pos, right = pos;
    while (left > 0 && zumaStr[left - 1] == ch)
    {
        left--;
    }
    while (right < zumaLen && zumaStr[right] == ch)
    {
        right++;
    }
    if (right - left + 1 >= ZUMA_REMOVE_NUM)
    {
        expandRemove(left, right);
        //memcpy(str + left, str + right, len - right + 1);
        zumaMemcpy(zumaStr + left, zumaStr + right, zumaLen - right + 1);
        zumaLen  = zumaLen - right + left;
        //printStr();
    }
    else
    {
        //memcpy(str + pos + 1, str + pos, len - pos + 1);
        zumaMemcpy(zumaStr + pos + 1, zumaStr + pos, zumaLen - pos + 1);
        //printStr();
        zumaStr[pos] = ch;
        //printStr();
        zumaLen++;
    }
}
void Chapter1_Part1::practice_052()
{
    int opNum, pos, i;
    char ch;
    VIO::scanf("%s", zumaStr);
    zumaLen = strlen(zumaStr);
    if (zumaStr[0] >= '0' && zumaStr[1] <= '9')
    {
        opNum = zumaStr[0] - '0';
        for (i = 1; i < zumaLen; i++)
        {
            opNum *= 10;
            opNum += (zumaStr[i] - '0');
        }
        memset(zumaStr, 0x00, zumaLen);
        zumaLen = 0;
    }
    else
    {
        VIO::scanf("%d", &opNum);
    }
    for (i = 0; i < opNum; i++)
    {
        VIO::scanf("%d %c", &pos, &ch);
        shootBead(pos, ch);
        if (zumaLen > 0)
        {
            VIO::printf("%s\n", zumaStr);
            //printStr();
        }
        else
        {
            VIO::printf("-\n");
        }
    }
    //system("pause");
}
