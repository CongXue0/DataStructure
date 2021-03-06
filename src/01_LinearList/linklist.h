#ifndef LINKLIST_H
#define LINKLIST_H

#include <assert.h>
#include <QString>
#include <QDebug>

#define LINKLIST_CONS_DEBUG 0

template <typename T>
class LinkList
{
public:
    class LinkListNode
    {
    public:
        LinkListNode() : next(NULL) {}
        LinkListNode(const T &t) : data(t) , next(NULL) {}
        T data;
        LinkListNode *next;
    };
    LinkList();
    LinkList(const LinkList &list);
    ~LinkList();
    LinkList &operator=(const LinkList &list);
    LinkList &operator=(LinkList &&list);
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
    LinkListNode *m_head;
    int m_length;
};

template<typename T>
LinkList<T>::LinkList()
{
#if LINKLIST_CONS_DEBUG == 1
    qDebug() << "LinkList gouzao 1 null";
#endif
    m_head = NULL;
    m_length = 0;
}

template<typename T>
LinkList<T>::LinkList(const LinkList &list)
{
#if LINKLIST_CONS_DEBUG == 1
    qDebug() << "LinkList gouzao 2 copy";
#endif
    LinkListNode **p = &m_head;
    LinkListNode *tmp = list.m_head;
    while (tmp != NULL)
    {
        *p = new LinkListNode(tmp->data);
        p = &((*p)->next);
        tmp = tmp->next;
    }
    m_length = list.m_length;
}

template<typename T>
LinkList<T>::~LinkList()
{
#if LINKLIST_CONS_DEBUG == 1
    qDebug() << "LinkList ~";
#endif
    clear();
}

template<typename T>
LinkList<T> &LinkList<T>::operator=(const LinkList<T> &list)
{
#if LINKLIST_CONS_DEBUG == 1
    qDebug() << "LinkList fuzhi 1";
#endif
    clear();
    LinkListNode **p = &m_head;
    LinkListNode *tmp = list.m_head;
    while (tmp != NULL)
    {
        *p = new LinkListNode(tmp->data);
        p = &((*p)->next);
    }
    m_length = list.m_length;
}

template<typename T>
LinkList<T> &LinkList<T>::operator=(LinkList<T> &&list)
{
#if LINKLIST_CONS_DEBUG == 1
    qDebug() << "LinkList fuzhi 2 move";
#endif
    clear();
    m_head = list.m_head;
    m_length = list.m_length;
    list.m_head = NULL;
    list.m_length = 0;
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
    while (m_head != NULL)
    {
        tmp = m_head;
        m_head = m_head->next;
        delete tmp;
    }
    m_length = 0;
}

template<typename T>
const T &LinkList<T>::at(int i) const
{
    assert(i >= 0 && i < m_length);
    LinkListNode *tmp = m_head;
    for (int j = 0; j < i; j++)
        tmp = tmp->next;
    return tmp->data;
}

template<typename T>
T &LinkList<T>::operator[](int i)
{
    assert(i >= 0 && i < m_length);
    LinkListNode *tmp = m_head;
    for (int j = 0; j < i; j++)
        tmp = tmp->next;
    return tmp->data;
}

template<typename T>
void LinkList<T>::insert(int i, const T &t)
{
    if (i < 0 || i > m_length)
        return;
    LinkListNode *node = new LinkListNode(t);
    if (i == 0)
    {
        node->next = m_head;
        m_head = node;
    }
    else
    {
        LinkListNode *tmp = m_head;
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
    LinkListNode *node = new LinkListNode(t);
    if (m_head == NULL)
    {
        m_head = node;
    }
    else
    {
        LinkListNode *tmp = m_head;
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
    LinkListNode *tmp1 = m_head;
    if (i == 0)
    {
        m_head = tmp1->next;
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
    LinkListNode *tmp2 = m_head;
    int i = 0;
    while (tmp2 != NULL)
    {
        if (tmp2->data == t)
        {
            if (i == 0)
            {
                m_head = tmp2->next;
                delete tmp2;
                m_length--;
                tmp2 = m_head;
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
    LinkListNode *tmp = m_head;
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
    LinkListNode *tmp = m_head;
    for (int i = 0; i < m_length; i++)
    {
        info.append(QString::number(tmp->data) + " ");
        tmp = tmp->next;
    }
    return info;
}

#endif // LINKLIST_H
