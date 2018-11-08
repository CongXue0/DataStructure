#ifndef DOUBLELINKLIST_H
#define DOUBLELINKLIST_H

#include <assert.h>
#include "src/01_LinearList/chapter1_part1.h"

template <typename T>
class DoubleLinkListNode
{
public:
    DoubleLinkListNode()
    {
        prior = nullptr;
        next = nullptr;
    }
    T data;
    DoubleLinkListNode *prior;
    DoubleLinkListNode *next;
};

template <typename T>
class DoubleLinkList //双向链表
{
public:
    friend class Chapter1_Part1;
    DoubleLinkList();
    ~DoubleLinkList();
    int getLength();
    void clear();
    const T &at(int i) const;
    T &operator[](int i);
    void insert(int i, const T &t);
    void append(const T &t);
    void removeAt(int i);

private:
    DoubleLinkListNode<T> *m_header;
    int m_length;

};

template<typename T>
DoubleLinkList<T>::DoubleLinkList()
{
    m_header = nullptr;
    m_length = 0;
}

template<typename T>
DoubleLinkList<T>::~DoubleLinkList()
{
    clear();
}

template<typename T>
int DoubleLinkList<T>::getLength()
{
    return m_length;
}

template<typename T>
void DoubleLinkList<T>::clear()
{
    while (m_length > 0)
        removeAt(0);
}

template<typename T>
const T &DoubleLinkList<T>::at(int i) const
{
    assert(i >= 0 && i < m_length);
    DoubleLinkListNode<T> *tmp = m_header;
    for (int j = 0; j < i; j++)
        tmp = tmp->next;
    return tmp->data;
}

template<typename T>
T &DoubleLinkList<T>::operator[](int i)
{
    assert(i >= 0 && i < m_length);
    DoubleLinkListNode<T> *tmp = m_header;
    for (int j = 0; j < i; j++)
        tmp = tmp->next;
    return tmp->data;
}

template<typename T>
void DoubleLinkList<T>::insert(int i, const T &t)
{
    if (i < 0 || i > m_length)
        return;
    DoubleLinkListNode<T> *node = new DoubleLinkListNode<T>();
    node->data = t;
    if (m_length == 0)
    {
        node->prior = node;
        node->next = node;
        m_header = node;
    }
    else
    {
        DoubleLinkListNode<T> *tmp = m_header;
        for (int j = 0; j < i; j++)//找到插入位置
            tmp = tmp->next;
        node->prior = tmp->prior;
        node->next = tmp;
        tmp->prior->next = node;
        tmp->prior = node;
    }
    m_length++;
}

template<typename T>
void DoubleLinkList<T>::append(const T &t)
{
    insert(m_length, t);
}

template<typename T>
void DoubleLinkList<T>::removeAt(int i)
{
    if (i < 0 || i >= m_length)
        return;
    if (m_length == 1)
    {
        delete m_header;
        m_header = nullptr;
    }
    else
    {
        DoubleLinkListNode<T> *tmp = m_header;
        for (int j = 0; j < i; j++)//找到插入位置
            tmp = tmp->next;
        tmp->prior->next = tmp->next;
        tmp->next->prior = tmp->prior;
        delete tmp;
    }
    m_length--;
}

#endif // DOUBLELINKLIST_H
