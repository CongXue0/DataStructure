#include "src/03_String/mystring.h"
#include <string.h>
#include <assert.h>
#include <QString>
#include <QDebug>
#include <stdlib.h>
#include "src/01_LinearList/linklist.h"

char String::m_digit[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

#define MYSTRING_CONS_OPEN 0

String::String() : m_str(nullptr), m_length(0), m_capacity(0), m_refCount(nullptr)
{
#if MYSTRING_CONS_OPEN == 1
    qDebug() << "String gouzao 1 null";
#endif
}

String::String(const char *str, int len)
{
#if MYSTRING_CONS_OPEN == 1
    qDebug() << "String gouzao 2 char * , str:"<<str<<", len:"<<len;
#endif
    if (str == nullptr || (m_length = strlen(str)) == 0)
    {
        m_str = nullptr;
        m_length = 0;
        m_capacity = 0;
        m_refCount = nullptr;
        return;
    }
    m_capacity = STRING_INIT_SIZE;
    if (m_length > m_capacity - 1)
        m_capacity = m_length + 1;
    m_str = new char[m_capacity];
    memset(m_str, 0x00, m_capacity);
    int _len = strlen(str);
    if (len < 0 || len > _len)
        len = _len;
    strncpy(m_str, str, len);
    m_length = len;
    m_str[m_length] = '\0';
    m_refCount = new int;
    *m_refCount = 1;
}

String::String(const String &str)
{
#if MYSTRING_CONS_OPEN == 1
    qDebug() << "String gouzao 3 copy";
#endif
    if (str.m_length == 0)
    {
        m_str = nullptr;
        m_length = 0;
        m_capacity = 0;
        m_refCount = nullptr;
        return;
    }
    m_str = str.m_str;
    m_length = str.m_length;
    m_capacity = str.m_capacity;
    m_refCount = str.m_refCount;
    (*m_refCount)++;
}

String::String(String &&str)
{
#if MYSTRING_CONS_OPEN == 1
    qDebug() << "String gouzao 4 move";
#endif
    if (str.m_capacity == 0)
    {
        m_str = nullptr;
        m_length = 0;
        m_capacity = 0;
        m_refCount = nullptr;
        return;
    }
    m_str = str.m_str;
    m_length = str.m_length;
    m_capacity = str.m_capacity;
    m_refCount = str.m_refCount;
    str.m_str = nullptr;
    str.m_length = 0;
    str.m_capacity = 0;
    str.m_refCount = nullptr;
}

String::~String()
{
#if MYSTRING_CONS_OPEN == 1
    qDebug() << "String ~";
#endif
    if (m_refCount != nullptr)
    {
        if (*m_refCount > 0)
        {
            (*m_refCount)--;
        }
#if MYSTRING_CONS_OPEN == 1
        qDebug() << "ref count:"<<(*m_refCount);
#endif
        if (*m_refCount == 0)
        {
            delete[] m_str;
            delete m_refCount;
        }
    }
}

String &String::operator=(const String &str)
{
#if MYSTRING_CONS_OPEN == 1
    qDebug() << "String operator= 1";
#endif
    if (m_capacity == 0)
    {
        if (str.m_length > 0)
        {
            m_str = str.m_str;
            m_length = str.m_length;
            m_capacity = str.m_capacity;
            m_refCount = str.m_refCount;
            (*m_refCount)++;
        }
    }
    else if (str.m_length == 0)
    {
        clear();
    }
    else
    {
        if (*m_refCount > 1)
        {
            (*m_refCount)--;
        }
        else
        {
            delete[] m_str;
            delete m_refCount;
        }
        m_str = str.m_str;
        m_length = str.m_length;
        m_capacity = str.m_capacity;
        m_refCount = str.m_refCount;
        (*m_refCount)++;
    }
    return *this;
}

String &String::operator=(String &&str)
{
#if MYSTRING_CONS_OPEN == 1
    qDebug() << "String operator= 2 move";
#endif
    if (m_capacity == 0)
    {
        if (str.m_capacity > 0)
        {
            m_str = str.m_str;
            m_length = str.m_length;
            m_capacity = str.m_capacity;
            m_refCount = str.m_refCount;
            str.m_str = nullptr;
            str.m_length = 0;
            str.m_capacity = 0;
            str.m_refCount = nullptr;
        }
    }
    else if (str.m_capacity == 0)
    {
        clear();
    }
    else
    {
        (*m_refCount)--;
        if (*m_refCount == 0)
        {
            delete[] m_str;
            delete m_refCount;
        }
        m_str = str.m_str;
        m_length = str.m_length;
        m_capacity = str.m_capacity;
        m_refCount = str.m_refCount;
        str.m_str = nullptr;
        str.m_length = 0;
        str.m_capacity = 0;
        str.m_refCount = nullptr;
    }
    return *this;
}

int String::size() const
{
    return m_length;
}

int String::length() const
{
    return m_length;
}

int String::capacity() const
{
    return m_capacity;
}

int String::getRefCount() const
{
//    if (m_refCount == nullptr)
//    {
//        qDebug()<<"null ref";
//    }
//    else
//    {
//        qDebug()<<"ref:"<<(*m_refCount);
//    }
    return (m_refCount == nullptr ? 1 : *m_refCount);
}

bool String::isEmpty() const
{
    return m_length == 0;
}

const char *String::data() const
{
    return (m_str == nullptr ? "" : m_str);
}

void String::clear()
{
    if (m_refCount != nullptr)
    {
        if (*m_refCount > 1)
        {
            (*m_refCount)--;
            m_str = nullptr;
            m_length = 0;
            m_capacity = 0;
            m_refCount = nullptr;
        }
        else
        {
            m_length = 0;
            m_str[m_length] = '\0';
        }
    }
}

void String::resize(int size)
{
    if (size > m_capacity)
    {
        if (m_capacity == 0)
        {
            m_capacity = size;
            m_str = new char[m_capacity];
            m_refCount = new int;
            *m_refCount = 1;
        }
        else
        {
            if (*m_refCount > 1)
            {
                (*m_refCount)--;
                char *tmp = new char[size];
                memcpy(tmp, m_str, m_capacity);
                m_str = tmp;
                m_capacity = size;
                m_refCount = new int;
                *m_refCount = 1;
            }
            else
            {
                char *tmp = new char[size];
                memcpy(tmp, m_str, m_capacity);
                delete[] m_str;
                m_str = tmp;
                m_capacity = size;
            }
        }
    }
}

void String::swap(String &other)
{
    std::swap(m_str, other.m_str);
    std::swap(m_length, other.m_length);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_refCount, other.m_refCount);
}

