#ifndef VIRTUALIO_H
#define VIRTUALIO_H
#include <QStringList>

class VirtualIO;
typedef VirtualIO VIO;

class VirtualIO
{
public:
    VirtualIO() = delete;
    static void setInput(QString input);
    static void clearInput();
    static int scanf(const char *format, ...);
    static void printf(const char *format, ...);
    static void putchar(int ch);

private:
    static QStringList m_inputList;
    static QString m_info;

};

#endif // VIRTUALIO_H
