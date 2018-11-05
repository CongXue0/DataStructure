#ifndef TOOL_H
#define TOOL_H

#include <QDebug>

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



};

#endif // TOOL_H
