#include "chapter9_part1.h"
#include "src/09_Sorting/sorting.h"
#include "src/utils/tool.h"
#include <QDateTime>
#include "src/utils/virtualio.h"

/*
排序demo
*/
void Chapter9_Part1::practice_000()
{
    const int len = 10000;
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

    delete[] arr;

    //    DEBUG<<Tool::printArr<int>(arr, 0, 9);
}

/*
直接插入排序demo
*/
void Chapter9_Part1::practice_001()
{
    const int len = 10000;
    int *arr = new int[len];
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Tool::createRandArr(arr, len, -10 * len, 10 * len);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Sorting::insertSort<int>(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    delete[] arr;
}

/*
希尔排序demo
*/
void Chapter9_Part1::practice_002()
{
    const int len = 10000000;
    int *arr = new int[len];
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Tool::createRandArr(arr, len, -10 * len, 10 * len);
    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Sorting::shellSort<int>(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    DEBUG<<Tool::printArr(arr, 0, len - 1);
    delete[] arr;
}

/*
堆排序demo
*/
void Chapter9_Part1::practice_003()
{
    const int len = 10000000;
    int *arr = new int[len];
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Tool::createRandArr(arr, len, -10 * len, 10 * len);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Sorting::heapSort<int>(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<Tool::checkArr(arr, 0, len - 1);
    delete[] arr;
}

/*
快速排序demo
*/
void Chapter9_Part1::practice_004()
{
    const int len = 10000000;
    int *arr = new int[len];
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Tool::createRandArr(arr, len, -10 * len, 10 * len);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Sorting::quickSort<int>(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<Tool::checkArr(arr, 0, len - 1);
    delete[] arr;
}

/*
计数排序demo
*/
void Chapter9_Part1::practice_005()
{
    const int len = 10000000;
    int *arr = new int[len];
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Tool::createRandArr(arr, len, 0, len / 100);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Sorting::countSort<int>(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<Tool::checkArr(arr, 0, len - 1);
    delete[] arr;
}

/*
桶排序demo
*/
void Chapter9_Part1::practice_006()
{
    const int len = 10000000;
    int *arr = new int[len];
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Tool::createRandArr(arr, len, 0, len / 100);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Sorting::bucketSort<int>(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<Tool::checkArr(arr, 0, len - 1);
    delete[] arr;
}

/*
基数排序demo
*/
void Chapter9_Part1::practice_007()
{
    const int len = 10000000;
    int *arr = new int[len];
//    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Tool::createRandArr(arr, len, 0, len * 10);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Sorting::radixSort<int>(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<Tool::checkArr(arr, 0, len - 1);

    Tool::createRandArr(arr, len, 0, len * 10);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
    Sorting::radixSort2<int>(arr, 0, len - 1);
    DEBUG<<QDateTime::currentDateTime().toString(TIMEFORMAT);
//    DEBUG<<Tool::printArr(arr, 0, len - 1);
    DEBUG<<Tool::checkArr(arr, 0, len - 1);

    delete[] arr;
}

/*
O(n2)排序算法统计
Debug统计：
"chapter9_part1.cpp practice_050:171 排序元素个数：30000, 统计次数：10"
"chapter9_part1.cpp practice_050:238 重复元素较少的平均用时统计："
"chapter9_part1.cpp practice_050:239 简单选择排序用时：1038 ms"
"chapter9_part1.cpp practice_050:240 冒泡排序用时：2267 ms"
"chapter9_part1.cpp practice_050:241 直接插入排序用时：530 ms"
"chapter9_part1.cpp practice_050:242 重复元素较多的平均用时统计："
"chapter9_part1.cpp practice_050:243 简单选择排序用时：1033 ms"
"chapter9_part1.cpp practice_050:244 冒泡排序用时：2269 ms"
"chapter9_part1.cpp practice_050:245 直接插入排序用时：528 ms"

Release统计：
"chapter9_part1.cpp practice_050:184 排序元素个数：30000, 统计次数：10"
"chapter9_part1.cpp practice_050:251 重复元素较少的平均用时统计："
"chapter9_part1.cpp practice_050:252 简单选择排序用时：928 ms"
"chapter9_part1.cpp practice_050:253 冒泡排序用时：1298 ms"
"chapter9_part1.cpp practice_050:254 直接插入排序用时：140 ms"
"chapter9_part1.cpp practice_050:255 重复元素较多的平均用时统计："
"chapter9_part1.cpp practice_050:256 简单选择排序用时：936 ms"
"chapter9_part1.cpp practice_050:257 冒泡排序用时：1285 ms"
"chapter9_part1.cpp practice_050:258 直接插入排序用时：133 ms"
*/
void Chapter9_Part1::practice_050()
{
    const int len = 30000;//排序元素个数
    const int times = 10;//统计次数
    int *arr, *copyArr;
    quint64 countArr[3][2][100] = {0}, resultArr[3][2] = {0};
    QDateTime start;
    quint64 uTime;
    arr = new int[len];
    copyArr = new int[len];

    DEBUG<<"排序元素个数："<<len<<", 统计次数："<<times;
    for (int i = 0; i < times; i++)
    {
        DEBUG<<"重复元素较少的统计结果：";
        Tool::createRandArr(arr, len, -len * 10, len * 10);

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::selectSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("简单选择排序用时：%1 ms").arg(uTime);
        countArr[0][0][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::bubbleSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("冒泡排序用时：%1 ms").arg(uTime);
        countArr[1][0][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::insertSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("直接插入排序用时：%1 ms").arg(uTime);
        countArr[2][0][i] = uTime;

        DEBUG<<"重复元素较多的统计结果：";
        Tool::createRandArr(arr, len, 0, len / 100);

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::selectSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("简单选择排序用时：%1 ms").arg(uTime);
        countArr[0][1][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::bubbleSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("冒泡排序用时：%1 ms").arg(uTime);
        countArr[1][1][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::insertSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("直接插入排序用时：%1 ms").arg(uTime);
        countArr[2][1][i] = uTime;
    }

    for (int i = 0; i < times; i++)
    {
        resultArr[0][0] += countArr[0][0][i];
        resultArr[1][0] += countArr[1][0][i];
        resultArr[2][0] += countArr[2][0][i];
        resultArr[0][1] += countArr[0][1][i];
        resultArr[1][1] += countArr[1][1][i];
        resultArr[2][1] += countArr[2][1][i];
    }
    resultArr[0][0] /= times;
    resultArr[1][0] /= times;
    resultArr[2][0] /= times;
    resultArr[0][1] /= times;
    resultArr[1][1] /= times;
    resultArr[2][1] /= times;
    DEBUG<<"重复元素较少的平均用时统计：";
    DEBUG<<QString("简单选择排序用时：%1 ms").arg(resultArr[0][0]);
    DEBUG<<QString("冒泡排序用时：%1 ms").arg(resultArr[1][0]);
    DEBUG<<QString("直接插入排序用时：%1 ms").arg(resultArr[2][0]);
    DEBUG<<"重复元素较多的平均用时统计：";
    DEBUG<<QString("简单选择排序用时：%1 ms").arg(resultArr[0][1]);
    DEBUG<<QString("冒泡排序用时：%1 ms").arg(resultArr[1][1]);
    DEBUG<<QString("直接插入排序用时：%1 ms").arg(resultArr[2][1]);

    delete[] arr;
    delete[] copyArr;
}

/*
O(nlogn)排序算法统计
Debug统计：
"chapter9_part1.cpp practice_051:274 排序元素个数：10000000, 统计次数：10"
"chapter9_part1.cpp practice_051:359 重复元素较少的平均用时统计："
"chapter9_part1.cpp practice_051:360 希尔排序用时：5189 ms"
"chapter9_part1.cpp practice_051:361 快速排序用时：4013 ms"
"chapter9_part1.cpp practice_051:362 归并排序用时：2823 ms"
"chapter9_part1.cpp practice_051:363 堆排序用时：2975 ms"
"chapter9_part1.cpp practice_051:364 重复元素较多的平均用时统计："
"chapter9_part1.cpp practice_051:365 希尔排序用时：4873 ms"
"chapter9_part1.cpp practice_051:366 快速排序用时：10636 ms"
"chapter9_part1.cpp practice_051:367 归并排序用时：2707 ms"
"chapter9_part1.cpp practice_051:368 堆排序用时：2768 ms"

Release版本：
"chapter9_part1.cpp practice_051:290 排序元素个数：10000000, 统计次数：10"
"chapter9_part1.cpp practice_051:375 重复元素较少的平均用时统计："
"chapter9_part1.cpp practice_051:376 希尔排序用时：2862 ms"
"chapter9_part1.cpp practice_051:377 快速排序用时：1377 ms"
"chapter9_part1.cpp practice_051:378 归并排序用时：1772 ms"
"chapter9_part1.cpp practice_051:379 堆排序用时：2103 ms"
"chapter9_part1.cpp practice_051:380 重复元素较多的平均用时统计："
"chapter9_part1.cpp practice_051:381 希尔排序用时：2727 ms"
"chapter9_part1.cpp practice_051:382 快速排序用时：2817 ms"
"chapter9_part1.cpp practice_051:383 归并排序用时：1715 ms"
"chapter9_part1.cpp practice_051:384 堆排序用时：1920 ms"

"chapter9_part1.cpp practice_051:312 排序元素个数：50000000, 统计次数：1"
"chapter9_part1.cpp practice_051:397 重复元素较少的平均用时统计："
"chapter9_part1.cpp practice_051:398 希尔排序用时：20831 ms"
"chapter9_part1.cpp practice_051:399 快速排序用时：19617 ms"
"chapter9_part1.cpp practice_051:400 归并排序用时：9566 ms"
"chapter9_part1.cpp practice_051:401 堆排序用时：12620 ms"
"chapter9_part1.cpp practice_051:402 重复元素较多的平均用时统计："
"chapter9_part1.cpp practice_051:403 希尔排序用时：20577 ms"
"chapter9_part1.cpp practice_051:404 快速排序用时：19357 ms"
"chapter9_part1.cpp practice_051:405 归并排序用时：9359 ms"
"chapter9_part1.cpp practice_051:406 堆排序用时：12514 ms"
*/
void Chapter9_Part1::practice_051()
{
    const int len = 50000000;//排序元素个数
    const int times = 1;//统计次数
    int *arr, *copyArr;
    quint64 countArr[4][2][100] = {0}, resultArr[4][2] = {0};
    QDateTime start;
    quint64 uTime;
    arr = new int[len];
    copyArr = new int[len];

    DEBUG<<"排序元素个数："<<len<<", 统计次数："<<times;
    for (int i = 0; i < times; i++)
    {
        DEBUG<<"重复元素较少的统计结果：";
        Tool::createRandArr(arr, len, -len * 10, len * 10);

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::shellSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("希尔排序用时：%1 ms").arg(uTime);
        countArr[0][0][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::quickSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("快速排序用时：%1 ms").arg(uTime);
        countArr[1][0][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::mergeSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("归并排序用时：%1 ms").arg(uTime);
        countArr[2][0][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::heapSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("堆排序用时：%1 ms").arg(uTime);
        countArr[3][0][i] = uTime;

        DEBUG<<"重复元素较多的统计结果：";
        Tool::createRandArr(arr, len, 0, len / 1000);

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::shellSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("希尔排序用时：%1 ms").arg(uTime);
        countArr[0][1][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::quickSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("快速排序用时：%1 ms").arg(uTime);
        countArr[1][1][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::mergeSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("归并排序用时：%1 ms").arg(uTime);
        countArr[2][1][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::heapSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("堆排序用时：%1 ms").arg(uTime);
        countArr[3][1][i] = uTime;
    }

    for (int i = 0; i < times; i++)
    {
        resultArr[0][0] += countArr[0][0][i];
        resultArr[1][0] += countArr[1][0][i];
        resultArr[2][0] += countArr[2][0][i];
        resultArr[3][0] += countArr[3][0][i];
        resultArr[0][1] += countArr[0][1][i];
        resultArr[1][1] += countArr[1][1][i];
        resultArr[2][1] += countArr[2][1][i];
        resultArr[3][1] += countArr[3][1][i];
    }
    resultArr[0][0] /= times;
    resultArr[1][0] /= times;
    resultArr[2][0] /= times;
    resultArr[3][0] /= times;
    resultArr[0][1] /= times;
    resultArr[1][1] /= times;
    resultArr[2][1] /= times;
    resultArr[3][1] /= times;
    DEBUG<<"重复元素较少的平均用时统计：";
    DEBUG<<QString("希尔排序用时：%1 ms").arg(resultArr[0][0]);
    DEBUG<<QString("快速排序用时：%1 ms").arg(resultArr[1][0]);
    DEBUG<<QString("归并排序用时：%1 ms").arg(resultArr[2][0]);
    DEBUG<<QString("堆排序用时：%1 ms").arg(resultArr[3][0]);
    DEBUG<<"重复元素较多的平均用时统计：";
    DEBUG<<QString("希尔排序用时：%1 ms").arg(resultArr[0][1]);
    DEBUG<<QString("快速排序用时：%1 ms").arg(resultArr[1][1]);
    DEBUG<<QString("归并排序用时：%1 ms").arg(resultArr[2][1]);
    DEBUG<<QString("堆排序用时：%1 ms").arg(resultArr[3][1]);

    delete[] arr;
    delete[] copyArr;
}

/*
非比较排序算法统计
Debug统计：
"chapter9_part1.cpp practice_052:442 排序元素个数：50000000, 统计次数：10"
"chapter9_part1.cpp practice_052:509 重复元素较少的平均用时统计："
"chapter9_part1.cpp practice_052:510 计数排序用时：870 ms"
"chapter9_part1.cpp practice_052:511 桶排序用时：326 ms"
"chapter9_part1.cpp practice_052:512 基数排序用时：3537 ms"
"chapter9_part1.cpp practice_052:513 重复元素较多的平均用时统计："
"chapter9_part1.cpp practice_052:514 计数排序用时：873 ms"
"chapter9_part1.cpp practice_052:515 桶排序用时：327 ms"
"chapter9_part1.cpp practice_052:516 基数排序用时：3534 ms"

Release版本：
"chapter9_part1.cpp practice_052:450 排序元素个数：50000000, 统计次数：10"
"chapter9_part1.cpp practice_052:517 重复元素较少的平均用时统计："
"chapter9_part1.cpp practice_052:518 计数排序用时：776 ms"
"chapter9_part1.cpp practice_052:519 桶排序用时：93 ms"
"chapter9_part1.cpp practice_052:520 基数排序用时：2134 ms"
"chapter9_part1.cpp practice_052:521 重复元素较多的平均用时统计："
"chapter9_part1.cpp practice_052:522 计数排序用时：766 ms"
"chapter9_part1.cpp practice_052:523 桶排序用时：92 ms"
"chapter9_part1.cpp practice_052:524 基数排序用时：2130 ms"

"chapter9_part1.cpp practice_052:459 排序元素个数：50000000, 统计次数：10"
"chapter9_part1.cpp practice_052:544 重复元素较少的平均用时统计："
"chapter9_part1.cpp practice_052:545 计数排序用时：762 ms"
"chapter9_part1.cpp practice_052:546 桶排序用时：93 ms"
"chapter9_part1.cpp practice_052:547 基数排序用时：2184 ms"
"chapter9_part1.cpp practice_052:548 基数2排序用时：837 ms"
"chapter9_part1.cpp practice_052:549 重复元素较多的平均用时统计："
"chapter9_part1.cpp practice_052:550 计数排序用时：768 ms"
"chapter9_part1.cpp practice_052:551 桶排序用时：93 ms"
"chapter9_part1.cpp practice_052:552 基数排序用时：2170 ms"
"chapter9_part1.cpp practice_052:553 基数2排序用时：840 ms"
*/
void Chapter9_Part1::practice_052()
{
    const int len = 50000000;//排序元素个数
    const int times = 10;//统计次数
    int *arr, *copyArr;
    quint64 countArr[4][2][100] = {0}, resultArr[4][2] = {0};
    QDateTime start;
    quint64 uTime;
    arr = new int[len];
    copyArr = new int[len];

    DEBUG<<"排序元素个数："<<len<<", 统计次数："<<times;
    for (int i = 0; i < times; i++)
    {
        DEBUG<<"重复元素较少的统计结果：";
        Tool::createRandArr(arr, len, 0, len * 10);

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::countSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("计数排序用时：%1 ms").arg(uTime);
        countArr[0][0][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::bucketSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("桶排序用时：%1 ms").arg(uTime);
        countArr[1][0][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::radixSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("基数排序用时：%1 ms").arg(uTime);
        countArr[2][0][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::radixSort2<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("基数排序2用时：%1 ms").arg(uTime);
        countArr[3][0][i] = uTime;

        DEBUG<<"重复元素较多的统计结果：";
        Tool::createRandArr(arr, len, 0, len / 1000);

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::countSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("计数排序用时：%1 ms").arg(uTime);
        countArr[0][1][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::bucketSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("桶排序用时：%1 ms").arg(uTime);
        countArr[1][1][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::radixSort<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("基数排序用时：%1 ms").arg(uTime);
        countArr[2][1][i] = uTime;

        memcpy(copyArr, arr, sizeof(int) * len);
        start = QDateTime::currentDateTime();
        Sorting::radixSort2<int>(copyArr, 0, len - 1);
        uTime = start.msecsTo(QDateTime::currentDateTime());
        DEBUG<<QString("基数排序2用时：%1 ms").arg(uTime);
        countArr[3][1][i] = uTime;
    }

    for (int i = 0; i < times; i++)
    {
        resultArr[0][0] += countArr[0][0][i];
        resultArr[1][0] += countArr[1][0][i];
        resultArr[2][0] += countArr[2][0][i];
        resultArr[3][0] += countArr[3][0][i];
        resultArr[0][1] += countArr[0][1][i];
        resultArr[1][1] += countArr[1][1][i];
        resultArr[2][1] += countArr[2][1][i];
        resultArr[3][1] += countArr[3][1][i];
    }
    resultArr[0][0] /= times;
    resultArr[1][0] /= times;
    resultArr[2][0] /= times;
    resultArr[3][0] /= times;
    resultArr[0][1] /= times;
    resultArr[1][1] /= times;
    resultArr[2][1] /= times;
    resultArr[3][1] /= times;
    DEBUG<<"重复元素较少的平均用时统计：";
    DEBUG<<QString("计数排序用时：%1 ms").arg(resultArr[0][0]);
    DEBUG<<QString("桶排序用时：%1 ms").arg(resultArr[1][0]);
    DEBUG<<QString("基数排序用时：%1 ms").arg(resultArr[2][0]);
    DEBUG<<QString("基数2排序用时：%1 ms").arg(resultArr[3][0]);
    DEBUG<<"重复元素较多的平均用时统计：";
    DEBUG<<QString("计数排序用时：%1 ms").arg(resultArr[0][1]);
    DEBUG<<QString("桶排序用时：%1 ms").arg(resultArr[1][1]);
    DEBUG<<QString("基数排序用时：%1 ms").arg(resultArr[2][1]);
    DEBUG<<QString("基数2排序用时：%1 ms").arg(resultArr[3][1]);

    delete[] arr;
    delete[] copyArr;
}

/*
范围查询(Range)：
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
/*
归并 + 二分查找 方式
*/
//#if OJ_TEST == 1
//int p100_arr[10000000];
//#else
//int p100_arr[100];
//#endif
//void p100_merge(int arr[], int low, int mid, int high)
//{
//    if (low <= mid && mid < high)
//    {
//        int len = high - low + 1;
//        int *tmp = new int[len];
//        int i = low, j = mid + 1, k = 0;

//        while (i <= mid && j <= high)
//        {
//            if (arr[i] <= arr[j])
//            {
//                tmp[k] = arr[i];
//                k++;
//                i++;
//            }
//            else
//            {
//                tmp[k] = arr[j];
//                k++;
//                j++;
//            }
//        }
//        for (; i <= mid; i++, k++)//剩余表元素插入 tmp
//        {
//            tmp[k] = arr[i];
//        }
//        for (; j <= high; j++, k++)//剩余表元素插入 tmp
//        {
//            tmp[k] = arr[j];
//        }

//        for (i = 0; i < len; i++)
//        {
//            arr[low + i] = tmp[i];
//        }
//        delete[] tmp;
//    }
//}
//void p100_mergeSort(int arr[], int low, int high)//归并排序
//{
//    if (low < high)
//    {
//        int mid = (low + high) / 2;
//        p100_mergeSort(arr, low, mid);
//        p100_mergeSort(arr, mid + 1, high);
//        p100_merge(arr, low, mid, high);//合并两个序列
//    }
//}
//int p100_searchLeft(int arr[], int low, int high,  const int &key)//二分之左
//{
//    if (key <= arr[low])
//    {
//        return low;
//    }
//    else if (key == arr[high])
//    {
//        return high;
//    }
//    else if (key > arr[high])
//    {
//        return high + 1;
//    }
//    int mid;
//    while (low < high)
//    {
//        mid = (low + high) / 2;
//        if (key > arr[mid])
//        {
//            low = mid + 1;
//        }
//        else if (key < arr[mid])
//        {
//            high = mid;
//        }
//        else
//        {
//            return mid;
//        }
//    }
//    return low;
//}
//int p100_searchRight(int arr[], int low, int high,  const int &key)//二分之右
//{
//    if (key < arr[low])
//    {
//        return low;
//    }
//    else if (key == arr[low])
//    {
//        return low + 1;
//    }
//    else if (key >= arr[high])
//    {
//        return high + 1;
//    }
//    int mid;
//    while (low < high)
//    {
//        mid = (low + high) / 2;
//        if (key > arr[mid])
//        {
//            low = mid + 1;
//        }
//        else if (key < arr[mid])
//        {
//            high = mid;
//        }
//        else
//        {
//            return mid + 1;
//        }
//    }
//    return high;
//}
//void Chapter9_Part1::practice_100()
//{
//    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
//    int i, size, n, left, right;
//    SCANF("%d %d", &size, &n);

//    for (i = 0; i < size; i++)
//        SCANF("%d", p100_arr + i);

//    p100_mergeSort(p100_arr, 0, size - 1);
//    for (i = 0; i < n; i++)
//    {
//        SCANF("%d %d", &left, &right);
//        PRINTF("%d\n", p100_searchRight(p100_arr, 0, size - 1, right) - p100_searchLeft(p100_arr, 0, size - 1, left));
//    }
//}

/*
计数排序 方式
*/
#if OJ_TEST == 1
    #define p100_ARRSIZE 10000000
#else
    #define p100_ARRSIZE 100
#endif
int p100_arr[p100_ARRSIZE];
void Chapter9_Part1::practice_100()
{
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    int i, j, size, n, left, right;
    SCANF("%d %d", &size, &n);

    //统计每个元素出现的次数，再统计元素值到0之间的元素个数
    for (i = 0; i < size; i++)
    {
        SCANF("%d", &j);
        p100_arr[j]++;
    }
    for (i = 1; i <= p100_ARRSIZE; i++)
        p100_arr[i] += p100_arr[i - 1];

    for (i = 0; i < n; i++)
    {
        SCANF("%d %d", &left, &right);
        PRINTF("%d\n", p100_arr[right] - p100_arr[left - 1]);
    }
}
