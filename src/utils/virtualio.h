#ifndef VIRTUALIO_H
#define VIRTUALIO_H
#include <QStringList>

class VirtualIO;
typedef VirtualIO VIO;

#define QT_TEST 1
#if QT_TEST == 1
    #define SCANF VIO::scanf
    #define PRINTF VIO::printf
    #define PUTCHAR VIO::putchar
#else
    #define SCANF scanf
    #define PRINTF printf
    #define PUTCHAR putchar
#endif

class VirtualIO
{
public:
    VirtualIO() = delete;
    static void setInput(QString input);
    static void clearInput();
    static void flush();//输出缓冲器留存数据
    static int scanf(const char *format, ...);
    static void printf(const char *format, ...);
    static void putchar(int ch);

private:
    static QStringList m_inputList;//输入列表
    static QString m_info;//行缓冲

};

#endif // VIRTUALIO_H
