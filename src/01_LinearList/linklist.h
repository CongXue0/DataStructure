#ifndef LINKLIST_H
#define LINKLIST_H

#include <assert.h>
#include "src/01_LinearList/chapter1_part1.h"

template <typename T>
class LinkListNode
{
public:
    LinkListNode()
    {
        next = nullptr;
    }
    T data;
    LinkListNode *next;
};

template <typename T>
class LinkList
{
public:
    friend class Chapter1_Part1;
    LinkList();
    ~LinkList();
    int getLength();
    void clear();
    const T &at(int i) const;
    T &operator[](int i);
    void insert(int i, const T &t);
    void append(const T &t);
    void removeAt(int i);

private:
    LinkListNode<T> *m_header;
    int m_length;
};

template<typename T>
LinkList<T>::LinkList()
{
    m_header = nullptr;
    m_length = 0;
}

template<typename T>
LinkList<T>::~LinkList()
{
    clear();
}

template<typename T>
int LinkList<T>::getLength()
{
    return m_length;
}

template<typename T>
void LinkList<T>::clear()
{
    while (m_length > 0)
        removeAt(0);
}

template<typename T>
const T &LinkList<T>::at(int i) const
{
    assert(i >= 0 && i < m_length);
    LinkListNode<T> *tmp = m_header;
    for (int j = 0; j < i; j++)
        tmp = tmp->next;
    return tmp->data;
}

template<typename T>
T &LinkList<T>::operator[](int i)
{
    assert(i >= 0 && i < m_length);
    LinkListNode<T> *tmp = m_header;
    for (int j = 0; j < i; j++)
        tmp = tmp->next;
    return tmp->data;
}

template<typename T>
void LinkList<T>::insert(int i, const T &t)
{
    if (i < 0 || i > m_length)
        return;
    LinkListNode<T> *node = new LinkListNode<T>();
    node->data = t;
    if (i == 0)
    {
        node->next = m_header;
        m_header = node;
    }
    else
    {
        LinkListNode<T> *tmp = m_header;
        for (int j = 0; j < i - 1; j++)//找到插入位置的前驱
            tmp = tmp->next;
        node->next = tmp->next;
        tmp->next = node;
    }
    m_length++;
}

template<typename T>
void LinkList<T>::append(const T &t)
{
    insert(m_length, t);
}

template<typename T>
void LinkList<T>::removeAt(int i)
{
    if (i < 0 || i >= m_length)
        return;
    LinkListNode<T> *tmp1 = m_header;
    if (i == 0)
    {
        m_header = tmp1->next;
        delete tmp1;
    }
    else
    {
        for (int j = 0; j < i - 1; j++)
            tmp1 = tmp1->next;
        LinkListNode<T> *tmp2 = tmp1->next;
        tmp1->next = tmp2->next;
        delete tmp2;
    }
    m_length--;
}

#endif // LINKLIST_H
