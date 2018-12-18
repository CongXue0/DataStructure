#include "adjacencylistgraph.h"
#include <strings.h>
#include "src/02_StackAndQueue/linkqueue.h"
#include "src/utils/tool.h"

AdjacencyListGraph::AdjacencyListGraph(int capacity)
{
    if (capacity < GRAPH_INIT_SIZE)
        capacity = GRAPH_INIT_SIZE;
    m_capacity = capacity;
    m_adjList = new VNode[m_capacity];
    for (int i = 0; i < m_capacity; i++)
    {
        m_adjList[i].en = 0;
    }
    m_visited = new unsigned char[m_capacity];
    m_verNum = 0;
    m_arcNum = 0;
}

AdjacencyListGraph::~AdjacencyListGraph()
{
    delete[] m_adjList;
    delete[] m_visited;
}

int AdjacencyListGraph::getVerNum()
{
    return m_verNum;
}

int AdjacencyListGraph::getArcNum()
{
    return m_arcNum;
}

int AdjacencyListGraph::getCapacity()
{
    return m_capacity;
}

void AdjacencyListGraph::clear()
{
    ArcNode *tmp;
    for (int i = 0; i < m_capacity; i++)
    {
        if (m_adjList[i].en == 1)
        {
            m_adjList[i].en = 0;
            while (m_adjList[i].first != NULL)
            {
                tmp = m_adjList[i].first;
                m_adjList[i].first = m_adjList[i].first->next;
                delete tmp;
            }
        }
    }
    m_verNum = 0;
    m_arcNum = 0;
}

bool AdjacencyListGraph::isVertexExist(int v)
{
    if (v >= m_capacity || v < 0)
        return false;
    return m_adjList[v].en == 1;
}

bool AdjacencyListGraph::isArcExist(int v, int w)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0 || v == w)
        return false;
    ArcNode *tmp = m_adjList[v].first;
    while (tmp != NULL)
    {
        if (tmp->vex == w)
            return true;
        tmp = tmp->next;
    }
    return false;
}

bool AdjacencyListGraph::isVertexConnected(int v, int w)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0 || v == w || !isVertexExist(v) || !isVertexExist(w))
        return false;
    SeqList<int> list;
    list.append(v);
    int i, j, num = 1, len;
    while (num > 0)//深度遍历
    {
        len = list.getLength();
        i = len - num;
        num = 0;
        for (; i < len; i++)
        {
            for (j = firstAdjVex(list.at(i)); j >= 0; j = nextAdjVex(list.at(i), j))
            {
                if (j == w)//剪枝
                    return true;
                if (!list.contains(j))
                {
                    list.append(j);
                    num++;
                }
            }
        }
    }
    return false;
}

bool AdjacencyListGraph::isGraphConnected()
{
    if (m_verNum < 2)
        return false;
    SeqList<int> list;
    int i, j, num = 0, len;
    for (i = 0; i < m_capacity; i++)//选出一个起始顶点
    {
        if (m_adjList[i].en == 1)
        {
            list.append(i);
            num = 1;
            break;
        }
    }
    while (num > 0)//广度遍历，每一层的顶点加入list
    {
        len = list.getLength();
        i = len - num;
        num = 0;
        for (; i < len; i++)
        {
            for (j = firstAdjVex(list.at(i)); j >= 0; j = nextAdjVex(list.at(i), j))
            {
                if (!list.contains(j))
                {
                    list.append(j);
                    num++;
                }
            }
        }
    }
    return list.getLength() == m_verNum;
}

int AdjacencyListGraph::firstAdjVex(int v)
{
    if (v >= m_capacity || v < 0 || m_adjList[v].first == NULL)
        return -1;
    return m_adjList[v].first->vex;
}

int AdjacencyListGraph::nextAdjVex(int v, int w)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0 || v == w)
        return -1;
    ArcNode *tmp = m_adjList[v].first;
    while (tmp != NULL)
    {
        if (tmp->vex == w)
        {
            tmp = tmp->next;
            return (tmp != NULL ? tmp->vex : -1);
        }
        tmp = tmp->next;
    }
    return -1;
}

int AdjacencyListGraph::inDegree(int v)
{
    if (v >= m_capacity || v < 0)
        return 0;
    int num = 0;
    ArcNode *tmp;
    for (int i = 0; i < m_capacity; i++)
    {
        if (i != v)
        {
            tmp = m_adjList[i].first;
            while (tmp != NULL)
            {
                if (tmp->vex == v)
                {
                    num++;
                    break;
                }
                tmp = tmp->next;
            }
        }
    }
    return num;
}

int AdjacencyListGraph::outDegree(int v)
{
    if (v >= m_capacity || v < 0)
        return 0;
    int num = 0;
    ArcNode *tmp = m_adjList[v].first;
    while (tmp != NULL)
    {
        num++;
        tmp = tmp->next;
    }
    return num;
}

