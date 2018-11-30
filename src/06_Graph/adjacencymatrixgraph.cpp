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
    if (v >= m_capacity || v < 0 || w >= m_capacity || v == w || w < 0)
        return false;
    return m_arc[v][w] > 0;
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
    if (v >= m_capacity || v < 0 || w >= m_capacity || v == w || w < 0)
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
            memcpy(arc[i], m_arc[i], len * sizeof(int));
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
                memcpy(arc[i], m_arc[i], len * sizeof(int));
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
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0 || v == w)
        return;
    if (value == 0)
        value = 1;
    if (m_arc[v][w] == 0)
    {
        m_arc[v][w] = value;
        m_arcNum++;
    }
}

void AdjacencyMatrixGraph::insertUArc(int v, int w, int value)
{
    if (v >= m_capacity || v < 0 || w >= m_capacity || w < 0 || v == w)
        return;
    if (value == 0)
        value = 1;
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
    for (int i = 0; i < m_capacity; i++)
    {
        QString line;
        for (int j = 0; j < m_capacity; j++)
            line.append(QString::number(m_arc[i][j]) + " ");
        DEBUG<<line;
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
