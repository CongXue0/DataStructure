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
        LinkStackNode()
        {
            prior = NULL;
            next = NULL;
        }
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
    T pop();
    QString print();

private:
    LinkStackNode *m_header;
    int m_size;

};

template <typename T>
LinkStack<T>::LinkStack()
{
    m_header = NULL;
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
        tmp = m_header;
        m_header = m_header->next;
        delete tmp;
    }
    m_header = NULL;
    m_size = 0;
}

template<typename T>
T &LinkStack<T>::top()
{
    assert(m_size > 0);
    return m_header->prior->data;
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
        m_header = node;
    }
    else
    {
        node->prior = m_header->prior;
        node->next = m_header;
        m_header->prior->next = node;
        m_header->prior = node;
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
        tmpData = m_header->data;
        delete m_header;
        m_header = NULL;
    }
    else
    {
        LinkStackNode *tmp = m_header->prior;
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
    LinkStackNode *tmp = m_header;
    for (int i = 0; i < m_size; i++)
    {
        info.append(QString::number(tmp->data) + " ");
        tmp = tmp->next;
    }
    return info;
}

#endif // LINKSTACK_H
