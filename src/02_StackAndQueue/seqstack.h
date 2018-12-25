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
    T &top();
    void push(const T &t);
    T pop();
    QString print();

private:
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
T &SeqStack<T>::top()
{
    assert(m_size > 0);
    return m_elem[m_size - 1];
}

template<typename T>
void SeqStack<T>::push(const T &t)
{
    if (m_size >= m_capacity)
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
    m_elem[m_size] = t;
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
