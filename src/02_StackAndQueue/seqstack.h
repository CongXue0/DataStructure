#ifndef SEQSTACK_H
#define SEQSTACK_H

#include <assert.h>
#include <QString>

#define SEQSTACK_INIT_SIZE 40

template <typename T>
class SeqStack
{
public:
    SeqStack(int capacity = SEQSTACK_INIT_SIZE);
    ~SeqStack();
    int getSize();
    int getCapacity();
    void clear();
    T &top(int i = 1);//返回栈顶倒数第几个结点
    void expand();
    void push(const T &t);
    void insert(int i, const T &t);
    T pop();
    QString print();

public:
    T *m_elem;
    int m_size;
    int m_capacity;

};

template<typename T>
SeqStack<T>::SeqStack(int capacity)
{
    m_size = 0;
    if (capacity <= 0)
    {
        m_capacity = SEQSTACK_INIT_SIZE;
    }
    else
    {
        m_capacity = capacity;
    }
    m_elem = new T[m_capacity];
}

template<typename T>
SeqStack<T>::~SeqStack()
{
    if (m_elem != NULL)
        delete[] m_elem;
}

template<typename T>
int SeqStack<T>::getSize()
{
    return m_size;
}

template<typename T>
int SeqStack<T>::getCapacity()
{
    return m_capacity;
}

template<typename T>
void SeqStack<T>::clear()
{
    m_size = 0;
}

template<typename T>
T &SeqStack<T>::top(int i)
{
    assert(m_size > 0 && i > 0 && i <= m_size);
    return m_elem[m_size - i];
}

template<typename T>
void SeqStack<T>::expand()
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
void SeqStack<T>::push(const T &t)
{
    if (m_size >= m_capacity)
    {
        expand();
    }
    m_elem[m_size] = t;
    m_size++;
}

template<typename T>
void SeqStack<T>::insert(int i, const T &t)
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
T SeqStack<T>::pop()
{
    assert(m_size > 0);
    m_size--;
    return m_elem[m_size];
}

template<typename T>
QString SeqStack<T>::print()
{
    QString info;
    for (int i = 0; i < m_size; i++)
    {
        info.append(QString::number(m_elem[i]) + " ");
    }
    return info;
}

#endif // SEQSTACK_H
