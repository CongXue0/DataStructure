#include "chapter2_part1.h"
#include "src/02_StackAndQueue/seqstack.h"
#include "src/02_StackAndQueue/linkstack.h"
#include "src/02_StackAndQueue/seqqueue.h"
#include "src/02_StackAndQueue/linkqueue.h"
#include "src/utils/tool.h"
#include "src/utils/virtualio.h"

/*
栈与队列demo
*/
void Chapter2_Part1::practice_000()
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
void Chapter2_Part1::practice_001()
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
void Chapter2_Part1::practice_002()
{
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
bool isStackShuffle(int arrA[], int arrB[], int len)//判断栈B是否石栈A的栈混洗
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
    delete[] tmpArr;
    return (pt == -1);
}
void Chapter2_Part1::practice_003()
{
    //右边为栈顶
    int arrA[5] = {5, 4, 3, 2, 1};
    int arrB[5] = {3, 4, 2, 5, 1};
    int arrC[5] = {3, 4, 1, 5, 2};
    DEBUG<<"isStackShuffle:"<<isStackShuffle(arrA, arrB, 5);
    DEBUG<<"isStackShuffle:"<<isStackShuffle(arrA, arrC, 5);
}

/*
表达式求值，中缀表达式先转成后缀表达式，在求值
中缀转后缀算法：
    数字直接输出
    符号：
        左括号 进栈
        运算符号 与栈顶符号比较优先级，若栈顶优先级低进栈
            ，若栈顶优先级高，栈顶出栈，符号进栈，默认左括号优先级最低
        右括号 将栈顶符号弹出，直到匹配到左括号
*/
void infixToSuffixExpression_transform(const char *source, char *destination)//中缀转后缀表达式
{
    int len = strlen(source);
    char ch, tmp;
    int i = 0, j = 0;
    SeqStack<char> stack;
    for (; i < len; i++)
    {
        ch = source[i];
        if (ch == ' ')
            continue;
        if (ch == '-' || ch == '+')
        {
            destination[j++] = '0';
            destination[j++] = ' ';
            while (source[i + 1] >= '0' && source[i + 1] <= '9')
            {
                destination[j++] = source[++i];
            }
            destination[j++] = ' ';
            destination[j++] = ch;
            destination[j++] = ' ';
            i++;
        }
        break;
    }
    for (; i < len; i++)
    {
        ch = source[i];
        if (ch == ' ')
            continue;
        if (ch >= '0' && ch <= '9')
        {
            destination[j++] = ch;
            while (source[i + 1] >= '0' && source[i + 1] <= '9')
            {
                destination[j++] = source[++i];
            }
            destination[j++] = ' ';
        }
        else
        {
            if (ch == '(' || stack.getSize() == 0)
            {
                stack.push(ch);
            }
            else if (ch == '*' || ch == '/')
            {
                tmp = stack.top();
                if (tmp == '+' || tmp == '-' || tmp == '(')
                    stack.push(ch);
                else if (tmp == '*' || tmp == '/')
                {
                    destination[j++] = stack.pop();
                    destination[j++] = ' ';
                    stack.push(ch);
                }
            }
            else if (ch == '+' || ch == '-')
            {
                tmp = stack.top();
                if (tmp == '(' || stack.getSize() == 0)
                    stack.push(ch);
                else if (tmp == '+' || tmp == '-' || tmp == '*' || tmp == '/')
                {
                    destination[j++] = stack.pop();
                    destination[j++] = ' ';
                    stack.push(ch);
                }
            }
            else if (ch == ')')
            {
                while ((tmp = stack.pop()) != '(')
                {
                    destination[j++] = tmp;
                    destination[j++] = ' ';
                }
            }
        }
        if (i == len - 1)
        {
            while (stack.getSize() > 0)
            {
                destination[j++] = stack.pop();
                destination[j++] = ' ';
            }
            destination[j] = '\0';
        }
    }
}
int suffixExpression_calc(char *expression)
{
    LinkStack<int> stack;
    int len = strlen(expression);
    for (int i = 0; i < len; i++)
    {
        char ch = expression[i];
        if (ch == ' ')
            continue;
        if (ch >= '0' && ch <= '9')
        {
            int tmp = ch - '0';
            while (expression[i + 1] >= '0' && expression[i + 1] <= '9')
            {
                tmp = tmp * 10 + expression[i + 1] - '0';
                i++;
            }
            stack.push(tmp);
        }
        else
        {
            int tmp2 = stack.pop();
            int tmp1 = stack.pop();
            switch (ch)
            {
            case '+':
                tmp1 = tmp1 + tmp2;
                break;
            case '-':
                tmp1 = tmp1 - tmp2;
                break;
            case '*':
                tmp1 = tmp1 * tmp2;
                break;
            case '/':
                tmp1 = tmp1 / tmp2;
                break;
            }
            stack.push(tmp1);
        }
    }
    return stack.top();
}
void Chapter2_Part1::practice_004()
{
//    char *expression1 = "(1 - 4) * 8 + 29 / ((5 - 2) * 3)";
    const char *expression1 = "-1 * 20 + 100";
    char buffer[50];
    infixToSuffixExpression_transform(expression1 , buffer);
    DEBUG<<"expression1:"<<expression1;
    DEBUG<<"expression1 tran:"<<buffer;
    DEBUG<<"结果为: "<<suffixExpression_calc(buffer);

    const char *expression2 = "1+2*(66/(2*3))+7";
    infixToSuffixExpression_transform(expression2, buffer);
    DEBUG<<"expression2:"<<expression2;
    DEBUG<<"expression2 tran:"<<buffer;
    DEBUG<<"结果为: "<<suffixExpression_calc(buffer);
}

