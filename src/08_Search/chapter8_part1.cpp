#include "chapter8_part1.h"
#include "src/08_Search/search.h"
#include "src/08_Search/hashtable.h"
#include "src/08_Search/redblacktree.h"
#include "src/utils/tool.h"

/*
哈希表demo
*/
void Chapter8_Part1::practice_000()
{
    HashTable<const char *, int> h1;
    h1.insert("a", 10);
    h1.insert("b", 20);
    h1.insert("c", 30);
    h1.insert("apple", 100);
    h1.insert("anviz", 200);
    h1.print();
    DEBUG<<"h1 size:"<<h1.getSize();
    DEBUG<<"a : "<<h1["a"];
    DEBUG<<"b : "<<h1["b"];
    DEBUG<<"c : "<<h1["c"];
    DEBUG<<"apple : "<<h1["apple"];
    DEBUG<<"anviz : "<<h1["anviz"];
    DEBUG<<"contains apple : "<<h1.contains("apple");
    h1.remove("b");
    DEBUG<<"contains b : "<<h1.contains("b");
    h1.clear();
    DEBUG<<"contains apple : "<<h1.contains("apple");
    DEBUG<<"h1 capacity : "<<h1.getCapacity();
    DEBUG<<"h1 size:"<<h1.getSize();
    h1.print();

    DEBUG<<"--------------------";
    HashTable<int, int> h2;
    for (int i = -100; i < 1000; i++)
    {
        h2.insert(i, i + 1000);
    }
    h2.print();
    DEBUG<<"256 : "<<h2.value(256);
    DEBUG<<"999 : "<<h2.value(999);
    DEBUG<<"-1 : "<<h2.value(-1);
    DEBUG<<"-100 : "<<h2.value(-100);
    DEBUG<<"h2 capacity : "<<h2.getCapacity();
    DEBUG<<"h2 size:"<<h2.getSize();
    h2.clear();
    DEBUG<<"h2 capacity : "<<h2.getCapacity();
    DEBUG<<"h2 size:"<<h2.getSize();
}

/*
红黑树demo
*/
void Chapter8_Part1::practice_001()
{
    RedBlackTree<int, int> t1;
    const int len = 100;
    int *arr = new int[len];
    int r;
    SeqQueue<int> queue;
    Tool::createRandArr(arr, len, -1 * len, len);
    DEBUG<<Tool::printArr<int>(arr, 0, len - 1);
    for (int i = 0; i < len; i++)
    {
        t1.insert(arr[i], i + 100);
    }
    t1.print();
    DEBUG<<"t1 size:"<<t1.getSize();
    for (int i = 0; i < t1.getSize() / 2; i++)
    {
        r = Tool::rand(0, len - 1);
        queue.enqueue(arr[r]);
        DEBUG<<"remove "<<arr[r];
        t1.remove(arr[r]);
    }
    while (queue.getSize() > 0)
    {
        r = queue.dequeue();
        DEBUG<<"contain "<<r<<" : "<<t1.contains(r);
    }
    t1.print();
    DEBUG<<"t1 size:"<<t1.getSize();
    t1.clear();
    DEBUG<<"t1 size:"<<t1.getSize();

//    QStringList list = QString("-27 85 -57 -46 -19 -41 37 -60 -7 -34").split(' ');
//    for (int i = 0; i < 10; i++)
//    {
//        t1.insert(list.at(i).toInt(), list.at(i).toInt() + 100);
//    }
//    t1.print();
//    DEBUG<<"t1 size:"<<t1.getSize();
//    t1.remove(-19);
//    t1.remove(85);
//    t1.remove(-7);
//    t1.remove(37);
//    t1.print();
//    DEBUG<<"t1 size:"<<t1.getSize();
//    t1.clear();
//    DEBUG<<"t1 size:"<<t1.getSize();



//    RedBlackTree<const char *, int> t2;
//    t2.insert("a", 10);
//    t2.insert("b", 20);
//    t2.insert("c", 30);
//    t2.insert("apple", 100);
//    t2.insert("anviz", 200);
//    t2.print();
//    DEBUG<<"h1 size:"<<t2.getSize();
//    DEBUG<<"a : "<<t2["a"];
//    DEBUG<<"b : "<<t2["b"];
//    DEBUG<<"c : "<<t2["c"];
//    DEBUG<<"apple : "<<t2["apple"];
//    DEBUG<<"anviz : "<<t2["anviz"];
//    DEBUG<<"contains apple : "<<t2.contains("apple");
//    t2.remove("b");
//    DEBUG<<"contains b : "<<t2.contains("b");
//    t2.clear();
//    DEBUG<<"contains apple : "<<t2.contains("apple");
//    DEBUG<<"h1 size:"<<t2.getSize();
//    t2.print();

    delete[] arr;
}
