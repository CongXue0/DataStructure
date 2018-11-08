#include "chapter1_part1.h"
#include "src/utils/tool.h"
#include "src/01_LinearList/seqlist.h"
#include "src/01_LinearList/linklist.h"
#include "src/01_LinearList/doublelinklist.h"

/*
已知顺序表 La 和 Lb 的元素递增排列，归并 La 和 Lb 到 Lc，使其也为递增排列
*/
void Chapter1_Part1::practice_000(QString input, QString &result)
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

/*
逆位序输入n个元素的值，建立单链表list
*/
void Chapter1_Part1::practice_050(QString input, QString &result)
{
    if (input.isEmpty())
    {
        input = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10";
    }
    QStringList strList = input.split('\n');

    LinkList<int> list;
    for (int i = 0; i < strList.count(); i++)
    {
        LinkListNode<int> *node = new LinkListNode<int>();
        node->data = strList.at(i).toInt();
        node->next = list.m_header;
        list.m_header = node;
        list.m_length++;
    }
    result.append(Tool::printLinkList(list) + "\n");
}

/*
双向链表demo
*/
void Chapter1_Part1::practice_100(QString input, QString &result)
{
    DoubleLinkList<int> list;
    list.append(-1);
    list.append(-2);
    list.append(0);
    list.append(4);
    list.append(99);
    list.append(200);
    list.append(134);
    result.append(Tool::printDoubleLinkList(list) + "\n");

    list.insert(4, -87);
    result.append(Tool::printDoubleLinkList(list) + "\n");

    list.removeAt(6);
    result.append(Tool::printDoubleLinkList(list) + "\n");

    list.clear();
    result.append(Tool::printDoubleLinkList(list) + "\n");

    DEBUG<<result;
}
