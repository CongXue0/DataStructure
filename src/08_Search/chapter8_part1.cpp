#include "chapter8_part1.h"
#include "src/08_Search/search.h"
#include "src/08_Search/hashtable.h"

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
