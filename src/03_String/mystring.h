#ifndef MYSTRING_H
#define MYSTRING_H

#include "src/01_LinearList/linklist.h"
#include "src/03_String/mystringlist.h"

#define STRING_INIT_SIZE 20

class String
{
public:
    String();
    String(const char *str, int len = -1);
    String(const String &str);
    String(String &&str);
    ~String();
    String &operator=(const String &str);
    String &operator=(String &&str);
    int size() const;
    int length() const;
    int capacity() const;
    int getRefCount() const;
    bool isEmpty() const;
    const char *data() const;
    void clear();
    void resize(int size);
    void swap(String &other);
    String &fill(char c, int size = -1);
    char at(int i) const;
    char operator[](int i) const;
    static inline bool charCmp_case_sensitive(const char &a, const char &b);
    static inline bool charCmp_case_insensitive(const char &a, const char &b);
    static int match_char(const char *s, int low, int high, const char &c, bool isPositive, bool isCaseSensitive);
    static int match_normal(const char *s, int low, int high, const char *t, int tlen, bool isPositive, bool isCaseSensitive);
    static int match_KMP(const char *s, int low, int high, const char *t, int tlen, bool isPositive, bool isCaseSensitive);
    int indexOf(char c, int from = 0, bool isCaseSensitive = true) const;
    int indexOf(const char *s, int from = 0, bool isCaseSensitive = true) const;
    int indexOf(const String &s, int from = 0, bool isCaseSensitive = true) const;
    int lastIndexOf(char c, int from = -1, bool isCaseSensitive = true) const;
    int lastIndexOf(const char *s, int from = -1, bool isCaseSensitive = true) const;
    int lastIndexOf(const String &s, int from = -1, bool isCaseSensitive = true) const;
    bool contains(char c, bool isCaseSensitive = true) const;
    bool contains(const char *s, bool isCaseSensitive = true) const;
    bool contains(const String &s, bool isCaseSensitive = true) const;
    String left(int n) const;
    String right(int n) const;
    String mid(int position, int n = -1) const;
    bool startsWith(const char *s, bool isCaseSensitive = true) const;
    bool startsWith(const String &s, bool isCaseSensitive = true) const;
    bool endsWith(const char *s, bool isCaseSensitive = true) const;
    bool endsWith(const String &s, bool isCaseSensitive = true) const;
    StringList split(char sep, bool isCaseSensitive = true) const;
    StringList split(const String &sep, bool isCaseSensitive = true) const;
    int compare(const char *s, bool isCaseSensitive = true) const;
    int compare(const String &s, bool isCaseSensitive = true) const;
    String toLower() const;
    String toUpper() const;
    String trimmed() const;
    short toShort(bool *ok = nullptr, int base = 10) const;
    unsigned short toUShort(bool *ok = nullptr, int base = 10) const;
    int toInt(bool *ok = nullptr, int base = 10) const;
    unsigned int toUInt(bool *ok = nullptr, int base = 10) const;
    long toLong(bool *ok = nullptr, int base = 10) const;
    unsigned long toULong(bool *ok = nullptr, int base = 10) const;
    long long toLongLong(bool *ok = nullptr, int base = 10) const;
    unsigned long long toULongLong(bool *ok = nullptr, int base = 10) const;
    float toFloat(bool *ok = nullptr) const;
    double toDouble(bool *ok = nullptr) const;
    void removeRef();
    String &insert(int i, char c);
    String &insert(int i, const char *s, int len = -1);
    String &insert(int i, const String &s);
    String &append(char c);
    String &append(const char *s, int len = -1);
    String &append(const String &s);
    String &prepend(char c);// { return insert(0, c); }
    String &prepend(const char *s, int len = -1);// { return insert(0, s, len); }
    String &prepend(const String &s);// { return insert(0, s); }
    String &remove(int i, int len);
    String &remove(char c, bool isCaseSensitive = true);
    String &remove(const String &s, bool isCaseSensitive = true);
    String &replace(int i, int len, char c);
    String &replace(int i, int len, const char *s, int slen = -1);
    String &replace(int i, int len, const String &s);
    String &replace(char before, char after, bool isCaseSensitive = true);
    String &replace(const char *before, int blen, const char *after, int alen, bool isCaseSensitive = true);
    String &replace(const String &before, const String &after, bool isCaseSensitive = true);
    String &setNum(short num, int base = 10);
    String &setNum(unsigned short num, int base = 10);
    String &setNum(int num, int base = 10);
    String &setNum(unsigned int num, int base = 10);
    String &setNum(long num, int base = 10);
    String &setNum(unsigned long num, int base = 10);
    String &setNum(long long num, int base = 10);
    String &setNum(unsigned long long num, int base = 10);
    String &setNum(float num);
    String &setNum(double num);
    static String number(int num, int base = 10);
    static String number(unsigned int num, int base = 10);
    static String number(long num, int base = 10);
    static String number(unsigned long num, int base = 10);
    static String number(long long num, int base = 10);
    static String number(unsigned long long num, int base = 10);
    static String number(double num);

    bool operator==(const String &s) const;
    bool operator==(const char *s) const;
    friend bool operator==(const char *s1, const String &s2);
    bool operator!=(const String &s) const;
    bool operator!=(const char *s) const;
    friend bool operator!=(const char *s1, const String &s2);
    bool operator>(const String &s) const;
    bool operator>(const char *s) const;
    friend bool operator>(const char *s1, const String &s2);
    bool operator<(const String &s) const;
    bool operator<(const char *s) const;
    friend bool operator<(const char *s1, const String &s2);
    bool operator>=(const String &s) const;
    bool operator>=(const char *s) const;
    friend bool operator>=(const char *s1, const String &s2);
    bool operator<=(const String &s) const;
    bool operator<=(const char *s) const;
    friend bool operator<=(const char *s1, const String &s2);

    String &operator+=(char c);
    String &operator+=(const char *s);
    String &operator+=(const String &s);

public:
    static char m_digit[16];
    char *m_str;
    int m_length;
    int m_capacity;
    int *m_refCount;//引用计数

};

String operator+(char c, const String &s);
String operator+(const String &s, char c);
String operator+(const String &s1, const char *s2);
String operator+(const char *s1, const String &s2);
String operator+(const String &s1, const String &s2);

#endif // MYSTRING_H
