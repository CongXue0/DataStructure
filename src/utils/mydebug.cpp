#include "mydebug.h"
#include <QMutex>
#include <QDebug>

QString MyDebug::m_line;
QString MyDebug::m_info;

MyDebug::MyDebug()
{
    m_line.clear();
}

MyDebug::~MyDebug()
{
    qDebug() << m_line;
    m_info.append(m_line + "\n");
}

MyDebug MyDebug::info()
{
    return MyDebug();
}

void MyDebug::clear()
{
    m_info.clear();
}

QString MyDebug::infoPop()
{
    QString tmp = m_info;
    m_info.clear();
    return tmp;
}
