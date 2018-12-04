#ifndef LINKLIST_H
#define LINKLIST_H

#include <assert.h>
#include <QString>

template <typename T>
class LinkList
{
public:
    class LinkListNode
    {
    public:
        LinkListNode()
        {
            next = NULL;
        }
        T data;
        LinkListNode *next;
    };
    LinkList();
    ~LinkList();
    int getLength();
    void clear();
    const T &at(int i) const;
    T &operator[](int i);
    void insert(int i, const T &t);
    void append(const T &t);
    LinkList<T> &operator<<(const T &t) { append(t); return *this; }
    void removeAt(int i);
    void removeAll(const T &t);
    bool contains(const T &t);
    QString print();

public:
    LinkListNode *m_header;
    int m_length;
};

template<typename T>
LinkList<T>::LinkList()
{
    m_header = NULL;
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
    LinkListNode *tmp;
    while (m_header != NULL)
    {
        tmp = m_header;
        m_header = m_header->next;
        delete tmp;
    }
    m_length = 0;
}

template<typename T>
const T &LinkList<T>::at(int i) const
{
    assert(i >= 0 && i < m_length);
    LinkListNode *tmp = m_header;
    for (int j = 0; j < i; j++)
        tmp = tmp->next;
    return tmp->data;
}

template<typename T>
T &LinkList<T>::operator[](int i)
{
    assert(i >= 0 && i < m_length);
    LinkListNode *tmp = m_header;
    for (int j = 0; j < i; j++)
        tmp = tmp->next;
    return tmp->data;
}

template<typename T>
void LinkList<T>::insert(int i, const T &t)
{
    if (i < 0 || i > m_length)
        return;
    LinkListNode *node = new LinkListNode();
    node->data = t;
    if (i == 0)
    {
        node->next = m_header;
        m_header = node;
    }
    else
    {
        LinkListNode *tmp = m_header;
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
    LinkListNode *node = new LinkListNode();
    node->data = t;
    node->next = NULL;
    if (m_header == NULL)
    {
        m_header = node;
    }
    else
    {
        LinkListNode *tmp = m_header;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = node;
    }
    m_length++;
}

template<typename T>
void LinkList<T>::removeAt(int i)
{
    if (i < 0 || i >= m_length)
        return;
    LinkListNode *tmp1 = m_header;
    if (i == 0)
    {
        m_header = tmp1->next;
        delete tmp1;
    }
    else
    {
        for (int j = 0; j < i - 1; j++)
            tmp1 = tmp1->next;
        LinkListNode *tmp2 = tmp1->next;
        tmp1->next = tmp2->next;
        delete tmp2;
    }
    m_length--;
}

template<typename T>
void LinkList<T>::removeAll(const T &t)
{
    LinkListNode *tmp1 = NULL;
    LinkListNode *tmp2 = m_header;
    int i = 0;
    while (tmp2 != NULL)
    {
        if (tmp2->data == t)
        {
            if (i == 0)
            {
                m_header = tmp2->next;
                delete tmp2;
                m_length--;
                tmp2 = m_header;
            }
            else
            {
                tmp1->next = tmp2->next;
                delete tmp2;
                m_length--;
                tmp2 = tmp1->next;
            }
        }
        else
        {
            tmp1 = tmp2;
            tmp2 = tmp2->next;
            i++;
        }
    }
}

template<typename T>
bool LinkList<T>::contains(const T &t)
{
    LinkListNode *tmp = m_header;
    while (tmp != NULL)
    {
        if (tmp->data == t)
            return true;
        tmp = tmp->next;
    }
    return false;
}

template<typename T>
QString LinkList<T>::print()
{
    QString info;
    LinkListNode *tmp = m_header;
    for (int i = 0; i < m_length; i++)
    {
        info.append(QString::number(tmp->data) + " ");
        tmp = tmp->next;
    }
    return info;
}

#endif // LINKLIST_H
