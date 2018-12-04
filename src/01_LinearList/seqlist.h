#ifndef SEQLIST_H
#define SEQLIST_H

#include <assert.h>
#include <QString>

#define SEQLIST_INIT_SIZE 100

template <typename T>
class SeqList
{
public:
    SeqList(int capacity = SEQLIST_INIT_SIZE);
    ~SeqList();
    int getLength();
    int getCapacity();
    void clear();
    const T &at(int i) const;
    T &operator[](int i);
    void insert(int i, const T &t);
    void append(const T &t);
    void removeAt(int i);
    void removeAll(const T &t);
    bool contains(const T &t);
    QString print();

private:
    T *m_elem;
    int m_length;
    int m_capacity;

};

template<typename T>
SeqList<T>::SeqList(int capacity)
{
    m_length = 0;
    if (capacity <= 0)
    {
        m_capacity = SEQLIST_INIT_SIZE;
    }
    else
    {
        m_capacity = capacity;
    }
    m_elem = new T[m_capacity];
}

template<typename T>
SeqList<T>::~SeqList()
{
    if (m_elem != NULL)
        delete[] m_elem;
}

template<typename T>
int SeqList<T>::getLength()
{
    return m_length;
}

template<typename T>
int SeqList<T>::getCapacity()
{
    return m_capacity;
}

template<typename T>
void SeqList<T>::clear()
{
    m_length = 0;
}

template<typename T>
const T &SeqList<T>::at(int i) const
{
    assert(i >= 0 && i < m_length);
    return m_elem[i];
}

template<typename T>
T &SeqList<T>::operator[](int i)
{
    assert(i >= 0 && i < m_length);
    return m_elem[i];
}

template<typename T>
void SeqList<T>::insert(int i, const T &t)
{
    if (i < 0 || i > m_length)
        return;
    if (m_length >= m_capacity)
    {
        m_capacity = m_capacity * 2;
        T *tmp = new T[m_capacity];
        if (m_elem != NULL)
        {
            for (int j = 0; j < m_length; j++)
                tmp[j] = m_elem[j];
            delete[] m_elem;
        }
        m_elem = tmp;
    }
    if (m_length > 0)
    {
        for (int j = m_length; j > i; j--)//元素后移
            m_elem[j] = m_elem[j - 1];
    }
    m_elem[i] = t;
    m_length++;
}

template<typename T>
void SeqList<T>::append(const T &t)
{
    if (m_length >= m_capacity)
    {
        m_capacity = m_capacity * 2;
        T *tmp = new T[m_capacity];
        if (m_elem != NULL)
        {
            for (int j = 0; j < m_length; j++)
                tmp[j] = m_elem[j];
            delete[] m_elem;
        }
        m_elem = tmp;
    }
    m_elem[m_length] = t;
    m_length++;
}

template<typename T>
void SeqList<T>::removeAt(int i)
{
    if (i < 0 || i >= m_length)
        return;
    m_length--;
    for (int j = i; j < m_length; j++)
        m_elem[j] = m_elem[j + 1];
}

template<typename T>
void SeqList<T>::removeAll(const T &t)
{
    int i, j, num = 0;
    for (i = 0, j = 0; i < m_length; i++)
    {
        if (m_elem[i] != t)
        {
            if (num > 0)
            {
                m_elem[j] = m_elem[i];
            }
            j++;
        }
        else
        {
            num++;
        }
    }
    m_length = m_length - num;
}

template<typename T>
bool SeqList<T>::contains(const T &t)
{
    for (int i = 0; i < m_length; i++)
    {
        if (m_elem[i] == t)
            return true;
    }
    return false;
}

template<typename T>
QString SeqList<T>::print()
{
    QString info;
    for (int i = 0; i < m_length; i++)
    {
        info.append(QString::number(m_elem[i]) + " ");
    }
    return info;
}

#endif // SEQLIST_H
