#ifndef TOOL_H
#define TOOL_H

#include <QDebug>
#include <QString>
#include "src/01_LinearList/seqlist.h"
#include "src/01_LinearList/linklist.h"
#include "src/01_LinearList/doublelinklist.h"
#include "src/utils/mydebug.h"

#define BOOLSTR(a) ((a == true) ? "true" : "false")
#define TIMEFORMAT ("yyyy-MM-dd hh:mm:ss")
//#define DEBUG qDebug() << QString("%1 %2:%3 ").arg(QString(__FILE__).split('\\').last()).arg(__FUNCTION__).arg(__LINE__)
#define DEBUG MyDebug::info() << QString("%1 %2:%3 ").arg(QString(__FILE__).split('\\').last()).arg(__FUNCTION__).arg(__LINE__)

#define MAX_CHAPTER_NUM 12

/* 类型判断器 */
template<typename T1, typename T2>
struct is_same
{
    operator bool()
    {
        return false;
    }
};
template<typename T1>
struct is_same<T1, T1>
{
    operator bool()
    {
        return true;
    }
};

template <typename T>
struct is_char
{
    operator bool()
    {
        return false;
    }
};
template <>
struct is_char<char>
{
    operator bool()
    {
        return true;
    }
};

class Tool
{
public:
    Tool() = delete;

    /* 文件操作 */
    static QString readFileInfo(const QString &path);
    static void appendFileInfo(const QString &path, const QString &info);
    static void writeFileInfo(const QString &path, const QString &info);
    static bool makePath(const QString &path);
    static bool makeDir(const QString &path);

    /* 其他 */
    static int rand(const int &a, const int &b);//得到一个 [a, b] 范围内的随机数
    static void createRandArr(int arr[], int len, int left, int right);//生成随机数组
    template<typename T>
    static QString printArr(T arr[], int low, int high);

};

template<typename T>
QString Tool::printArr(T arr[], int low, int high)
{
    QString result;
    for (int i = low; i <= high; i++)
    {
        result.append(QString::number(arr[i]) + " ");
    }
    return result;
}

#endif // TOOL_H
