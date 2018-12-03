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

    graph.DFSTraverse();
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
无向图最小生成树Prim（普里姆）算法
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
    while (veslist.getLength() > 0)
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
    graph.addVertexs(10);
    LinkList<ARC> list;
    list << ARC(0, 1) << ARC(0, 2) << ARC(0, 6) << ARC(0, 7) << ARC(6, 7) << ARC(1, 3) << ARC(2, 3) << ARC(5, 1) <<
        ARC(5, 9) << ARC(9, 3) << ARC(3, 4) << ARC(2, 4) << ARC(2, 8);
    graph.insertUArcs(list);
    AdjMGraph t;
    Prim(&graph, &t);
    t.print();
}

void Chapter6_Part1::practice_022(QString input, QString &result)
{
    Q_UNUSED(input);Q_UNUSED(result);




}
