#include "chapter6_part1.h"
#include "src/06_Graph/adjacencymatrixgraph.h"
#include "src/utils/tool.h"
#include "src/02_StackAndQueue/linkqueue.h"
#include "src/01_LinearList/seqlist.h"

/*
邻接矩阵demo
*/
void Chapter6_Part1::practice_000(QString input, QString &result)
{
    Q_UNUSED(input);Q_UNUSED(result);
    AdjMGraph graph;
    graph.addVertexs(10);
    LinkList<ARC> list;
    list << ARC(0, 1) << ARC(0, 2) << ARC(0, 6) << ARC(0, 7) << ARC(6, 7) << ARC(1, 3) << ARC(2, 3) << ARC(5, 1) <<
        ARC(5, 9) << ARC(9, 3) << ARC(3, 4) << ARC(2, 4);
    graph.insertUArcs(list);
//    DEBUG<<"--------------------";
//    graph.print();

    DEBUG<<"VerNum:"<<graph.getVerNum();
    DEBUG<<"ArcNum:"<<graph.getArcNum();

//    graph.BFSTraverse();
//    DEBUG<<"--------------------";

//    graph.DFSTraverse();

    DEBUG<<graph.isVertexConnected(0, 7);
    DEBUG<<graph.isVertexConnected(7, 6);
    DEBUG<<graph.isVertexConnected(6, 9);
    DEBUG<<graph.isVertexConnected(5, 4);
    DEBUG<<graph.isVertexConnected(1, 2);
    DEBUG<<graph.isVertexConnected(0, 8);
    DEBUG<<graph.isVertexConnected(2, 8);
    DEBUG<<graph.isVertexConnected(5, 8);
    DEBUG<<graph.isVertexConnected(0, 0);
    DEBUG<<"--------------------";

    DEBUG<<graph.isGraphConnected();
    graph.insertUArc(2, 8);
    DEBUG<<graph.isGraphConnected();
}

/*
非带权图 BFS算法求解单源最短路径
*/
int BFS_MIN_Distance(AdjMGraph *g, int v, int w)
{
    int capacity = g->getCapacity(), i;
    if (v >= capacity || v < 0 || w >= capacity || w < 0 || !g->isVertexExist(v) || !g->isVertexExist(w))
        return -1;
    if (v == w)
        return 0;
    int *arr = new int[capacity];
    unsigned char *visited = new unsigned char[capacity];
    for (i = 0; i < capacity; i++)
    {
        arr[i] = -1;
        visited[i] = 0;
    }
    LinkQueue<int> queue;
    visited[v] = 1;
    arr[v] = 0;
    queue.enqueue(v);
    while (queue.getSize() > 0)
    {
        v = queue.dequeue();
        for (i = g->firstAdjVex(v); i >= 0; i = g->nextAdjVex(v, i))
        {
            if (visited[i] == 0)
            {
                visited[i] = 1;
                arr[i] = arr[v] + 1;
                if (i == w)
                {
                    queue.clear();
                    break;
                }
                queue.enqueue(i);
            }
        }
    }
    int ret = arr[w];
    delete[] arr;
    delete[] visited;
    return ret;
}
void Chapter6_Part1::practice_020(QString input, QString &result)
{
    Q_UNUSED(input);Q_UNUSED(result);
    AdjMGraph graph;
    graph.addVertexs(10);
    LinkList<ARC> list;
    list << ARC(0, 1) << ARC(0, 2) << ARC(0, 6) << ARC(0, 7) << ARC(6, 7) << ARC(1, 3) << ARC(2, 3) << ARC(5, 1) <<
        ARC(5, 9) << ARC(9, 3) << ARC(3, 4) << ARC(2, 4);
    graph.insertUArcs(list);

    DEBUG<<BFS_MIN_Distance(&graph, 5, 7);
    DEBUG<<BFS_MIN_Distance(&graph, 0, 0);
    DEBUG<<BFS_MIN_Distance(&graph, 4, 7);
    DEBUG<<BFS_MIN_Distance(&graph, 8, 9);
    DEBUG<<BFS_MIN_Distance(&graph, 1, 2);
}

