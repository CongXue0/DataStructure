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
    LinkQueueNode *m_head;
    int m_size;

};

template <typename T>
LinkQueue<T>::LinkQueue()
{
    m_head = NULL;
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
        tmp = m_head;
        m_head = m_head->next;
        delete tmp;
    }
    m_head = NULL;
    m_size = 0;
}

template <typename T>
T &LinkQueue<T>::head()
{
    assert(m_size > 0);
    return m_head->data;
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

template <typename T>
T LinkQueue<T>::dequeue()
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
        LinkQueueNode *tmp = m_head;
        m_head = m_head->next;
        m_head->prior = tmp->prior;
        tmp->prior->next = m_head;
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
    LinkQueueNode *tmp = m_head;
    for (int i = 0; i < m_size; i++)
    {
        info.append(QString::number(tmp->data) + " ");
        tmp = tmp->next;
    }
    return info;
}

#endif // LINKQUEUE_H
