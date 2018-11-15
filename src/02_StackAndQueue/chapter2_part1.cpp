#include "chapter2_part1.h"
#include "src/02_StackAndQueue//seqstack.h"
#include "src/02_StackAndQueue/linkstack.h"

/*
栈与队列demo
*/
void Chapter2_Part1::practice_000(QString input, QString &result)
{
//    SeqStack<int> stack;
    SeqStack<int> stack;
    stack.push(1);
    stack.push(-1);
    stack.push(100);
    stack.push(60);
    DEBUG<<stack.print();
    DEBUG<<stack.pop();
    DEBUG<<stack.pop();
    stack.push(34);
    DEBUG<<stack.print();
    stack.clear();
    DEBUG<<stack.print();
}
