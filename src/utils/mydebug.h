#ifndef MYDEBUG_H
#define MYDEBUG_H

#include <QString>
#include <qglobal.h>
#include "src/03_String/mystring.h"

//#define DEBUG qDebug() << QString("%1 %2:%3 ").arg(QString(__FILE__).split('\\').last()).arg(__FUNCTION__).arg(__LINE__)
#define DEBUG MyDebug::info() << QString("%1 %2:%3 ").arg(QString(__FILE__).split('\\').last()).arg(__FUNCTION__).arg(__LINE__)

class String;

class MyDebug
{
private:
    explicit MyDebug();

public:
    ~MyDebug();

    static MyDebug info();
    static void setDebugFlag(bool save);
    static void clear();
    static QString infoPop();

    inline MyDebug &operator<<(QChar t) { m_line.append(QString(t)); return *this; }
    inline MyDebug &operator<<(bool t) { m_line.append(t ? "true" : "false"); return *this; }
    inline MyDebug &operator<<(char t) { m_line.append(QString(t)); return *this; }
    inline MyDebug &operator<<(short t) { m_line.append(QString::number(t)); return *this; }
    inline MyDebug &operator<<(unsigned short t) { m_line.append(QString::number(t)); return *this; }
    inline MyDebug &operator<<(int t) { m_line.append(QString::number(t)); return *this; }
    inline MyDebug &operator<<(unsigned int t) { m_line.append(QString::number(t)); return *this; }
    inline MyDebug &operator<<(long t) { m_line.append(QString::number(t)); return *this; }
    inline MyDebug &operator<<(unsigned long t) { m_line.append(QString::number(t)); return *this; }
    inline MyDebug &operator<<(qint64 t) { m_line.append(QString::number(t)); return *this; }
    inline MyDebug &operator<<(quint64 t) { m_line.append(QString::number(t)); return *this; }
    inline MyDebug &operator<<(float t) { m_line.append(QString::number(t)); return *this; }
    inline MyDebug &operator<<(double t) { m_line.append(QString::number(t)); return *this; }
    inline MyDebug &operator<<(const char *t) { m_line.append(QString::fromUtf8(t)); return *this; }
    inline MyDebug &operator<<(const QString &t) { m_line.append(t); return *this; }
    inline MyDebug &operator<<(const QStringRef &t) { m_line.append(t); return *this; }
    inline MyDebug &operator<<(QLatin1String t) { m_line.append(t); return *this; }
    inline MyDebug &operator<<(const QByteArray & t) { m_line.append(QString(t)); return *this; }
    inline MyDebug &operator<<(const String &t) { m_line.append(t.data()); return *this; }

private:
    static bool m_saveDebug;
    static QString m_line;
    static QString m_info;

};

#endif // MYDEBUG_H