int AdjacencyListGraph::addVertex()
{
    int pos;
    for (pos = 0; pos < m_capacity; pos++)
    {
        if (m_adjList[pos].en == 0)
            break;
    }
    if (pos >= m_capacity)//扩容
    {
        int len = m_capacity, i;
        m_capacity = m_capacity * 2;
        VNode *adjList = new VNode[m_capacity];
        for (i = 0; i < m_capacity; i++)
        {
            if (i < len)
            {
                adjList[i].en = m_adjList[i].en;
                adjList[i].first = m_adjList[i].first;
            }
            else
            {
                adjList[i].en = 0;
            }
        }
        delete[] m_adjList;
        delete[] m_visited;
        m_visited = new unsigned char[m_capacity];
        m_adjList = adjList;
    }
    m_adjList[pos].en = 1;
    m_verNum++;
    return pos;
}

void AdjacencyListGraph::addVertexs(int num)
{
    int pos = 0;
    for (int j = 0; j < num; j++)
    {
        for (; pos < m_capacity; pos++)
        {
            if (m_adjList[pos].en == 0)
                break;
        }
        if (pos >= m_capacity)//扩容
        {
            int len = m_capacity, i;
            m_capacity = m_capacity * 2;
            VNode *adjList = new VNode[m_capacity];
            for (i = 0; i < m_capacity; i++)
            {
                if (i < len)
                {
                    adjList[i].en = m_adjList[i].en;
                    adjList[i].first = m_adjList[i].first;
                }
                else
                {
                    adjList[i].en = 0;
                }
            }
            delete[] m_adjList;
            delete[] m_visited;
            m_visited = new unsigned char[m_capacity];
            m_adjList = adjList;
        }
        m_adjList[pos].en = 1;
        m_verNum++;
    }
}

void AdjacencyListGraph::removeVertex(int v)
{
    if (v >= m_capacity || v < 0)
        return;
    if (m_adjList[v].en == 1)
    {
        m_adjList[v].en = 0;
        m_verNum--;
        ArcNode *tmp;
        while (m_adjList[v].first != NULL)//删除由v出去的边
        {
            tmp = m_adjList[v].first;
            m_adjList[v].first = m_adjList[v].first->next;
            delete tmp;
            m_arcNum--;
        }
        for (int i = 0; i < m_capacity; i++)//删除由v进来的边
        {
            if (m_adjList[i].first != NULL)
            {
                if (m_adjList[i].first->vex == v)
                {
                    tmp = m_adjList[i].first;
                    m_adjList[i].first = m_adjList[i].first->next;
                    delete tmp;
                    m_arcNum--;
                }
                else
                {
                    ArcNode *tmp2 = m_adjList[i].first;
                    tmp = tmp2->next;
                    while (tmp != NULL)
                    {
                        if (tmp->vex == v)
                        {
                            tmp2->next = tmp->next;
                            delete tmp;
                            m_arcNum--;
                            break;
                        }
                        tmp2 = tmp;
                        tmp = tmp->next;
                    }
                }
            }
        }
    }
}

void AdjacencyListGraph::insertDArc(int v, int w, int value)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0 || v == w || value < 1)
        return;
    if (m_adjList[v].first == NULL)
    {
        m_adjList[v].first = new ArcNode(w, value);
        m_arcNum++;
        return;
    }
    ArcNode **last = &m_adjList[v].first;
    while (*last != NULL)
    {
        if ((*last)->vex == w)
        {
            last = NULL;
            break;
        }
        last = &(*last)->next;
    }
    if (last != NULL)
    {
        *last = new ArcNode(w, value);
        m_arcNum++;
    }
}

void AdjacencyListGraph::insertUArc(int v, int w, int value)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0 || v == w || value < 1)
        return;
    ArcNode **last1 = &m_adjList[v].first;
    ArcNode **last2 = &m_adjList[w].first;
    while (*last1 != NULL)
    {
        if ((*last1)->vex == w)
        {
            last1 = NULL;
            break;
        }
        last1 = &(*last1)->next;
    }
    while (*last2 != NULL)
    {
        if ((*last2)->vex == v)
        {
            last2 = NULL;
            break;
        }
        last2 = &(*last2)->next;
    }
    if (last1 != NULL && last2 != NULL)
    {
        *last1 = new ArcNode(w, value);
        *last2 = new ArcNode(v, value);
        m_arcNum += 2;
    }
}

void AdjacencyListGraph::insertDArcs(LinkList<ARC> &arcList)
{
    LinkList<ARC>::LinkListNode *head = arcList.m_head;
    while (head != NULL)
    {
        insertDArc(head->data.v, head->data.w, head->data.val);
        head = head->next;
    }
}

void AdjacencyListGraph::insertUArcs(LinkList<ARC> &arcList)
{
    LinkList<ARC>::LinkListNode *head = arcList.m_head;
    while (head != NULL)
    {
        insertUArc(head->data.v, head->data.w, head->data.val);
        head = head->next;
    }
}

