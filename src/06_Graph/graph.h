#ifndef GRAPH_H
#define GRAPH_H

#define GRAPH_INIT_SIZE 10
#define ARC_INFINITY 0x40000000

//v -> w
class ARC
{
public:
    ARC() : v(0), w(0), val(1) {}
    ARC(int _v, int _w, int _val = 1)
    {
        v = _v, w = _w;
        val = (_val < 1 ? 1 : _val);
    }
    int v, w;
    int val;
};

class Graph
{
public:

};

#endif // GRAPH_H
