#include "chapter6_part1.h"
#include "src/06_Graph/adjacencymatrixgraph.h"
#include "src/utils/tool.h"
#include "src/02_StackAndQueue/linkqueue.h"
#include "src/01_LinearList/seqlist.h"
#include "src/utils/virtualio.h"
#include "src/02_StackAndQueue/seqstack.h"
#include "src/02_StackAndQueue/seqqueue.h"

/*
邻接矩阵demo
*/
void Chapter6_Part1::practice_000()
{
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
void Chapter6_Part1::practice_020()
{
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
        if (g->m_vexs[i] > 0)
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
void Chapter6_Part1::practice_021()
{
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
    for (i = 1; i < g->getCapacity(); i++)
    {
        for (j = 0; j < i; j++)
        {
            if (g->getValue(i, j) > 0)
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
void Chapter6_Part1::practice_022()
{
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

/*
单源最短路径 Dijkstra算法
*/
void Dijkstra(AdjMGraph *g, int v, int w, LinkList<int> &ret)
{
    int i, min, tmp;
    SeqList<int> vlist;
    int *dist, *path;
    dist = new int[g->getVerNum()];//记录从v出发到其他各顶点的最短路径长度
    path = new int[g->getVerNum()];//path[i] 记录v到i最短路径上的倒数第二个顶点
    for (i = 0; i < g->getVerNum(); i++)//生成点集，初始化 dist, path
    {
        vlist.append(i);
        dist[i] = g->getValue(v, i);
        path[i] = (dist[i] > 0 ? v : -1);
    }
    vlist.removeAll(v);

    while (vlist.getLength() > 0)
    {
        for (i = 1, min = 0; i < vlist.getLength(); i++)//从vlist中选出距离v最短的点，并从vlist中去除
        {
            if ((dist[vlist.at(i)] < dist[vlist.at(min)] && dist[vlist.at(i)] > 0) || dist[vlist.at(min)] == 0)
            {
                min = i;
            }
        }
        tmp = vlist.at(min);
        vlist.removeAt(min);
        min = tmp;

        for (i = 0; i < vlist.getLength(); i++)//最短路径长度修正
        {
            if (g->isArcExist(min, vlist.at(i)))
            {
                if (dist[vlist.at(i)] == 0)
                {
                    dist[vlist.at(i)] = dist[min] + g->getValue(min, vlist.at(i));
                    path[vlist.at(i)] = min;
                }
                else
                {
                    if (dist[vlist.at(i)] > dist[min] + g->getValue(min, vlist.at(i)))
                    {
                        dist[vlist.at(i)] = dist[min] + g->getValue(min, vlist.at(i));
                        path[vlist.at(i)] = min;
                    }
                }
            }
        }
    }

    ret.insert(0, w);
    while (v != w)
    {
        w = path[w];
        ret.insert(0, w);
    }
    delete dist;
    delete path;
}
void Chapter6_Part1::practice_023()
{
    AdjMGraph graph;
    LinkList<ARC> list;
    graph.addVertexs(9);
    list << ARC(0, 1, 1) << ARC(0, 2, 10) << ARC(0, 6, 7) << ARC(0, 5, 6) << ARC(6, 5, 3) << ARC(1, 6, 4) <<
        ARC(1, 3, 2) << ARC(3, 2, 4) << ARC(7, 6, 10) << ARC(7, 1, 11) << ARC(5, 8, 4) << ARC(2, 8, 3) <<
        ARC(2, 5, 1) << ARC(6, 4, 7) << ARC(5, 4, 2);
    graph.insertUArcs(list);

    LinkList<int> ret;
    Dijkstra(&graph, 4, 3, ret);
    DEBUG<<"4 -> 3: "<<ret.print();
    ret.clear();
    Dijkstra(&graph, 0, 6, ret);
    DEBUG<<"0 -> 6: "<<ret.print();
    ret.clear();
    Dijkstra(&graph, 5, 7, ret);
    DEBUG<<"5 -> 7: "<<ret.print();
    ret.clear();
    Dijkstra(&graph, 0, 2, ret);
    DEBUG<<"0 -> 2: "<<ret.print();
    ret.clear();
    Dijkstra(&graph, 6, 8, ret);
    DEBUG<<"6 -> 8: "<<ret.print();
}

/*
单源最短路径 Floyd算法
*/
void Floyd(AdjMGraph *g, int v, int w, LinkList<int> &ret)
{
    int i, j, k;
    const int verNum = g->getVerNum();
    int **dist, **path;
    dist = new int *[verNum];//dist[i][j]记录从 i -> j 的最短路径长度
    path = new int *[verNum];//path[i][j]记录从 i -> j 的最短路径上j的前驱顶点
    for (i = 0; i < verNum; i++)
    {
        dist[i] = new int[verNum];
        path[i] = new int[verNum];
    }
    for (i = 0; i < verNum; i++)//初始化 dist, path
    {
        for (j = 0; j < verNum; j++)
        {
            dist[i][j] = g->getValue(i, j);
            path[i][j] = (dist[i][j] > 0 ? i : -1);
        }
    }

    for (i = 0; i < verNum; i++)
    {
        for (j = 0; j < verNum; j++)
        {
            for (k = 0; k < verNum; k++)
            {
                if (j != k)//最短路径长度修正
                {
                    if (dist[j][k] == 0)
                    {
                        if (dist[j][i] > 0 && dist[i][k] > 0)
                        {
                            dist[j][k] = dist[j][i] + dist[i][k];
                            path[j][k] = path[i][k];
                        }
                    }
                    else
                    {
                        if (dist[j][i] > 0 && dist[i][k] > 0 && dist[j][k] > dist[j][i] + dist[i][k])
                        {
                            dist[j][k] = dist[j][i] + dist[i][k];
                            path[j][k] = path[i][k];
                        }
                    }
                }
            }
        }
    }

    ret.insert(0, w);
    while (v != w)
    {
        w = path[v][w];
        ret.insert(0, w);
    }

    for (i = 0; i < verNum; i++)
    {
        delete[] dist[i];
        delete[] path[i];
    }
    delete[] dist;
    delete[] path;
}
void Chapter6_Part1::practice_024()
{
    AdjMGraph graph;
    LinkList<ARC> list;
    graph.addVertexs(9);
    list << ARC(0, 1, 1) << ARC(0, 2, 10) << ARC(0, 6, 7) << ARC(0, 5, 6) << ARC(6, 5, 3) << ARC(1, 6, 4) <<
        ARC(1, 3, 2) << ARC(3, 2, 4) << ARC(7, 6, 10) << ARC(7, 1, 11) << ARC(5, 8, 4) << ARC(2, 8, 3) <<
        ARC(2, 5, 1) << ARC(6, 4, 7) << ARC(5, 4, 2);
    graph.insertUArcs(list);

    LinkList<int> ret;
    Dijkstra(&graph, 4, 3, ret);
    DEBUG<<"4 -> 3: "<<ret.print();
    ret.clear();
    Dijkstra(&graph, 0, 6, ret);
    DEBUG<<"0 -> 6: "<<ret.print();
    ret.clear();
    Dijkstra(&graph, 5, 7, ret);
    DEBUG<<"5 -> 7: "<<ret.print();
    ret.clear();
    Dijkstra(&graph, 0, 2, ret);
    DEBUG<<"0 -> 2: "<<ret.print();
    ret.clear();
    Dijkstra(&graph, 6, 8, ret);
    DEBUG<<"6 -> 8: "<<ret.print();
}

/*
拓扑排序
*/
void TopologicalSort(AdjMGraph *g, LinkList<int> &ret)
{
    int i, v;
    SeqStack<int> stack;
    const int verNum = g->getVerNum();
    int *indegree = new int[verNum];//入度表，保存各个顶点的入度
    for (i = 0; i < verNum; i++)
    {
        indegree[i] = g->inDegree(i);
        if (indegree[i] == 0)//入度为0的顶点入栈
        {
            stack.push(i);
        }
    }
    while (stack.getSize() > 0)
    {
        v = stack.pop();
        ret.append(v);
        for (i = g->firstAdjVex(v); i >= 0; i = g->nextAdjVex(v, i))//所有已v关联的顶点入度减一
        {
            indegree[i]--;
            if (indegree[i] == 0)//入度为0的顶点入栈
            {
                stack.push(i);
            }
        }
    }
    delete[] indegree;
}
void Chapter6_Part1::practice_025()
{
    AdjMGraph graph;
    LinkList<ARC> list;
    graph.addVertexs(15);
    list << ARC(0, 1, 1) << ARC(0, 2, 1) << ARC(1, 8, 1) << ARC(1, 3, 1) << ARC(2, 3, 1) << ARC(2, 4, 1) <<
        ARC(8, 9, 1) << ARC(8, 5, 1) << ARC(3, 5, 1) << ARC(3, 6, 1) << ARC(9, 10, 1) << ARC(5, 7, 1) <<
        ARC(7, 10, 1) << ARC(10, 12, 1) << ARC(7, 11, 1) << ARC(11, 13, 1) << ARC(12, 13, 1) << ARC(13, 14, 1);
    graph.insertDArcs(list);

    LinkList<int> ret;
    TopologicalSort(&graph, ret);
    DEBUG<<ret.print();
}

/*
关键路径
*/
void CriticalPath(AdjMGraph *g, LinkList<int> &ret)
{
    int i, j, v, ete, lte;
    const int verNum = g->getVerNum();
    SeqStack<int> stack1, stack2;//stack1用作拓扑排序的辅助栈，stack2用于存储拓扑排序的序列
    int *indegree;//入度表
    int *etv, *ltv;//etc为事件最早发生时间表，ltv为事件最迟发生时间表
    etv = new int[verNum];
    ltv = new int[verNum];
    memset(etv, 0x00, verNum * sizeof(int));
    indegree = new int[verNum];
    for (i = 0; i < verNum; i++)
    {
        indegree[i] = g->inDegree(i);
        if (indegree[i] == 0)//入度为0的顶点入栈
        {
            stack1.push(i);
        }
    }

    while (stack1.getSize() > 0)//通过拓扑排序算法构造事件最早发生时间表
    {
        v = stack1.pop();
        stack2.push(v);//弹出的顶点加入拓扑排序的序列
        for (i = g->firstAdjVex(v); i >= 0; i = g->nextAdjVex(v, i))//所有已v关联的顶点入度减一
        {
            indegree[i]--;
            if (indegree[i] == 0)//入度为0的顶点入栈
            {
                stack1.push(i);
            }
            if (etv[i] < etv[v] + g->getValue(v, i))//修正事件最早发生时间
            {
                etv[i] = etv[v] + g->getValue(v, i);
            }
        }
    }

    for (i = 0; i < verNum; i++)
    {
        ltv[i] = etv[verNum - 1];
    }
    while (stack2.getSize() > 0)//构造事件最迟发生时间表
    {
        v = stack2.pop();
        stack1.push(v);//保存之前的拓扑排序用于输出关键路径
        for (i = g->firstAdjVex(v); i >= 0; i = g->nextAdjVex(v, i))
        {
            if (ltv[v] > ltv[i] - g->getValue(v, i))
            {
                ltv[v] = ltv[i] - g->getValue(v, i);
            }
        }
    }

    while (stack1.getSize() > 0)
    {
        v = stack1.pop();
        for (i = g->firstAdjVex(v); i >= 0; i = g->nextAdjVex(v, i))
        {
            ete = etv[v];
            lte = ltv[i] - g->getValue(v, i);
            if (ete == lte)
            {
                if (ret.getLength() == 0)
                    ret.append(v);
                ret.append(i);
            }
        }
    }

    delete[] indegree;
    delete[] etv;
    delete[] ltv;
}
void Chapter6_Part1::practice_026()
{
    AdjMGraph graph;
    LinkList<ARC> list;
    graph.addVertexs(17);
    list << ARC(0, 1, 5) << ARC(2, 3, 1) << ARC(3, 1, 2) << ARC(1, 4, 4) << ARC(4, 5, 6) << ARC(4, 6, 8) << ARC(6, 7, 2) << ARC(5, 9, 9) << ARC(5, 7, 3) << ARC(7, 8, 6) << ARC(9, 8, 4) << ARC(9, 10, 1) << ARC(10, 11, 7) << ARC(8, 11, 11) << ARC(11, 12, 10) << ARC(12, 15, 7) << ARC(8, 13, 20) << ARC(13, 14, 7) << ARC(14, 15, 2) << ARC(15, 16, 3);
    graph.insertDArcs(list);

    LinkList<int> ret;
    CriticalPath(&graph, ret);
    DEBUG<<ret.print();
}
