#include "virtualio.h"
#include "src/utils/tool.h"

QStringList VirtualIO::m_inputList;
QString VirtualIO::m_info;

void VirtualIO::setInput(QString input)
{
    QStringList list = input.split('\n');
    for (int i = 0; i < list.count(); i++)
    {
        if (!list.at(i).isEmpty())
        {
            m_inputList.append(list.at(i));
        }
    }
}

void VirtualIO::clearInput()
{
    m_inputList.clear();
    m_info.clear();
}

int VirtualIO::scanf(const char *format, ...)
{
    static char buf[2048];
    if (m_inputList.count() > 0)
    {
        memset(buf, 0x00, 2048);
        strcpy(buf, m_inputList.at(0).toUtf8().data());
        m_inputList.removeAt(0);

        va_list args;
        va_start(args, format);
        int ret = vsscanf(buf, format, args);
        va_end(args);
        return ret;
    }
    return 0;
}

int VirtualIO::printf(const char *format, ...)
{
    QString str;
    va_list args;
    va_start(args, format);
    str.vsprintf(format, args);
    va_end(args);
    if (str.length() > 0 && str.at(str.length() - 1) == QChar('\n'))
    {
        str = str.mid(0, str.length() - 1);
        m_info.append(str);
        if (!m_info.isEmpty())
        {
            MyDebug::info() << m_info;
            m_info.clear();
        }
    }
    else if (str.length() > 0)
    {
        m_info.append(str);
    }
}

int VirtualIO::putchar(int ch)
{
    if (ch == '\n')
    {
        if (!m_info.isEmpty())
        {
            MyDebug::info() << m_info;
            m_info.clear();
        }
    }
    else
    {
        m_info.append(QChar(ch));
    }
}
