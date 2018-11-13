#ifndef SORTING_H
#define SORTING_H


class Sorting
{
public:
    Sorting() = delete;

    template <typename T>
    static void selectSort(T arr[], int len);//选择排序
    template <typename T>
    static void bubbleSort(T arr[], int len);//冒泡排序
    template <typename T>
    static void insertSort(T arr[], int len);//插入排序
    template <typename T>
    static void shellSort(T arr[], int len);//希尔排序
    template <typename T>
    static void quickSort(T arr[], int low, int high);//快速排序
    template <typename T>
    static void mergeSort(T arr[], int low, int high);//归并排序

private:
    template <typename T>
    static void mergeSort(T src[], T des[], int start, int end);


};

template <typename T>
void Sorting::selectSort(T arr[], int len)//选择排序
{
    int i, j, min;
    T tmp;
    for (i = 0; i < len; i++)
    {
        min = i;
        for (j = i + 1; j < len; j++)
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
void Sorting::bubbleSort(T arr[], int len)//冒泡排序
{
    int i, j;
    bool exchange = true;
    T tmp;
    for (i = len - 1; i > 0 && exchange; i--)
    {
        exchange = false;
        for (j = 0; j < i; j++)
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

template <typename T>
void Sorting::insertSort(T arr[], int len)//插入排序
{
    for (int i = 0; i < len - 1; i++)
    {
        int k = i + 1;
        T tmp = arr[k];
        int j = i;
        for (; j >= 0 && arr[j] > tmp; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = tmp;
    }
}

template <typename T>
void Sorting::shellSort(T arr[], int len)//希尔排序
{
    for (int gap = len / 2; gap >= 1; gap /= 2)	//选取间隔
    {
        for (int i = 0; i < gap; i++)			//分成gap个组
        {
            for (int j = i; j < len - gap; j += gap)//对组插入排序
            {
                int k = j + gap;
                T tmp = arr[k];
                int a = j;
                for (; a >= 0 && arr[a] > tmp; a -= gap)
                    arr[a + gap] = arr[a];
                arr[a + gap] = tmp;
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
void merge(T arr[], int low, int mid, int high)
{

}

template <typename T>
void Sorting::mergeSort(T arr[], int low, int high)//归并排序
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

#endif // SORTING_H
