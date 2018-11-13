#ifndef SEARCH_H
#define SEARCH_H


class Search
{
public:
    Search() = delete;

    template <typename T>
    static int binarySearch(T arr[], int low, int high,  const T &key);//二分查找




};

template <typename T>
int Search::binarySearch(T arr[], int low, int high,  const T &key)//二分查找
{
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (key > arr[mid])
        {
            low = mid + 1;
        }
        else if (key < arr[mid])
        {
            high = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

#endif // SEARCH_H