/*
列车调度(Train)
描述
某列车调度站的铁道联接结构如Figure 1所示。
其中，A为入口，B为出口，S为中转盲端。所有铁道均为单轨单向式：列车行驶的方向只能是从A到S，再从S到B；另外，不允许超车。因为车厢可在S中驻留，所以它们从B端驶出的次序，可能与从A端驶入的次序不同。不过S的容量有限，同时驻留的车厢不得超过m节。
设某列车由编号依次为{1, 2, ..., n}的n节车厢组成。调度员希望知道，按照以上交通规则，这些车厢能否以{a1, a2, ..., an}的次序，重新排列后从B端驶出。如果可行，应该以怎样的次序操作?

输入
共两行。
第一行为两个整数n，m。
第二行为以空格分隔的n个整数，保证为{1, 2, ..., n}的一个排列，表示待判断可行性的驶出序列{a1，a2，...，an}。

输出
若驶出序列可行，则输出操作序列，其中push表示车厢从A进入S，pop表示车厢从S进入B，每个操作占一行。
若不可行，则输出No。

样例
Example 1
Input:
5 2
1 2 3 5 4
Output:
push
pop
push
pop
push
pop
push
push
pop
pop

Example 2
Input:
5 5
3 1 2 4 5
Output:
No

限制
1 ≤ n ≤ 1600000
0 ≤ m ≤ 1600000
时间：2 sec
空间：256 MB
*/
#if OJ_TEST == 1
    #define p050_ARRSIZE 1600000
#else
    #define p050_ARRSIZE 100
#endif
int p050_tmpStack[p050_ARRSIZE];
int p050_stack[p050_ARRSIZE];
char p050_output[p050_ARRSIZE * 5];
void Chapter2_Part1::practice_050()
{
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    int i, j = 0, m = -1, k = 0;//i 初始栈的指针, j 结果栈的指针, m 辅助栈的指针, k 输出结果的长度
    int stackSize, tmpStackSize;
    SCANF("%d %d", &stackSize, &tmpStackSize);
    for (i = 0; i < stackSize; i++)
        SCANF("%d", &p050_stack[i]);
    if (tmpStackSize == 0)
        goto p050_EXIT;

    i = 1;
    while (i <= stackSize)
    {
        while (i <= stackSize)//先入辅助栈
        {
            if (i == p050_stack[j])
            {
                if (m + 2 > tmpStackSize)
                    goto p050_EXIT;
                p050_output[k] = 'p', p050_output[k + 1] = 'u', p050_output[k + 2] = 's', p050_output[k + 3] = 'h', p050_output[k + 4] = '\n';
                k += 5;
                p050_output[k] = 'p', p050_output[k + 1] = 'o', p050_output[k + 2] = 'p', p050_output[k + 3] = '\n';
                k += 4;
                i++, j++;
                break;
            }
            if (m + 2 > tmpStackSize)
                goto p050_EXIT;
            p050_output[k] = 'p', p050_output[k + 1] = 'u', p050_output[k + 2] = 's', p050_output[k + 3] = 'h', p050_output[k + 4] = '\n';
            k += 5;
            p050_tmpStack[++m] = i++;
        }
        while (m > -1 && p050_tmpStack[m] == p050_stack[j])//辅助栈元素入结果栈
        {
            p050_output[k] = 'p', p050_output[k + 1] = 'o', p050_output[k + 2] = 'p', p050_output[k + 3] = '\n';
            k += 4;
            m--, j++;
        }
    }
p050_EXIT:
    p050_output[k] = '\0';
    if (m == -1 && k > 0)
        PRINTF("%s", p050_output);
    else
        PRINTF("No\n");
}
