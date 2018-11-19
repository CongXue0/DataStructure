#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include <assert.h>
#include <QString>

template <typename T>
class LinkQueue
{
public:
    class LinkQueueNode
    {
    public:
        LinkQueueNode()
        {
            prior = NULL;
            next = NULL;
        }
        T data;
        LinkQueueNode *prior;
        LinkQueueNode *next;
    };
    LinkQueue();
    ~LinkQueue();
    int getSize();
    void clear();
    T &head();
    void enqueue(const T &t);
    T dequeue();
    QString print();

private:
    LinkQueueNode *m_header;
    int m_size;

};

template <typename T>
LinkQueue<T>::LinkQueue()
{
    m_header = NULL;
    m_size = 0;
}

template <typename T>
LinkQueue<T>::~LinkQueue()
{
    clear();
}

template <typename T>
int LinkQueue<T>::getSize()
{
    return m_size;
}

template <typename T>
void LinkQueue<T>::clear()
{
    LinkQueueNode *tmp;
    for (int i = 0; i < m_size; i++)
    {
        tmp = m_header;
        m_header = m_header->next;
        delete tmp;
    }
    m_header = NULL;
    m_size = 0;
}

template <typename T>
T &LinkQueue<T>::head()
{
    assert(m_size > 0);
    return m_header->data;
}

template <typename T>
void LinkQueue<T>::enqueue(const T &t)
{
    LinkQueueNode *node = new LinkQueueNode();
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

template <typename T>
T LinkQueue<T>::dequeue()
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
        LinkQueueNode *tmp = m_header;
        m_header = m_header->next;
        m_header->prior = tmp->prior;
        tmp->prior->next = m_header;
        tmpData = tmp->data;
        delete tmp;
    }
    m_size--;
    return tmpData;
}

template <typename T>
QString LinkQueue<T>::print()
{
    QString info;
    LinkQueueNode *tmp = m_header;
    for (int i = 0; i < m_size; i++)
    {
        info.append(QString::number(tmp->data) + " ");
        tmp = tmp->next;
    }
    return info;
}

#endif // LINKQUEUE_H
