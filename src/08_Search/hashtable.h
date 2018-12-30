#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <assert.h>
#include <QString>
#include <string.h>
#include "src/02_StackAndQueue/seqqueue.h"
#include "src/utils/tool.h"

#define HASHTABLE_INIT_SIZE 41

class HashCalc
{
public:
    HashCalc() = delete;
    inline static unsigned int hash(unsigned char key) { return (unsigned int)(key); }
    inline static unsigned int hash(char key) { return (unsigned int)(key); }
    inline static unsigned int hash(unsigned short key) { return (unsigned int)(key); }
    inline static unsigned int hash(short key) { return (unsigned int)(key); }
    inline static unsigned int hash(unsigned int key) { return (unsigned int)(key); }
    inline static unsigned int hash(int key) { return (unsigned int)(key); }
    inline static unsigned int hash(unsigned long key) { return (unsigned int)(key); }
    inline static unsigned int hash(long key) { return (unsigned int)(key); }
    inline static unsigned int hash(unsigned long long key)
    {
        if (sizeof(unsigned long long) > sizeof(unsigned int))
        {
            return (unsigned int)(((key >> (8 * sizeof(unsigned int) - 1)) ^ key) & (~0U));
        }
        else
        {
            return (unsigned int)(key & (~0U));
        }
    }
    inline static unsigned int hash(long long key) { return hash((unsigned long long)(key)); }
    inline static unsigned int hash(const char *key)
    {
        unsigned int ret;
        int len = strlen(key);
        if (len == 0)
            return 0;
        ret = (unsigned int)(key[0]);
        for (int i = 1; i < len; i++)
        {
            ret = (unsigned int)(ret * key[i]);
        }
        return ret;
    }
    inline static unsigned int hash(char *key) { return hash((const char *)(key)); }

};

template <typename Key, typename T>
class HashTable
{
public:
    class HashTableNode
    {
    public:
        HashTableNode() : next(NULL) {}
        HashTableNode(const Key &_key, const T &_data) : key(_key), data(_data), next(NULL) {}
        Key key;
        T data;
        HashTableNode *next;//key冲突时，存放在下一个结点
    };
    HashTable();
    ~HashTable();
    int getSize();//获取元素个数
    int getCapacity();//获取哈希表容量
    void clear();//清空所有元素
    const T &value(const Key &key) const;//根据key键查找对应的值
    T &operator[](const Key &key);
    void insert(const Key &key, const T &t);//插入键值对
    void remove(const Key &key);//移除键
    bool contains(const Key &key);//判断键存不存在
    void print();//打印整个哈希表

public:
    HashTableNode **m_elem;
    int m_size;
    int m_capacity;
};

template <typename Key, typename T>
HashTable<Key, T>::HashTable()
{
    m_size = 0;
    m_capacity = HASHTABLE_INIT_SIZE;
    m_elem = new HashTableNode *[m_capacity];
    for (int i = 0; i < m_capacity; i++)
        m_elem[i] = NULL;
}

template <typename Key, typename T>
HashTable<Key, T>::~HashTable()
{
    clear();
    delete m_elem;
}

template <typename Key, typename T>
int HashTable<Key, T>::getSize()
{
    return m_size;
}

template <typename Key, typename T>
int HashTable<Key, T>::getCapacity()
{
    return m_capacity;
}

template <typename Key, typename T>
void HashTable<Key, T>::clear()
{
    int i;
    HashTableNode *tmp;
    for (i = 0; i < m_capacity; i++)
    {
        while (m_elem[i] != NULL)
        {
            tmp = m_elem[i];
            m_elem[i] = m_elem[i]->next;
            delete tmp;
        }
    }
    m_size = 0;
}

template <typename Key, typename T>
const T &HashTable<Key, T>::value(const Key &key) const
{
    unsigned int index = HashCalc::hash(key) % m_capacity;
    HashTableNode *tmp = m_elem[index];
    while (tmp != NULL)
    {
        if (tmp->key == key)
            return tmp->data;
        tmp = tmp->next;
    }
    assert(tmp != NULL);
}

