#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include <assert.h>
#include <QString>

#define SEQQUEUE_INIT_SIZE 100

template <typename T>
class SeqQueue
{
public:
    SeqQueue(int capacity = SEQQUEUE_INIT_SIZE);
    ~SeqQueue();
    int getSize();
    int getCapacity();
    void clear();
    T &head();
    void expand();
    void enqueue(const T &t);
    void insert(int i, const T &t);
    T dequeue();
    QString print();

public:
    T *m_elem;
    int m_size;
    int m_capacity;

};

template<typename T>
SeqQueue<T>::SeqQueue(int capacity)
{
    m_size = 0;
    if (capacity <= 0)
    {
        m_capacity = SEQQUEUE_INIT_SIZE;
    }
    else
    {
        m_capacity = capacity;
    }
    m_elem = new T[m_capacity];
}

template<typename T>
SeqQueue<T>::~SeqQueue()
{
    if (m_elem != NULL)
        delete[] m_elem;
}

template<typename T>
int SeqQueue<T>::getSize()
{
    return m_size;
}

template<typename T>
int SeqQueue<T>::getCapacity()
{
    return m_capacity;
}

template<typename T>
void SeqQueue<T>::clear()
{
    m_size = 0;
}

template<typename T>
T &SeqQueue<T>::head()
{
    assert(m_size > 0);
    return m_elem[0];
}

template<typename T>
void SeqQueue<T>::expand()
{
    m_capacity = m_capacity * 2;
    T *tmp = new T[m_capacity];
    if (m_elem != NULL)
    {
        for (int i = 0; i < m_size; i++)
            tmp[i] = m_elem[i];
        delete[] m_elem;
    }
    m_elem = tmp;
}

template<typename T>
void SeqQueue<T>::enqueue(const T &t)
{
    if (m_size >= m_capacity)
    {
        expand();
    }
    m_elem[m_size] = t;
    m_size++;
}

template<typename T>
void SeqQueue<T>::insert(int i, const T &t)
{
    if (i < 0 || i > m_size)
        return;
    if (m_size >= m_capacity)
    {
        expand();
    }
    if (m_size > 0)
    {
        for (int j = m_size; j > i; j--)//元素后移
            m_elem[j] = m_elem[j - 1];
    }
    m_elem[i] = t;
    m_size++;
}

template<typename T>
T SeqQueue<T>::dequeue()
{
    assert(m_size > 0);
    T tmp = m_elem[0];
    m_size--;
    for (int i = 0; i < m_size; i++)
        m_elem[i] = m_elem[i + 1];
    return tmp;
}

template<typename T>
QString SeqQueue<T>::print()
{
    QString info;
    for (int i = 0; i < m_size; i++)
    {
        info.append(QString::number(m_elem[i]) + " ");
    }
    return info;
}

#endif // SEQQUEUE_H
