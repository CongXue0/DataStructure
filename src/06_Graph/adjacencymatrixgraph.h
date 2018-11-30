#ifndef ADJACENCYMATRIXGRAPH_H
#define ADJACENCYMATRIXGRAPH_H

#define ADJMGRAPH_INIT_SIZE 20

class AdjacencyMatrixGraph;
typedef AdjacencyMatrixGraph AdjMGraph;

//邻接矩阵
class AdjacencyMatrixGraph
{
public:
    AdjacencyMatrixGraph(int capacity = ADJMGRAPH_INIT_SIZE);
    ~AdjacencyMatrixGraph();
    int getVerNum();
    int getArcNum();
    int getCapacity();
    void clear();
    bool isVertexExist(int v);
    bool isArcExist(int v, int w);//边v -> w是否存在
    int firstAdjVex(int v);//返回v的第一个邻接顶点，若无返回-1
    int nextAdjVex(int v, int w);//返回v相对于w的第一个邻接顶点，若无返回-1
    int addVertex();//增加1个新的顶点，返回顶点标号，标号从0开始
    void addVertexs(int num);//增加num个新的顶点
    void removeVertex(int v);//删除一个顶点
    void insertDArc(int v, int w, int value = 1);//加入有向边 v -> w, value为权重
    void insertUArc(int v, int w, int value = 1);//加入无向边
    void BFSTraverse();//广度优先搜索 Breadth-First-Search
    void DFSTraverse();//深度优先搜索 Depth-First-Search
    void print();

    static void BFS(AdjacencyMatrixGraph *g, int v);
    static void DFS(AdjacencyMatrixGraph *g, int v);


private:
    unsigned char *m_vexs;
    int **m_arc;
    unsigned char *m_visited;
    int m_verNum;//顶点数
    int m_arcNum;//弧数
    int m_capacity;

};

#endif // ADJACENCYMATRIXGRAPH_H
