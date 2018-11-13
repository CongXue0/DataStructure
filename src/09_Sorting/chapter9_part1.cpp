#include "chapter9_part1.h"
#include "src/09_Sorting/sorting.h"
#include "src/utils/tool.h"

void Chapter9_Part1::practice_000(QString input, QString &result)
{
    int arr[10];
    Tool::createRandArr(arr, 10, -100, 400);
    DEBUG<<Tool::printArr<int>(arr, 10);

    Sorting::bubbleSort<int>(arr, 10);

    DEBUG<<Tool::printArr<int>(arr, 10);
}
