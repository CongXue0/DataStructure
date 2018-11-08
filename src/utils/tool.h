#ifndef TOOL_H
#define TOOL_H

#include <QDebug>
#include <QString>
#include "src/01_LinearList/seqlist.h"
#include "src/01_LinearList/linklist.h"
#include "src/01_LinearList/doublelinklist.h"

#define BOOLSTR(a) ((a == true) ? "true" : "false")
#define TIMEFORMAT ("yyyy-MM-dd hh:mm:ss")
#define DEBUG qDebug() << QString("%1 %2:%3 ").arg(QString(__FILE__).split('\\').last()).arg(__FUNCTION__).arg(__LINE__)

#define MAX_CHAPTER_NUM 10

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

    /* 数据结构相关 */
    template<typename T>
    static QString printSeqList(SeqList<T> &list);
    template<typename T>
    static QString printLinkList(LinkList<T> &list);
    template<typename T>
    static QString printDoubleLinkList(DoubleLinkList<T> &list);

};

template<typename T>
QString Tool::printSeqList(SeqList<T> &list)
{
    QString result;
    for (int i = 0; i < list.getLength(); i++)
    {
        result.append(QString::number(list.at(i)) + " ");
    }
    return result;
}

template<typename T>
QString Tool::printLinkList(LinkList<T> &list)
{
    QString result;
    for (int i = 0; i < list.getLength(); i++)
    {
        result.append(QString::number(list.at(i)) + " ");
    }
    return result;
}

template<typename T>
QString Tool::printDoubleLinkList(DoubleLinkList<T> &list)
{
    QString result;
    for (int i = 0; i < list.getLength(); i++)
    {
        result.append(QString::number(list.at(i)) + " ");
    }
    return result;
}

#endif // TOOL_H
