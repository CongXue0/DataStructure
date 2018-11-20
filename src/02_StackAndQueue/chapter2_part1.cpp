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
    Q_UNUSED(input);Q_UNUSED(result);
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
void Chapter2_Part1::practice_001(QString input, QString &result)
{
    Q_UNUSED(input);Q_UNUSED(result);
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
void Chapter2_Part1::practice_002(QString input, QString &result)
{
    Q_UNUSED(input);Q_UNUSED(result);
    char str[500] = "{(4+5)-<3, 4>}&&{456-876}+<3, 90>";
    DEBUG<<nearestMatch(str, 0, 100);
}

/*
考查三个栈A、B和S。其中，B和S初始为空；A含有n个元素，自顶而下构成输入序列：
A = < a1, a2, ..., an ]
这里，分别用尖括号、方括号示意栈顶、栈底，这也是本小节将统一采用的约定。
以下， 若只允许通过S.push(A.pop())弹出栈A的顶元素并随即压入栈S中，或通过
B.push(S.pop())弹出S的顶元素并随即压入栈B中，则在经过这两类操作各n次之后，栈A和S
有可能均为空，原A中的元素均已转入栈B。此时，若将B中元素自底而上构成的序列记作：
B = [ ak1, ak2, ..., akn >
则该序列称作原输入序列的一个栈混洗（stack permutation）。
判断栈B是否石栈A的栈混洗
*/
bool isStackShuffle(int arrA[], int arrB[], int len)
{
    if (len <= 0)
        return false;
    int *tmpArr = new int[len];//创建辅助栈
    int pa = len - 1, pb = 0, pt = -1;
    while (pa > -1)
    {
        while (pa > -1)//先入辅助栈
        {
            if (arrA[pa] == arrB[pb])
            {
                pa--, pb++;
                break;
            }
            pt++;
            tmpArr[pt] = arrA[pa];
            pa--;
        }
        while (pt > -1 && tmpArr[pt] == arrB[pb])//辅助栈元素入栈B
        {
            pt--;
            pb++;
        }
    }
    return (pt == -1);
}
void Chapter2_Part1::practice_003(QString input, QString &result)
{
    Q_UNUSED(input);Q_UNUSED(result);
    //右边为栈顶
    int arrA[5] = {5, 4, 3, 2, 1};
    int arrB[5] = {3, 4, 2, 5, 1};
    int arrC[5] = {3, 4, 1, 5, 2};
    DEBUG<<"isStackShuffle:"<<isStackShuffle(arrA, arrB, 5);
    DEBUG<<"isStackShuffle:"<<isStackShuffle(arrA, arrC, 5);
}