/*
无向连通图最小生成树 Prim（普里姆）算法
*/
void Prim(AdjMGraph *g, AdjMGraph *t)
{
    int i, j, v, w, value;
    SeqList<int> veslist;
    SeqList<int> newlist;
    for (i = 0; i < g->m_capacity; i++)//生成点集
    {
        if (g->m_vexs[i] != 0)
        {
            veslist.append(i);
        }
    }
    if (veslist.getLength() > 0)//添加一个点作为顶点
    {
        t->addVertexs(veslist.getLength());
        newlist.append(veslist.at(0));
        veslist.removeAt(0);
    }
    while (veslist.getLength() > 0)//从v属于newlist，w属于veslist，中选一条权值最小的边<v, w>加入图t，w加入newlist，veslist移除w
    {
        value = 0;
        for (i = 0; i < newlist.getLength(); i++)
        {
            for (j = 0; j < veslist.getLength(); j++)
            {
                if (g->isArcExist(newlist.at(i), veslist.at(j)))
                {
                    if (g->getValue(newlist.at(i), veslist.at(j)) < value || value == 0)
                    {
                        v = newlist.at(i), w = veslist.at(j);
                        value = g->getValue(newlist.at(i), veslist.at(j));
                    }
                }
            }
        }
        t->insertUArc(v, w, value);
        newlist.append(w);
        veslist.removeAll(w);
    }
}
void Chapter6_Part1::practice_021(QString input, QString &result)
{
    Q_UNUSED(input);Q_UNUSED(result);
    AdjMGraph graph;
    LinkList<ARC> list;
    graph.addVertexs(9);
    list << ARC(0, 1, 1) << ARC(0, 2, 10) << ARC(0, 6, 7) << ARC(0, 5, 6) << ARC(6, 5, 3) << ARC(1, 6, 4) <<
        ARC(1, 3, 2) << ARC(3, 2, 4) << ARC(7, 6, 10) << ARC(7, 1, 11) << ARC(5, 8, 4) << ARC(2, 8, 3) <<
        ARC(2, 5, 1) << ARC(6, 4, 7) << ARC(5, 4, 2);
    graph.insertUArcs(list);
    AdjMGraph t;
    Prim(&graph, &t);
    t.print();
}

/*
无向连通图最小生成树 Kruskal（克鲁斯卡尔）算法
*/
void Kruskal(AdjMGraph *g, AdjMGraph *t)
{
    int i, j, min;
    SeqList<ARC> list;
    t->addVertexs(g->getVerNum());
    for (i = 1; i < g->m_capacity; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (g->m_arc[i][j] > 0)
            {
                list.append(ARC(i, j, g->m_arc[i][j]));
            }
        }
    }
    while (!t->isGraphConnected() && list.getLength() > 0)
    {
        for (i = 1, min = 0; i < list.getLength(); i++)//选出最小权值的边
        {
            if (list.at(i).val < list.at(min).val)
            {
                min = i;
            }
        }
        if (!t->isVertexConnected(list.at(min).v, list.at(min).w))//两点不相通才插入
        {
            t->insertUArc(list.at(min).v, list.at(min).w, list.at(min).val);
        }
        list.removeAt(min);
    }
}
void Chapter6_Part1::practice_022(QString input, QString &result)
{
    Q_UNUSED(input);Q_UNUSED(result);
    AdjMGraph graph;
    LinkList<ARC> list;
    graph.addVertexs(9);
    list << ARC(0, 1, 1) << ARC(0, 2, 10) << ARC(0, 6, 7) << ARC(0, 5, 6) << ARC(6, 5, 3) << ARC(1, 6, 4) <<
        ARC(1, 3, 2) << ARC(3, 2, 4) << ARC(7, 6, 10) << ARC(7, 1, 11) << ARC(5, 8, 4) << ARC(2, 8, 3) <<
        ARC(2, 5, 1) << ARC(6, 4, 7) << ARC(5, 4, 2);
    graph.insertUArcs(list);
    AdjMGraph t;
    Kruskal(&graph, &t);
    t.print();
}