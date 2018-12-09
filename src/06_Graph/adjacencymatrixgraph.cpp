#include "adjacencymatrixgraph.h"
#include <strings.h>
#include "src/02_StackAndQueue/linkqueue.h"
#include "src/utils/tool.h"

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int capacity)
{
    if (capacity < ADJMGRAPH_INIT_SIZE)
        capacity = ADJMGRAPH_INIT_SIZE;
    m_capacity = capacity;
    m_vexs = new unsigned char[m_capacity];
    m_arc = new int *[m_capacity];
    for (int i = 0; i < m_capacity; i++)
    {
        m_arc[i] = new int[m_capacity];
    }
    m_visited = new unsigned char[m_capacity];
    clear();
}

AdjacencyMatrixGraph::~AdjacencyMatrixGraph()
{
    delete[] m_vexs;
    for (int i = 0; i < m_capacity; i++)
    {
        delete[] m_arc[i];
    }
    delete[] m_arc;
    delete[] m_visited;
}

int AdjacencyMatrixGraph::getVerNum()
{
    return m_verNum;
}

int AdjacencyMatrixGraph::getArcNum()
{
    return m_arcNum;
}

int AdjacencyMatrixGraph::getCapacity()
{
    return m_capacity;
}

void AdjacencyMatrixGraph::clear()
{
    memset(m_vexs, 0x00, m_capacity * sizeof(unsigned char));
    for (int i = 0; i < m_capacity; i++)
    {
        memset(&m_arc[i][0], 0x00, m_capacity * sizeof(int));
    }
    m_verNum = 0;
    m_arcNum = 0;
}

bool AdjacencyMatrixGraph::isVertexExist(int v)
{
    if (v >= m_capacity || v < 0)
        return false;
    return m_vexs[v] > 0;
}

bool AdjacencyMatrixGraph::isArcExist(int v, int w)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0 || v == w)
        return false;
    return m_arc[v][w] > 0;
}

bool AdjacencyMatrixGraph::isVertexConnected(int v, int w)
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

bool AdjacencyMatrixGraph::isGraphConnected()
{
    if (m_verNum < 2)
        return false;
    SeqList<int> list;
    int i, j, num = 0, len;
    for (i = 0; i < m_capacity; i++)//选出一个起始顶点
    {
        if (m_vexs[i] > 0)
        {
            list.append(m_vexs[i]);
            num = 1;
            break;
        }
    }
    while (num > 0)//深度遍历
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

int AdjacencyMatrixGraph::firstAdjVex(int v)
{
    if (v >= m_capacity || v < 0)
        return -1;
    for (int i = 0; i < m_capacity; i++)
    {
        if (m_arc[v][i] > 0)
        {
            return i;
        }
    }
    return -1;
}

int AdjacencyMatrixGraph::nextAdjVex(int v, int w)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0 || v == w)
        return -1;
    for (int i = w + 1; i < m_capacity; i++)
    {
        if (m_arc[v][i] > 0)
        {
            return i;
        }
    }
    return -1;
}

int AdjacencyMatrixGraph::inDegree(int v)
{
    int num = 0;
    for (int i = 0; i < m_capacity; i++)
    {
        if (m_arc[i][v] > 0)
        {
            num++;
        }
    }
    return num;
}

int AdjacencyMatrixGraph::outDegree(int v)
{
    int num = 0;
    for (int i = 0; i < m_capacity; i++)
    {
        if (m_arc[v][i] > 0)
        {
            num++;
        }
    }
    return num;
}

int AdjacencyMatrixGraph::addVertex()
{
    int pos;
    for (pos = 0; pos < m_capacity; pos++)
    {
        if (m_vexs[pos] == 0)
            break;
    }
    if (pos >= m_capacity)//扩容
    {
        int len = m_capacity, i;
        m_capacity = m_capacity * 2;
        unsigned char *vexs = new unsigned char[m_capacity];
        memset(vexs, 0x00, m_capacity * sizeof(unsigned char));
        memcpy(vexs, m_vexs, len * sizeof(unsigned char));
        int **arc = new int *[m_capacity];
        for (i = 0; i < m_capacity; i++)
        {
            arc[i] = new int[m_capacity];
            memset(arc[i], 0x00, m_capacity * sizeof(int));
            if (i < len)
            {
                memcpy(arc[i], m_arc[i], len * sizeof(int));
            }
        }
        delete[] m_vexs;
        for (int i = 0; i < len; i++)
        {
            delete[] m_arc[i];
        }
        delete[] m_arc;
        delete[] m_visited;
        m_visited = new unsigned char[m_capacity];
        m_vexs = vexs;
        m_arc = arc;
    }
    m_vexs[pos] = 1;
    m_verNum++;
    return pos;
}

