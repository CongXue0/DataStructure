#include "chapter2_part1.h"
#include "src/02_StackAndQueue/seqstack.h"
#include "src/02_StackAndQueue/linkstack.h"
#include "src/02_StackAndQueue/seqqueue.h"
#include "src/02_StackAndQueue/linkqueue.h"
#include "src/utils/tool.h"

/*
栈与队列demo
*/
void Chapter2_Part1::practice_000(QString input, QString &result)
{
//    SeqStack<int> stack;
    LinkStack<int> stack;
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

//    SeqQueue<int> queue;
//    LinkQueue<int> queue;
//    queue.enqueue(1);
//    queue.enqueue(8);
//    queue.enqueue(-20);
//    queue.enqueue(-23);
//    DEBUG<<queue.head();
//    DEBUG<<queue.print();
//    DEBUG<<queue.dequeue();
//    DEBUG<<queue.dequeue();
//    DEBUG<<queue.print();
//    queue.enqueue(45);
//    queue.enqueue(13);
//    queue.enqueue(99);
//    DEBUG<<queue.head();
//    DEBUG<<queue.print();
//    queue.clear();
//    DEBUG<<queue.print();

}

/*
进制转换，十进制数n到base进制的转换
*/
void convert(SeqStack<char>& stack, unsigned long long num, int base)
{
    static char digit[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    while (num > 0)
    {
        stack.push(digit[num % base]);
        num = num / base;
    }
}
void Chapter2_Part1::practice_050(QString input, QString &result)
{
    SeqStack<char> stack;
    unsigned long long num = 123;
    convert(stack, num, 16);
    QString str;
    while (stack.getSize() > 0)
    {
        str.append(stack.pop());
    }
    DEBUG<<str;
}

/*
就近匹配
*/
bool nearestMatch(const char exp[], int low, int high)
{
    SeqStack<char> stack;
    for (int i = low; i <= high;  i++)
    {
        char ch = exp[i];
        if (ch == '<' || ch == '(' || ch == '{' || ch == '[')
        {
            stack.push(ch);
        }
        else if (ch == '>' || ch == ')' || ch == '}' || ch == ']')
        {
            if (stack.getSize() > 0)
            {
                char c = stack.pop();
                if (ch == '>') ch = '<';
                if (ch == ')') ch = '(';
                if (ch == '}') ch = '{';
                if (ch == ']') ch = '[';
                if (ch != c)
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }
    if (stack.getSize() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Chapter2_Part1::practice_051(QString input, QString &result)
{
    char str[500] = "{(4+5)-<3, 4>}&&{456-876}+<3, 90>";
    DEBUG<<nearestMatch(str, 0, 100);
}
