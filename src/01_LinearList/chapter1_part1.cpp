#include "chapter1_part1.h"
#include "src/utils/tool.h"
#include "src/01_LinearList/seqlist.h"

/*
已知顺序表 La 和 Lb 的元素递增排列，归并 La 和 Lb 到 Lc，使其也为递增排列
*/
void Chapter1_Part1::practice_001(QString &result)
{
    SeqList<int> lista;
    lista.append(-20);
    lista.append(30);
    lista.append(100);
    SeqList<int> listb;
    listb.append(-1);
    listb.append(0);
    listb.append(1);
    listb.append(100);
    listb.append(133);
    listb.append(500);

    SeqList<int> listc;
    int ia = 0;
    int ib = 0;
    while (ia < lista.getLength() && ib < listb.getLength())//把 a b 表排序插入 c
    {
        if (lista.at(ia) <= listb.at(ib))
        {
            listc.append(lista.at(ia));
            ia++;
        }
        else
        {
            listc.append(listb.at(ib));
            ib++;
        }
    }
    for (; ia < lista.getLength(); ia++)//剩余表元素插入 c
    {
        listc.append(lista.at(ia));
    }
    for (; ib < listb.getLength(); ib++)//剩余表元素插入 c
    {
        listc.append(listb.at(ib));
    }
    result = Tool::printSeqList(listc);
    DEBUG<<"result:"<<result;
}