void AdjacencyMatrixGraph::addVertexs(int num)
{
    int pos = 0;
    for (int j = 0; j < num; j++)
    {
        for (; pos < m_capacity; pos++)
        {
            if (m_vexs[pos] == 0)
                break;
        }
        if (pos >= m_capacity)//扩容
        {
            int len = m_capacity, i;
            m_capacity = m_capacity * 2;
            unsigned char *vexs = new unsigned char[m_capacity];
            memset(vexs, 0x00, m_capacity * sizeof(unsigned char));
            memcpy(vexs, m_vexs, len * sizeof(unsigned char));
            int **arc = new int *[m_capacity];
            for (i = 0; i < m_capacity; i++)
            {
                arc[i] = new int[m_capacity];
                memset(arc[i], 0x00, m_capacity * sizeof(int));
                if (i < len)
                {
                    memcpy(arc[i], m_arc[i], len * sizeof(int));
                }
            }
            delete[] m_vexs;
            for (int i = 0; i < len; i++)
            {
                delete[] m_arc[i];
            }
            delete[] m_arc;
            delete[] m_visited;
            m_visited = new unsigned char[m_capacity];
            m_vexs = vexs;
            m_arc = arc;
        }
        m_vexs[pos] = 1;
        m_verNum++;
    }
}

void AdjacencyMatrixGraph::removeVertex(int v)
{
    if (v >= m_capacity || v < 0)
        return;
    if (m_vexs[v] > 0)
    {
        m_vexs[v] = 0;
        m_verNum--;
    }
    for (int i = 0; i < m_capacity; i++)
    {
        if (m_arc[i][v] > 0)
        {
            m_arc[i][v] = 0;
            m_arcNum--;
        }
        if (m_arc[v][i] > 0)
        {
            m_arc[v][i] = 0;
            m_arcNum--;
        }
    }
}

void AdjacencyMatrixGraph::insertDArc(int v, int w, int value)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0 || v == w || value < 1)
        return;
    if (m_arc[v][w] == 0)
    {
        m_arc[v][w] = value;
        m_arcNum++;
    }
}

void AdjacencyMatrixGraph::insertUArc(int v, int w, int value)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0 || v == w || value < 1)
        return;
    if (m_arc[v][w] == 0)
    {
        m_arc[v][w] = value;
        m_arcNum++;
    }
    if (m_arc[w][v] == 0)
    {
        m_arc[w][v] = value;
        m_arcNum++;
    }
}

void AdjacencyMatrixGraph::insertDArcs(LinkList<ARC> &arcList)
{
    LinkList<ARC>::LinkListNode *header = arcList.m_header;
    while (header != NULL)
    {
        if (m_arc[header->data.v][header->data.w] == 0)
        {
            m_arc[header->data.v][header->data.w] = header->data.val;
            m_arcNum++;
        }
        header = header->next;
    }
}

void AdjacencyMatrixGraph::insertUArcs(LinkList<ARC> &arcList)
{
    LinkList<ARC>::LinkListNode *header = arcList.m_header;
    while (header != NULL)
    {
        if (m_arc[header->data.v][header->data.w] == 0)
        {
            m_arc[header->data.v][header->data.w] = header->data.val;
            m_arcNum++;
        }
        if (m_arc[header->data.w][header->data.v] == 0)
        {
            m_arc[header->data.w][header->data.v] = header->data.val;
            m_arcNum++;
        }
        header = header->next;
    }
}

void AdjacencyMatrixGraph::removeDArc(int v, int w)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0)
        return;
    if (m_arc[v][w] > 0)
    {
        m_arc[v][w] = 0;
        m_arcNum--;
    }
}

void AdjacencyMatrixGraph::removeUArc(int v, int w)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0)
        return;
    if (m_arc[v][w] > 0)
    {
        m_arc[v][w] = 0;
        m_arcNum--;
    }
    if (m_arc[w][v] > 0)
    {
        m_arc[w][v] = 0;
        m_arcNum--;
    }
}

void AdjacencyMatrixGraph::setValue(int v, int w, int value)
{
    if (isArcExist(v, w) && value > 0)
    {
        m_arc[v][w] = value;
    }
}

int AdjacencyMatrixGraph::getValue(int v, int w)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0)
        return 0;
    return m_arc[v][w];
}

void AdjacencyMatrixGraph::BFSTraverse()
{
    memset(m_visited, 0x00, m_capacity * sizeof(unsigned char));
    for (int i = 0; i < m_capacity; i++)
    {
        if (m_vexs[i] > 0 && m_visited[i] == 0)
        {
            BFS(this, i);
        }
    }
}

void AdjacencyMatrixGraph::DFSTraverse()
{
    memset(m_visited, 0x00, m_capacity * sizeof(unsigned char));
    for (int i = 0; i < m_capacity; i++)
    {
        if (m_vexs[i] > 0 && m_visited[i] == 0)
        {
            DFS(this, i);
        }
    }
}

void AdjacencyMatrixGraph::print()
{
    QString line1;
    for (int i = 0; i < m_capacity; i++)
    {
        line1.append(QString::number(m_vexs[i]) + " ");
    }
    DEBUG<<line1;
    for (int i = 0; i < m_capacity; i++)
    {
        QString line2;
        for (int j = 0; j < m_capacity; j++)
            line2.append(QString::number(m_arc[i][j]) + " ");
        DEBUG<<line2;
    }

}

void AdjacencyMatrixGraph::BFS(AdjacencyMatrixGraph *g, int v)
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

void AdjacencyMatrixGraph::DFS(AdjacencyMatrixGraph *g, int v)
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