String &String::fill(char c, int size)
{
    if (c == '\0')
        return *this;
    if (size == -1)
    {
        if (m_capacity > 0 && m_length > 0)
        {
            if (*m_refCount > 1)
            {
                (*m_refCount)--;
                m_str = new char[m_capacity];
                m_refCount = new int;
                *m_refCount = 1;
            }
            memset(m_str, c, m_length);
            m_str[m_length] = '\0';
        }
        return *this;
    }
    if (size > 0)
    {
        if (m_capacity < size + 1)
        {
            resize(size + 1);
        }
        if (m_length < size)
            m_length = size;
        memset(m_str, c, size);
        m_str[m_length] = '\0';
    }
    return *this;
}

char String::at(int i) const
{
    assert(i >= 0 && i < m_length);
    return m_str[i];
}

char String::operator[](int i) const
{
    assert(i >= 0 && i < m_length);
    return m_str[i];
}

bool String::charCmp_case_sensitive(const char &a, const char &b)
{
    return a == b;
}

bool String::charCmp_case_insensitive(const char &a, const char &b)
{
    if (a != b)
    {
        if (a + 32 == b)
        {
            return a >= 65 && a <= 90;
        }
        else if (a - 32 == b)
        {
            return a >= 97 && a <= 122;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

int String::match_char(const char *s, int low, int high, const char &c, bool isPositive, bool isCaseSensitive)
{
    if (low > high || low < 0 || high < 0)
        return -1;
    int i;
    bool (*cmpFunc)(const char &, const char &) = (isCaseSensitive ? charCmp_case_sensitive : charCmp_case_insensitive);
    if (isPositive)
    {
        i = low;
        while (i <= high)
        {
            if (cmpFunc(s[i], c))
            {
                return i;
            }
            i++;
        }
        return -1;
    }
    else
    {
        i = high;
        while (i >= low)
        {
            if (cmpFunc(s[i], c))
            {
                return i;
            }
            i--;
        }
        return -1;
    }
}

int String::match_normal(const char *s, int low, int high, const char *t, int tlen, bool isPositive, bool isCaseSensitive)
{
    if (tlen > high - low + 1 || tlen < 0 || low > high || low < 0 || high < 0)
        return -1;
    int i, j;
    bool (*cmpFunc)(const char &, const char &) = (isCaseSensitive ? charCmp_case_sensitive : charCmp_case_insensitive);
    if (isPositive)
    {
        i = low, j = 0;
        while (i <= high && j < tlen)
        {
            if (cmpFunc(s[i], t[j]))
            {
                i++;
                j++;
            }
            else
            {
                i = i - j + 1;
                j = 0;
            }
        }
        if (j == tlen)
            return i - tlen;
        else
            return -1;
    }
    else
    {
        i = high, j = tlen - 1;
        while (i >= low && j >= 0)
        {
            if (cmpFunc(s[i], t[j]))
            {
                i--;
                j--;
            }
            else
            {
                i = i + tlen - j - 2;
                j = tlen - 1;
            }
        }
        if (j == -1)
            return i + 1;
        else
            return -1;
    }
}

int String::match_KMP(const char *s, int low, int high, const char *t, int tlen, bool isPositive, bool isCaseSensitive)
{
    static int *next = nullptr;
    static int nextLen = 128;
    if (tlen > high - low + 1 || tlen < 0 || low > high || low < 0 || high < 0)
        return -1;
    if (nextLen < tlen)
    {
        while (nextLen < tlen)
            nextLen = 2 * nextLen;
        if (next != NULL)
            delete next;
        next = new int[nextLen];
    }
    else
    {
        if (next == nullptr)
        {
            next = new int[nextLen];
        }
    }

    int i, j;
    bool (*cmpFunc)(const char &, const char &) = (isCaseSensitive ? charCmp_case_sensitive : charCmp_case_insensitive);
    if (isPositive)
    {
        i = 0, j = -1;
        next[i] = -1;
        while (i < tlen - 1)//生成next数组
        {
            if (j == -1 || cmpFunc(t[i], t[j]))//递推数组
            {
                i++;
                j++;
                //较之前next数组求法，改动在下面4行
                if (!cmpFunc(t[i], t[j]))
                    next[i] = j; //之前只有这一行
                else
                //因为不能出现t[j] = t[ next[j ]]，所以当出现时需要继续递归，j = next[j] = next[next[j]]
                    next[i] = next[j];
            }
            else
                j = next[j];//减少相同前缀的长度，寻找更短的前缀是否能匹配的上，直到j等于-1，再次匹配
        }
//        DEBUG<<"next : "<<Tool::printArr(next, 0, tlen - 1);

        i = low, j = 0;
        while (i <= high && j < tlen)
        {
            if (j == -1 || cmpFunc(s[i], t[j]))
            {
                i++;
                j++;
            }
            else
                j = next[j];//回到相同前缀处如果j>0，说明i与j位置有相同的前缀
        }
        if (j == tlen)
            return i - tlen;
        else
            return -1;
    }
    else
    {
        i = tlen - 1, j = tlen;
        next[i] = tlen;
        while (i > 0)//生成next数组
        {
            if (j == tlen || cmpFunc(t[i], t[j]))//递推数组
            {
                i--;
                j--;
                //较之前next数组求法，改动在下面4行
                if (!cmpFunc(t[i], t[j]))
                    next[i] = j; //之前只有这一行
                else
                //因为不能出现t[j] = t[ next[j ]]，所以当出现时需要继续递归，j = next[j] = next[next[j]]
                    next[i] = next[j];
            }
            else
                j = next[j];//减少相同前缀的长度，寻找更短的前缀是否能匹配的上，直到j等于-1，再次匹配
        }
//        DEBUG<<"next : "<<Tool::printArr(next, 0, tlen - 1);

        i = high, j = tlen - 1;
        while (i >= low && j >= 0)
        {
            if (j == tlen || cmpFunc(s[i], t[j]))
            {
                i--;
                j--;
            }
            else
                j = next[j];//回到相同前缀处如果j>0，说明i与j位置有相同的前缀
        }
        if (j == -1)
            return i + 1;
        else
            return -1;
    }
}

int String::indexOf(char c, int from, bool isCaseSensitive) const
{
    if (m_length > 0 && c != '\0')
    {
        return match_char(m_str, from, m_length - 1, c, true, isCaseSensitive);
    }
    return -1;
}

int String::indexOf(const char *s, int from, bool isCaseSensitive) const
{
    int len = strlen(s);
    if (len == 0)
        return 0;
    if (m_length > 0)
    {
        return match_KMP(m_str, from, m_length - 1, s, len, true, isCaseSensitive);
    }
    return -1;
}

int String::indexOf(const String &s, int from, bool isCaseSensitive) const
{
    if (s.m_length == 0)
        return 0;
    if (m_length > 0)
    {
        return match_KMP(m_str, from, m_length - 1, s.m_str, s.m_length, true, isCaseSensitive);
    }
    return -1;
}

int String::lastIndexOf(char c, int from, bool isCaseSensitive) const
{
    if (m_length > 0 && c != '\0')
    {
        return match_char(m_str, from, m_length - 1, c, false, isCaseSensitive);
    }
    return -1;
}

int String::lastIndexOf(const char *s, int from, bool isCaseSensitive) const
{
    int len = strlen(s);
    if (len == 0)
        return m_length;
    if (m_length > 0)
    {
        return match_KMP(m_str, from, m_length - 1, s, len, false, isCaseSensitive);
    }
    return -1;
}

int String::lastIndexOf(const String &s, int from, bool isCaseSensitive) const
{
    if (s.m_length == 0)
        return m_length;
    if (m_length > 0)
    {
        return match_KMP(m_str, from, m_length - 1, s.m_str, s.m_length, false, isCaseSensitive);
    }
    return -1;
}

bool String::contains(char c, bool isCaseSensitive) const
{
    if (m_length > 0 && c != '\0')
    {
        return match_char(m_str, 0, m_length - 1, c, true, isCaseSensitive) != -1;
    }
    return false;
}

bool String::contains(const char *s, bool isCaseSensitive) const
{
    int len = strlen(s);
    if (len == 0)
        return true;
    if (m_length > 0)
    {
        return match_KMP(m_str, 0, m_length - 1, s, len, true, isCaseSensitive) != -1;
    }
    return false;
}

bool String::contains(const String &s, bool isCaseSensitive) const
{
    if (s.m_length == 0)
        return true;
    if (m_length > 0)
    {
        return match_KMP(m_str, 0, m_length - 1, s.m_str, s.m_length, true, isCaseSensitive) != -1;
    }
    return false;
}

String String::left(int n) const
{
    if (n < 0 || n >= m_length)
        return *this;
    else if (n == 0)
    {
        return String();
    }
    else
    {
        return String(m_str, n);
    }
}

String String::right(int n) const
{
    if (n < 0 || n >= m_length)
        return *this;
    else if (n == 0)
    {
        return String();
    }
    else
    {
        return String(m_str + m_length - n);
    }
}

String String::mid(int position, int n) const
{
    if (n < 0)
    {
        if (position < 0 || position >= m_length)
        {
            return String();
        }
        else if (position == 0)
        {
            return *this;
        }
        else
        {
            return String(m_str + position);
        }
    }
    else
    {
        if (n > m_length)
            n = m_length;
        if (position < 0 || position >= m_length || n == 0)
        {
            return String();
        }
        else if (position == 0 && n == m_length)
        {
            return *this;
        }
        else
        {
            return String(m_str + position, n);
        }
    }
}

bool String::startsWith(const char *s, bool isCaseSensitive) const
{
    int len = strlen(s);
    if (len == 0)
        return true;
    if (m_length == 0 || len > m_length)
        return false;
    bool (*cmpFunc)(const char &, const char &) = (isCaseSensitive ? charCmp_case_sensitive : charCmp_case_insensitive);
    for (int i = 0; i < len; i++)
    {
        if (!cmpFunc(m_str[i], s[i]))
            return false;
    }
    return true;
}

bool String::startsWith(const String &s, bool isCaseSensitive) const
{
    if (s.m_length == 0)
        return true;
    if (m_length == 0 || s.m_length > m_length)
        return false;
    bool (*cmpFunc)(const char &, const char &) = (isCaseSensitive ? charCmp_case_sensitive : charCmp_case_insensitive);
    for (int i = 0; i < s.m_length; i++)
    {
        if (!cmpFunc(m_str[i], s.m_str[i]))
            return false;
    }
    return true;
}

bool String::endsWith(const char *s, bool isCaseSensitive) const
{
    int len = strlen(s);
    if (len == 0)
        return true;
    if (m_length == 0 || len > m_length)
        return false;
    bool (*cmpFunc)(const char &, const char &) = (isCaseSensitive ? charCmp_case_sensitive : charCmp_case_insensitive);
    for (int i = 0; i < len; i++)
    {
        if (!cmpFunc(m_str[m_length - len + i], s[i]))
            return false;
    }
    return true;
}

bool String::endsWith(const String &s, bool isCaseSensitive) const
{
    if (s.m_length == 0)
        return true;
    if (m_length == 0 || s.m_length > m_length)
        return false;
    bool (*cmpFunc)(const char &, const char &) = (isCaseSensitive ? charCmp_case_sensitive : charCmp_case_insensitive);
    for (int i = 0; i < s.m_length; i++)
    {
        if (!cmpFunc(m_str[m_length - s.m_length + i], s.m_str[i]))
            return false;
    }
    return true;
}

StringList String::split(char sep, bool isCaseSensitive) const
{
    StringList list;
    if (m_length > 0)
    {
        int i = 0, index = 0;
        while (index != -1 && i < m_length)
        {
            index = indexOf(sep, i, isCaseSensitive);
            if (index == -1)
            {
                list.append(mid(i));
            }
            else
            {
                list.append(mid(i, index - i));
                i = index + 1;
            }
        }
    }
    return list;
}

StringList String::split(const String &sep, bool isCaseSensitive) const
{
    StringList list;
    if (m_length > 0 && sep.m_length > 0)
    {
        int i = 0, index = 0;
        while (index != -1 && i < m_length)
        {
            index = indexOf(sep, i, isCaseSensitive);
            if (index == -1)
            {
                list.append(mid(i));
            }
            else
            {
                list.append(mid(i, index - i));
                i = index + sep.length();
            }
        }
    }
    return list;
}

int String::compare(const char *s, bool isCaseSensitive) const
{
    int len = strlen(s);
    if (m_length == 0 && m_length == len)
        return 0;
    bool (*cmpFunc)(const char &, const char &) = (isCaseSensitive ? charCmp_case_sensitive : charCmp_case_insensitive);
    for (int i = 0; i < m_length && i < len; i++)
    {
        if (!cmpFunc(m_str[i], s[i]))
            return (m_str[i] > s[i] ? 1 : -1);
    }
    if (m_length != len)
    {
        return (m_length > len ? 1 : -1);
    }
    return 0;
}

int String::compare(const String &s, bool isCaseSensitive) const
{
    if (m_length == 0 && m_length == s.m_length)
        return 0;
    bool (*cmpFunc)(const char &, const char &) = (isCaseSensitive ? charCmp_case_sensitive : charCmp_case_insensitive);
    for (int i = 0; i < m_length && i < s.m_length; i++)
    {
        if (!cmpFunc(m_str[i], s.m_str[i]))
            return (m_str[i] > s.m_str[i] ? 1 : -1);
    }
    if (m_length != s.m_length)
    {
        return (m_length > s.m_length ? 1 : -1);
    }
    return 0;
}

String String::toLower() const
{
    String str = *this;
    str.removeRef();
    for (int i = 0; i < m_length; i++)
    {
        if (str.m_str[i] >= 'A' && str.m_str[i] <= 'Z')
            str.m_str[i] += 32;
    }
    return str;
}

String String::toUpper() const
{
    String str = *this;
    str.removeRef();
    for (int i = 0; i < m_length; i++)
    {
        if (str.m_str[i] >= 'a' && str.m_str[i] <= 'z')
            str.m_str[i] -= 32;
    }
    return str;
}

String String::trimmed() const
{
    if (m_length == 0)
        return String();
    int low = 0, high = m_length - 1;
    bool flag = true;
    while (low <= high && flag)
    {
        flag = false;
        if (m_str[low] == ' ' || m_str[low] == '\t' || m_str[low] == '\r' || m_str[low] == '\n' || m_str[low] == '\f')
        {
            low++;
            flag = true;
        }
        if (m_str[high] == ' ' || m_str[high] == '\t' || m_str[high] == '\r' || m_str[high] == '\n' || m_str[high] == '\f')
        {
            high--;
            flag = true;
        }
    }
    if (low >= high)
    {
        return String();
    }
    else
    {
        return String(m_str + low, high - low + 1);
    }
}

short String::toShort(bool *ok, int base) const
{
    return static_cast<short>(toLongLong(ok, base));
}

unsigned short String::toUShort(bool *ok, int base) const
{
    return static_cast<unsigned short>(toULongLong(ok, base));
}

int String::toInt(bool *ok, int base) const
{
    return static_cast<int>(toLongLong(ok, base));
}

unsigned int String::toUInt(bool *ok, int base) const
{
    return static_cast<unsigned int>(toULongLong(ok, base));
}

long String::toLong(bool *ok, int base) const
{
    return static_cast<long>(toLongLong(ok, base));
}

unsigned long String::toULong(bool *ok, int base) const
{
    return static_cast<unsigned long>(toULongLong(ok, base));
}

long long String::toLongLong(bool *ok, int base) const
{
    if (m_length == 0 || base < 2 || base > 36)
    {
        if (ok != nullptr)
        {
            *ok = false;
        }
        return 0;
    }
    char *err;
    long long i = strtoll(m_str, &err, base);
    if (ok != nullptr)
    {
        *ok = (*err == 0);
    }
    return i;
}

unsigned long long String::toULongLong(bool *ok, int base) const
{
    if (m_length == 0 || base < 2 || base > 36)
    {
        if (ok != nullptr)
        {
            *ok = false;
        }
        return 0;
    }
    char *err;
    unsigned long long i = strtoull(m_str, &err, base);
    if (ok != nullptr)
    {
        *ok = (*err == 0);
    }
    return i;
}

float String::toFloat(bool *ok) const
{
    if (m_length == 0)
    {
        if (ok != nullptr)
        {
            *ok = false;
        }
        return 0;
    }
    char *err;
    float i = strtof(m_str, &err);
    if (ok != nullptr)
    {
        *ok = (*err == 0);
    }
    return i;
}

double String::toDouble(bool *ok) const
{
    if (m_length == 0)
    {
        if (ok != nullptr)
        {
            *ok = false;
        }
        return 0;
    }
    char *err;
    double i = strtod(m_str, &err);
    if (ok != nullptr)
    {
        *ok = (*err == 0);
    }
    return i;
}

void String::removeRef()
{
    if (m_refCount != nullptr && *m_refCount > 1)
    {
        (*m_refCount)--;
        char *tmp = new char[m_capacity];
        memcpy(tmp, m_str, m_capacity);
        m_str = tmp;
        m_refCount = new int;
        *m_refCount = 1;
    }
}

String &String::insert(int i, char c)
{
    if (i < 0 || i > m_length || c == '\0')
        return *this;
    if (m_length + 2 > m_capacity)
    {
        int capacity = (m_capacity == 0 ? STRING_INIT_SIZE : m_capacity);
        while (m_length + 2 > capacity)
            capacity = 2 * capacity;
        resize(capacity);
    }
    else
        removeRef();
    for (int j = m_length; j > i; j--)//元素后移
        m_str[j] = m_str[j - 1];
    m_str[i] = c;
    m_length++;
    m_str[m_length] = '\0';
    return *this;
}

String &String::insert(int i, const char *s, int len)
{
    int _len = strlen(s);
    if (len > _len || len < 0)
        len = _len;
    if (len == 0 || i < 0 || i > m_length)
        return *this;
    if (m_length + 1 + len > m_capacity)
    {
        int capacity = (m_capacity == 0 ? STRING_INIT_SIZE : m_capacity);
        while (m_length + 1 + len > capacity)
            capacity = 2 * capacity;
        resize(capacity);
    }
    else
        removeRef();
    for (int j = m_length - 1 + len; j >= i + len; j--)
        m_str[j] = m_str[j - len];
    memcpy(m_str + i, s, len);
    m_length += len;
    m_str[m_length] = '\0';
    return *this;
}

String &String::insert(int i, const String &s)
{
    if (s.m_length == 0 || i < 0 || i > m_length)
        return *this;
    if (m_length + 1 + s.m_length > m_capacity)
    {
        int capacity = (m_capacity == 0 ? STRING_INIT_SIZE : m_capacity);
        while (m_length + 1 + s.m_length > capacity)
            capacity = 2 * capacity;
        resize(capacity);
    }
    else
        removeRef();
    for (int j = m_length - 1 + s.m_length; j >= i + s.m_length; j--)
        m_str[j] = m_str[j - s.m_length];
    memcpy(m_str + i, s.m_str, s.m_length);
    m_length += s.m_length;
    m_str[m_length] = '\0';
    return *this;
}

String &String::append(char c)
{
    return insert(m_length, c);
}

String &String::append(const char *s, int len)
{
    return insert(m_length, s, len);
}

String &String::append(const String &s)
{
    return insert(m_length, s);
}

String &String::prepend(char c)
{
    return insert(0, c);
}

String &String::prepend(const char *s, int len)
{
    return insert(0, s, len);
}

String &String::prepend(const String &s)
{
    return insert(0, s);
}

String &String::remove(int i, int len)
{
    if (i < 0 || i >= m_length || len <= 0)
        return *this;
    removeRef();
    if (len > m_length - i)
        len = m_length - i;
    for (int j = i; j < m_length - len; j++)
        m_str[j] = m_str[j + len];
    m_length -= len;
    m_str[m_length] = '\0';
    return *this;
}

String &String::remove(char c, bool isCaseSensitive)
{
    if (!contains(c, isCaseSensitive))
        return *this;
    removeRef();
    bool (*cmpFunc)(const char &, const char &) = (isCaseSensitive ? charCmp_case_sensitive : charCmp_case_insensitive);
    int i, j, num = 0;
    for (i = 0, j = 0; i < m_length; i++)
    {
        if (!cmpFunc(m_str[i], c))
        {
            if (num > 0)
            {
                m_str[j] = m_str[i];
            }
            j++;
        }
        else
        {
            num++;
        }
    }
    m_length = m_length - num;
    m_str[m_length] = '\0';
    return *this;
}

String &String::remove(const String &s, bool isCaseSensitive)
{
    int index = indexOf(s, 0, isCaseSensitive);
    if (index == -1 || s.m_length == 0)
        return *this;
    removeRef();
    int i, j, num = 0;
    for (i = 0, j = 0; i < m_length; i++)
    {
        if (i < index || index == -1)
        {
            if (num > 0)
            {
                m_str[j] = m_str[i];
            }
            j++;
        }
        else if (i == index)
        {
            i = index + s.m_length - 1;
            index = indexOf(s, i + 1, isCaseSensitive);
            num += s.m_length;
        }
    }
    m_length = m_length - num;
    m_str[m_length] = '\0';
    return *this;
}

String &String::replace(int i, int len, char c)
{
    if (i < 0 || i >= m_length || len <= 0 || c == '\0')
        return *this;
    removeRef();
    if (len > m_length - i)
        len = m_length - i;
    memset(m_str + i, c, len);
    return *this;
}

String &String::replace(int i, int len, const char *s, int slen)
{
    return replace(i, len, String(s, slen));
}

String &String::replace(int i, int len, const String &s)
{
    if (i < 0 || i >= m_length || len <= 0)
        return *this;
    if (len > m_length - i)
        len = m_length - i;
    if (len == s.m_length && strncmp(m_str + i, s.m_str, len) == 0)
        return *this;
    removeRef();
    if (len > s.m_length)
    {
        for (int j = i + s.m_length; j < m_length - s.m_length; j++)
            m_str[j] = m_str[j + s.m_length];
    }
    else if (len < s.m_length)
    {
        int offset = s.m_length - len;
        if (m_length + 1 + offset > m_capacity)
        {
            int capacity = (m_capacity == 0 ? STRING_INIT_SIZE : m_capacity);
            while (m_length + 1 + offset > capacity)
                capacity = 2 * capacity;
            resize(capacity);
        }
        for (int j = m_length - 1 + offset; j >= i + s.m_length; j--)
            m_str[j] = m_str[j - offset];
    }
    if (s.m_length > 0)
        strncpy(m_str + i, s.m_str, s.m_length);
    m_length = m_length + s.m_length - len;
    m_str[m_length] = '\0';
    return *this;
}

String &String::replace(char before, char after, bool isCaseSensitive)
{
    if (!contains(before, isCaseSensitive) || before == after || after == '\0')
        return *this;
    removeRef();
    bool (*cmpFunc)(const char &, const char &) = (isCaseSensitive ? charCmp_case_sensitive : charCmp_case_insensitive);
    for (int i = 0; i < m_length; i++)
    {
        if (cmpFunc(m_str[i], before))
            m_str[i] = after;
    }
    return *this;
}

String &String::replace(const char *before, int blen, const char *after, int alen, bool isCaseSensitive)
{
    return replace(String(before, blen), String(after, alen), isCaseSensitive);
}

String &String::replace(const String &before, const String &after, bool isCaseSensitive)
{
    int index = indexOf(before, 0, isCaseSensitive);
    if (index == -1 || before.m_length == 0 || before == after)
        return *this;
    removeRef();
    if (after.m_length == 0)
    {
        remove(before, isCaseSensitive);
    }
    else
    {
        while (index != -1)
        {
            replace(index, before.m_length, after);
            index += after.m_length;
            index = indexOf(before, index, isCaseSensitive);
        }
    }
    return *this;
}

String &String::setNum(short num, int base)
{
    *this = String::number(num, base);
    return *this;
}

String &String::setNum(unsigned short num, int base)
{
    *this = String::number(num, base);
    return *this;
}

String &String::setNum(int num, int base)
{
    *this = String::number(num, base);
    return *this;
}

String &String::setNum(unsigned int num, int base)
{
    *this = String::number(num, base);
    return *this;
}

String &String::setNum(long num, int base)
{
    *this = String::number(num, base);
    return *this;
}

String &String::setNum(unsigned long num, int base)
{
    *this = String::number(num, base);
    return *this;
}

String &String::setNum(long long num, int base)
{
    *this = String::number(num, base);
    return *this;
}

String &String::setNum(unsigned long long num, int base)
{
    *this = String::number(num, base);
    return *this;
}

String &String::setNum(float num)
{
    *this = String::number(static_cast<double>(num));
    return *this;
}

String &String::setNum(double num)
{
    *this = String::number(num);
    return *this;
}

String String::number(int num, int base)
{
    return String::number(static_cast<long long>(num), base);
}

String String::number(unsigned int num, int base)
{
    return String::number(static_cast<unsigned long long>(num), base);
}

String String::number(long num, int base)
{
    return String::number(static_cast<long long>(num), base);
}

String String::number(unsigned long num, int base)
{
    return String::number(static_cast<unsigned long long>(num), base);
}

String String::number(long long num, int base)
{
    String str;
    char arr[100] = {0};
    int len = 0;
    char sign = '\0';
    if (base < 2)
        base = 2;
    if (base > 16)
        base = 16;
    if (num == 0)
    {
        arr[len] = '0';
        len++;
    }
    else
    {
        if (num < 0)
        {
            sign = '-';
            num = (-1) * num;
        }
        while (num > 0 && len < 100)
        {
            arr[len] = m_digit[num % base];
            num = num / base;
            len++;
        }
    }
    if (len + 1 > str.m_capacity)
    {
        int capacity = (str.m_capacity == 0 ? STRING_INIT_SIZE : str.m_capacity);
        while (len + 1 > capacity)
            capacity = 2 * capacity;
        str.resize(capacity);
    }
    for (int i = 0; i < len; i++)
        str.m_str[i] = arr[len - 1 - i];
    str.m_str[len] = '\0';
    str.m_length = len;
    if (sign != '\0')
        str.prepend(sign);
    return str;
}

String String::number(unsigned long long num, int base)
{
    String str;
    char arr[100] = {0};
    int len = 0;
    if (base < 2)
        base = 2;
    if (base > 16)
        base = 16;
    if (num == 0)
    {
        arr[len] = '0';
        len++;
    }
    else
    {
        while (num > 0 && len < 100)
        {
            arr[len] = m_digit[num % base];
            num = num / base;
            len++;
        }
    }
    if (len + 1 > str.m_capacity)
    {
        int capacity = (str.m_capacity == 0 ? STRING_INIT_SIZE : str.m_capacity);
        while (len + 1 > capacity)
            capacity = 2 * capacity;
        str.resize(capacity);
    }
    for (int i = 0; i < len; i++)
        str.m_str[i] = arr[len - 1 - i];
    str.m_str[len] = '\0';
    str.m_length = len;
    return str;
}

String String::number(double num)
{
    String str;
    char arr[100] = {0};
    int len = 0;
    char sign = '\0';
    if (num < 0)
    {
        sign = '-';
        num = (-1) * num;
    }
    long long num1 = static_cast<long long>(num);
    double num2 = num - num1 * 1.0;
    str = String::number(num1);
    if (sign != '\0')
        str.prepend(sign);
    if (num2 > 0)
    {
        str.append('.');
        int i = 0;
        while (num2 > 0 && i < 5)
        {
            num2 = num2 * 10.0;
            num1 = static_cast<long long>(num2);
            str.append(m_digit[num1]);
            i++;
            num2 = num2 - num1 * 1.0;
        }
        while (str.at(str.m_length - 1) == '0')
            str.remove(str.m_length - 1, 1);
    }
    return str;
}

bool String::operator==(const String &s) const
{
    return compare(s) == 0;
}

bool String::operator==(const char *s) const
{
    return compare(s) == 0;
}

bool operator==(const char *s1, const String &s2)
{
    return s2.compare(s1) == 0;
}

bool String::operator!=(const String &s) const
{
    return compare(s) != 0;
}

bool String::operator!=(const char *s) const
{
    return compare(s) != 0;
}

bool operator!=(const char *s1, const String &s2)
{
    return s2.compare(s1) != 0;
}

bool String::operator>(const String &s) const
{
    return compare(s) > 0;
}

bool String::operator>(const char *s) const
{
    return compare(s) > 0;
}

bool operator>(const char *s1, const String &s2)
{
    return s2.compare(s1) < 0;
}

bool String::operator<(const String &s) const
{
    return compare(s) < 0;
}

bool String::operator<(const char *s) const
{
    return compare(s) < 0;
}

bool operator<(const char *s1, const String &s2)
{
    return s2.compare(s1) > 0;
}

bool String::operator>=(const String &s) const
{
    return compare(s) >= 0;
}

bool String::operator>=(const char *s) const
{
    return compare(s) >= 0;
}

bool operator>=(const char *s1, const String &s2)
{
    return s2.compare(s1) <= 0;
}

bool String::operator<=(const String &s) const
{
    return compare(s) <= 0;
}

bool String::operator<=(const char *s) const
{
    return compare(s) <= 0;
}

bool operator<=(const char *s1, const String &s2)
{
    return s2.compare(s1) >= 0;
}

String &String::operator+=(char c)
{
    return append(c);
}

String &String::operator+=(const char *s)
{
    return append(s);
}

String &String::operator+=(const String &s)
{
    return append(s);
}

String operator+(char c, const String &s)
{
    return String(s).prepend(c);
}

String operator+(const String &s, char c)
{
    return String(s).append(c);
}

String operator+(const String &s1, const char *s2)
{
    return String(s1).append(s2);
}

String operator+(const char *s1, const String &s2)
{
    return String(s2).prepend(s1);
}

String operator+(const String &s1, const String &s2)
{
    return String(s1).append(s2);
}