template <typename Key, typename T>
T &HashTable<Key, T>::operator[](const Key &key)
{
    unsigned int index = HashCalc::hash(key) % m_capacity;
    HashTableNode *tmp = m_elem[index];
    while (tmp != NULL)
    {
        if (tmp->key == key)
            return tmp->data;
        tmp = tmp->next;
    }
    assert(tmp != NULL);
}

template <typename Key, typename T>
void HashTable<Key, T>::insert(const Key &key, const T &t)
{
    if (m_size >= m_capacity)//扩容
    {
        unsigned int h;
        int capacity = m_capacity, i;
        m_capacity = m_capacity * 2 + 1;
        SeqQueue<HashTableNode *> queue;//用于暂存所有结点的队列
        HashTableNode *tmp, *tmp2;
        for (i = 0; i < capacity; i++)//将所有结点存入队列
        {
            tmp = m_elem[i];
            while (tmp != NULL)
            {
                queue.enqueue(tmp);
                tmp = tmp->next;
            }
        }
        delete m_elem;
        m_elem = new HashTableNode *[m_capacity];
        for (i = 0; i < m_capacity; i++)
            m_elem[i] = NULL;
        while (queue.getSize() > 0)//重新连接所有结点
        {
            tmp = queue.dequeue();
            h = HashCalc::hash(tmp->key) % m_capacity;
            if (m_elem[h] == NULL)
            {
                m_elem[h] = tmp;
                tmp->next = NULL;
            }
            else
            {
                tmp2 = m_elem[h];
                while (tmp2->next != NULL)
                    tmp2 = tmp2->next;
                tmp2->next = tmp;
                tmp->next = NULL;
            }
        }
    }
    unsigned int index = HashCalc::hash(key) % m_capacity;
    if (m_elem[index] == NULL)
    {
        m_elem[index] = new HashTableNode(key, t);
    }
    else
    {
        HashTableNode *tmp = m_elem[index];
        while (tmp->next != NULL)
        {
            if (tmp->key == key)
                break;
            tmp = tmp->next;
        }
        if (tmp->next == NULL)
        {
            tmp->next = new HashTableNode(key, t);
        }
        else
        {
            tmp->data = t;
        }
    }
    m_size++;
}

template <typename Key, typename T>
void HashTable<Key, T>::remove(const Key &key)
{
    unsigned int index = HashCalc::hash(key) % m_capacity;
    HashTableNode *tmp = m_elem[index];
    if (tmp == NULL)
        return;
    if (tmp->key == key)
    {
        m_elem[index] = tmp->next;
        delete tmp;
        m_size--;
    }
    else
    {
        while (tmp->next != NULL)
        {
            if (tmp->next->key == key)
                break;
            tmp = tmp->next;
        }
        if (tmp->next != NULL)
        {
            HashTableNode *tmp2 = tmp;
            tmp->next = tmp->next->next;
            delete tmp2;
            m_size--;
        }
    }
}

template <typename Key, typename T>
bool HashTable<Key, T>::contains(const Key &key)
{
    unsigned int index = HashCalc::hash(key) % m_capacity;
    HashTableNode *tmp = m_elem[index];
    while (tmp != NULL)
    {
        if (tmp->key == key)
            return true;
        tmp = tmp->next;
    }
    return false;
}

template <typename Key, typename T>
void HashTable<Key, T>::print()
{
    QString info;
    HashTableNode *tmp;
    for (int i = 0; i < m_capacity; i++)
    {
        tmp = m_elem[i];
        if (tmp == NULL)
        {
            DEBUG<<QString("i:%1 NULL").arg(i);
        }
        else
        {
            info.clear();
            while (tmp != NULL)
            {
                info.append(QString("(%1, %2), ").arg(tmp->key).arg(tmp->data));
                tmp = tmp->next;
            }
            DEBUG<<QString("i:%1 ").arg(i)<<info;
        }
    }
}

#endif // HASHTABLE_H
