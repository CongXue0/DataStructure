#ifndef LINKSTACK_H
#define LINKSTACK_H

#include <assert.h>
#include <QString>

template <typename T>
class LinkStack
{
public:
    class LinkStackNode
    {
    public:
        LinkStackNode() : prior(NULL), next(NULL) {}
        LinkStackNode(const T &_data) : data(_data) , prior(NULL), next(NULL) {}
        T data;
        LinkStackNode *prior;
        LinkStackNode *next;
    };
    LinkStack();
    ~LinkStack();
    int getSize();
    void clear();
    T &top();
    void push(const T &t);
    void insert(int i, const T &t);
    T pop();
    QString print();

public:
    LinkStackNode *m_head;
    int m_size;

};

template <typename T>
LinkStack<T>::LinkStack()
{
    m_head = NULL;
    m_size = 0;
}

template <typename T>
LinkStack<T>::~LinkStack()
{
    clear();
}

template<typename T>
int LinkStack<T>::getSize()
{
    return m_size;
}

template<typename T>
void LinkStack<T>::clear()
{
    LinkStackNode *tmp;
    for (int i = 0; i < m_size; i++)
    {
        tmp = m_head;
        m_head = m_head->next;
        delete tmp;
    }
    m_head = NULL;
    m_size = 0;
}

template<typename T>
T &LinkStack<T>::top()
{
    assert(m_size > 0);
    return m_head->prior->data;
}

template<typename T>
void LinkStack<T>::push(const T &t)
{
    LinkStackNode *node = new LinkStackNode();
    node->data = t;
    if (m_size == 0)
    {
        node->prior = node;
        node->next = node;
        m_head = node;
    }
    else
    {
        node->prior = m_head->prior;
        node->next = m_head;
        m_head->prior->next = node;
        m_head->prior = node;
    }
    m_size++;
}

template<typename T>
void LinkStack<T>::insert(int i, const T &t)
{
    if (i < 0 || i > m_size)
        return;
    LinkStackNode *node = new LinkStackNode(t);
    if (m_size == 0)
    {
        node->prior = node;
        node->next = node;
        m_head = node;
    }
    else
    {
        LinkStackNode *tmp = m_head;
        for (int j = 0; j < i; j++)//找到插入位置
            tmp = tmp->next;
        node->prior = tmp->prior;
        node->next = tmp;
        tmp->prior->next = node;
        tmp->prior = node;
    }
    m_size++;
}

template<typename T>
T LinkStack<T>::pop()
{
    assert(m_size > 0);
    T tmpData;
    if (m_size == 1)
    {
        tmpData = m_head->data;
        delete m_head;
        m_head = NULL;
    }
    else
    {
        LinkStackNode *tmp = m_head->prior;
        tmp->prior->next = tmp->next;
        tmp->next->prior = tmp->prior;
        tmpData = tmp->data;
        delete tmp;
    }
    m_size--;
    return tmpData;
}

template<typename T>
QString LinkStack<T>::print()
{
    QString info;
    LinkStackNode *tmp = m_head;
    for (int i = 0; i < m_size; i++)
    {
        info.append(QString::number(tmp->data) + " ");
        tmp = tmp->next;
    }
    return info;
}

#endif // LINKSTACK_H