void AdjacencyListGraph::removeDArc(int v, int w)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0)
        return;
    ArcNode *tmp, *tmp2;
    if (m_adjList[v].first != NULL)
    {
        if (m_adjList[v].first->vex == w)
        {
            tmp = m_adjList[v].first;
            m_adjList[v].first = m_adjList[v].first->next;
            delete tmp;
            m_arcNum--;
        }
        else
        {
            tmp2 = m_adjList[v].first;
            tmp = tmp2->next;
            while (tmp != NULL)
            {
                if (tmp->vex == w)
                {
                    tmp2->next = tmp->next;
                    delete tmp;
                    m_arcNum--;
                    break;
                }
                tmp2 = tmp;
                tmp = tmp->next;
            }
        }
    }
}

void AdjacencyListGraph::removeUArc(int v, int w)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0)
        return;
    ArcNode *tmp, *tmp2;
    if (m_adjList[v].first != NULL)
    {
        if (m_adjList[v].first->vex == w)
        {
            tmp = m_adjList[v].first;
            m_adjList[v].first = m_adjList[v].first->next;
            delete tmp;
            m_arcNum--;
        }
        else
        {
            tmp2 = m_adjList[v].first;
            tmp = tmp2->next;
            while (tmp != NULL)
            {
                if (tmp->vex == w)
                {
                    tmp2->next = tmp->next;
                    delete tmp;
                    m_arcNum--;
                    break;
                }
                tmp2 = tmp;
                tmp = tmp->next;
            }
        }
    }
    if (m_adjList[w].first != NULL)
    {
        if (m_adjList[w].first->vex == v)
        {
            tmp = m_adjList[w].first;
            m_adjList[v].first = m_adjList[w].first->next;
            delete tmp;
            m_arcNum--;
        }
        else
        {
            tmp2 = m_adjList[w].first;
            tmp = tmp2->next;
            while (tmp != NULL)
            {
                if (tmp->vex == v)
                {
                    tmp2->next = tmp->next;
                    delete tmp;
                    m_arcNum--;
                    break;
                }
                tmp2 = tmp;
                tmp = tmp->next;
            }
        }
    }
}

void AdjacencyListGraph::setValue(int v, int w, int value)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0 || v == w || value < 1)
        return;
    ArcNode *tmp = m_adjList[v].first;
    while (tmp != NULL)
    {
        if (tmp->vex == w)
        {
            tmp->val = value;
            break;
        }
        tmp = tmp->next;
    }
}

int AdjacencyListGraph::getValue(int v, int w)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0 || v == w)
        return 0;
    ArcNode *tmp = m_adjList[v].first;
    while (tmp != NULL)
    {
        if (tmp->vex == w)
        {
            return tmp->val;
        }
        tmp = tmp->next;
    }
    return 0;
}

void AdjacencyListGraph::BFSTraverse()
{
    memset(m_visited, 0x00, m_capacity * sizeof(unsigned char));
    for (int i = 0; i < m_capacity; i++)
    {
        if (m_adjList[i].en == 1 && m_visited[i] == 0)
        {
            BFS(this, i);
        }
    }
}

void AdjacencyListGraph::DFSTraverse()
{
    memset(m_visited, 0x00, m_capacity * sizeof(unsigned char));
    for (int i = 0; i < m_capacity; i++)
    {
        if (m_adjList[i].en == 1 && m_visited[i] == 0)
        {
            DFS(this, i);
        }
    }
}

void AdjacencyListGraph::print()
{
    QString line1 = "adj: ";
    for (int i = 0; i < m_capacity; i++)
    {
        line1.append(QString::number(m_adjList[i].en) + " ");
    }
    DEBUG<<line1;
    ArcNode *tmp;
    for (int i = 0; i < m_capacity; i++)
    {
        if (m_adjList[i].en == 1)
        {
            QString line2 = "v" + QString::number(i) + ": ";
            tmp = m_adjList[i].first;
            while (tmp != NULL)
            {
                line2.append(QString("(%1, %2), ").arg(tmp->vex).arg(tmp->val));
                tmp = tmp->next;
            }
            DEBUG<<line2;
        }
    }
}

void AdjacencyListGraph::BFS(AdjacencyListGraph *g, int v)
{
    int w;
    LinkQueue<int> queue;
    DEBUG << v << " ";
    g->m_visited[v] = 1;
    queue.enqueue(v);
    while (queue.getSize() > 0)
    {
        v = queue.dequeue();
        for (w = g->firstAdjVex(v); w >= 0; w = g->nextAdjVex(v, w))
        {
            if (g->m_visited[w] == 0)
            {
                DEBUG << w << " ";
                g->m_visited[w] = 1;
                queue.enqueue(w);
            }
        }
    }
}

void AdjacencyListGraph::DFS(AdjacencyListGraph *g, int v)
{
    int w;
    DEBUG << v << " ";
    g->m_visited[v] = 1;
    for (w = g->firstAdjVex(v); w >= 0; w = g->nextAdjVex(v, w))
    {
        if (g->m_visited[w] == 0)
        {
            DFS(g, w);
        }
    }
}
