#include "chapter6_part1.h"
#include "src/06_Graph/adjacencymatrixgraph.h"
#include "src/utils/tool.h"
#include "src/02_StackAndQueue/linkqueue.h"

/*
邻接矩阵demo
*/
void Chapter6_Part1::practice_000(QString input, QString &result)
{
    Q_UNUSED(input);Q_UNUSED(result);
    AdjMGraph graph;
    graph.addVertexs(10);
    graph.insertUArc(0, 1);
    graph.insertUArc(0, 2);
    graph.insertUArc(0, 6);
    graph.insertUArc(0, 7);
    graph.insertUArc(6, 7);
    graph.insertUArc(1, 3);
    graph.insertUArc(2, 3);
    graph.insertUArc(5, 1);
    graph.insertUArc(5, 9);
    graph.insertUArc(9, 3);
    graph.insertUArc(3, 4);
    graph.insertUArc(2, 4);
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
    graph.insertUArc(0, 1);
    graph.insertUArc(0, 2);
    graph.insertUArc(0, 6);
    graph.insertUArc(0, 7);
    graph.insertUArc(6, 7);
    graph.insertUArc(1, 3);
    graph.insertUArc(2, 3);
    graph.insertUArc(5, 1);
    graph.insertUArc(5, 9);
    graph.insertUArc(9, 3);
    graph.insertUArc(3, 4);
    graph.insertUArc(2, 4);

    DEBUG<<BFS_MIN_Distance(&graph, 5, 7);
    DEBUG<<BFS_MIN_Distance(&graph, 0, 0);
    DEBUG<<BFS_MIN_Distance(&graph, 4, 7);
    DEBUG<<BFS_MIN_Distance(&graph, 8, 9);
    DEBUG<<BFS_MIN_Distance(&graph, 1, 2);
}

void Chapter6_Part1::practice_021(QString input, QString &result)
{

}

void Chapter6_Part1::practice_022(QString input, QString &result)
{

}
