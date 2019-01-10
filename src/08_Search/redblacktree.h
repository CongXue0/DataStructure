#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "src/utils/tool.h"
#include "src/02_StackAndQueue/linkstack.h"
#include "src/02_StackAndQueue/linkqueue.h"
#include "src/02_StackAndQueue/seqstack.h"
#include "src/01_LinearList/seqlist.h"

/*
红黑树：
    1. 节点是红色或黑色。
    2. 根是黑色。
    3. 所有叶子都是黑色（叶子是NIL节点）。
    4. 每个红色节点必须有两个黑色的子节点。（从每个叶子到根的所有路径上不能有两个连续的红色节点。）
    5. 从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点（简称黑高）。
红黑树的旋转操作与平衡二叉树相同
*/
template <typename Key, typename T>
class RedBlackTree
{
public:
    enum DIRECTION
    {
        MID, LEFT, RIGHT
    };
    enum COLOR
    {
        RED, BLACK
    };
    enum ROTATE
    {
        LL, LR, RR, RL
    };
    class RedBlackTreeNode
    {
    public:
        RedBlackTreeNode() : color(RED), lchild(NULL), rchild(NULL) {}
        RedBlackTreeNode(const Key &_key, const T &_data) : key(_key), data(_data), color(RED), lchild(NULL), rchild(NULL) {}
        Key key;
        T data;
        COLOR color;//结点的颜色只有红或黑
        RedBlackTreeNode *lchild;
        RedBlackTreeNode *rchild;
    };
    RedBlackTree();
    ~RedBlackTree();
    int getSize();//元素个数
    void clear();
    int depth();
    int leafCount();//叶子结点个数
    RedBlackTree<Key, T>::RedBlackTreeNode *root();
    inline COLOR getColor(RedBlackTree<Key, T>::RedBlackTreeNode *&node) { return (node == NULL ? BLACK : (node->color)); }
    inline void swapColor(COLOR &c1, COLOR &c2) { COLOR tmp = c1; c1 = c2; c2 = tmp; }
    void insert(const Key &key, const T &t);//插入键值对，存在键时覆盖值
    void remove(const Key &key);//移除键
    void rotate(RedBlackTree<Key, T>::RedBlackTreeNode *root, RedBlackTree<Key, T>::RedBlackTreeNode **pchild, int mode);//对root做旋转操作，pchild为root的引用
    const T &value(const Key &key) const;//根据key键查找对应的值
    T &operator[](const Key &key);
    bool contains(const Key &key);//判断键存不存在
    void levelOrderTrav();//层次遍历
    void preOrderTrav();//先序遍历
    void inOrderTrav();//中序遍历
    void postOrderTrav();//后序遍历
    void print();

    static void deleteTree(RedBlackTree<Key, T>::RedBlackTreeNode *root);
    static void copyTree(RedBlackTree<Key, T>::RedBlackTreeNode *&dstRoot, const RedBlackTree<Key, T>::RedBlackTreeNode *srcRoot);
    static int depth(RedBlackTree<Key, T>::RedBlackTreeNode *root);
    static void preOrderTrav_R(RedBlackTree<Key, T>::RedBlackTreeNode *node);//先序遍历
    static void inOrderTrav_R(RedBlackTree<Key, T>::RedBlackTreeNode *node);//中序遍历
    static void postOrderTrav_R(RedBlackTree<Key, T>::RedBlackTreeNode *node);//后序遍历

public:
    RedBlackTreeNode *m_root;
    int m_size;
};

template <typename Key, typename T>
RedBlackTree<Key, T>::RedBlackTree()
{
    m_root = NULL;
    m_size = 0;
}

template <typename Key, typename T>
RedBlackTree<Key, T>::~RedBlackTree()
{
    clear();
}

template <typename Key, typename T>
int RedBlackTree<Key, T>::getSize()
{
    return m_size;
}

template <typename Key, typename T>
void RedBlackTree<Key, T>::clear()
{
    RedBlackTree<Key, T>::deleteTree(m_root);
    m_root = NULL;
    m_size = 0;
}

template <typename Key, typename T>
int RedBlackTree<Key, T>::depth()
{
    return RedBlackTree<Key, T>::depth(m_root);
}

template <typename Key, typename T>
int RedBlackTree<Key, T>::leafCount()
{
    return (m_size > 0 ? m_size + 1 : 0);
}

template <typename Key, typename T>
typename RedBlackTree<Key, T>::RedBlackTreeNode *RedBlackTree<Key, T>::root()
{
    return m_root;
}

/*
插入元素：
    1. 先找到插入结点的位置创建结点插入，插入的结点默认为红色
    2. 当新插入的结点为root结点或父结点为黑色时，不需要做改动
    3. 当插入结点的父结点和叔叔结点为红色，祖父结点为黑色，将父结点和叔叔结点变为黑色，祖父结点该为红色，再将祖父结点当做新的插入结点做判断
    4. 当插入结点的父结点为红色，叔叔结点为黑色，祖父结点为黑色，需要做旋转操作：
        （1）父结点为祖父结点的左孩子，并且插入结点为父结点的左孩子，对祖父结点使用LL操作，父结点变为黑色和祖父结点变为红色
        （2）父结点为祖父结点的左孩子，并且插入结点为父结点的右孩子，对祖父结点使用LR操作，插入结点变为黑色和祖父结点变为红色
        （3）父结点为祖父结点的右孩子，并且插入结点为父结点的右孩子，对祖父结点使用RR操作，父结点变为黑色和祖父结点变为红色
        （4）父结点为祖父结点的右孩子，并且插入结点为父结点的左孩子，对祖父结点使用RL操作，插入结点变为黑色和祖父结点变为红色
*/
template <typename Key, typename T>
void RedBlackTree<Key, T>::insert(const Key &key, const T &t)
{
    if (m_root == NULL)
    {
        m_root = new RedBlackTreeNode(key, t);
        m_root->color = BLACK;
        m_size++;
        return;
    }
    SeqStack<RedBlackTreeNode *> nodeStack;//保存从根结点到插入结点路径的栈
    SeqStack<DIRECTION> direStack;//保存从根结点到插入结点路径方向的栈
    RedBlackTreeNode *tmp = m_root, *tmp2, *tmp3;
    RedBlackTreeNode **p;

    direStack.push(MID);
    while (tmp != NULL)//查找要插入的结点和路径
    {
        nodeStack.push(tmp);
        if (key == tmp->key)
        {
            tmp->data = t;//已存在键对元素做修改
            return;
        }
        else if (key < tmp->key)
        {
            tmp = tmp->lchild;
            direStack.push(LEFT);
        }
        else if (key > tmp->key)
        {
            tmp = tmp->rchild;
            direStack.push(RIGHT);
        }
    }
    tmp = nodeStack.top();
    if (direStack.top() == LEFT)//插入元素
    {
        tmp->lchild = new RedBlackTreeNode(key, t);
        nodeStack.push(tmp->lchild);
    }
    else
    {
        tmp->rchild = new RedBlackTreeNode(key, t);
        nodeStack.push(tmp->rchild);
    }
    m_size++;
    while (nodeStack.getSize() > 2)//重新平衡红黑树
    {
        tmp = nodeStack.top(1);//插入结点
        tmp2 = nodeStack.top(2);//父节点
        if (getColor(tmp2) == BLACK)
            break;
        tmp3 = nodeStack.top(3);//祖父结点
        if (getColor(tmp3->lchild) == RED && getColor(tmp3->rchild) == RED)
        {
            tmp3->lchild->color = BLACK;
            tmp3->rchild->color = BLACK;
            tmp3->color = RED;
        }
        else
        {
            if (direStack.top(3) == MID)
            {
                p = &m_root;
            }
            else if (direStack.top(3) == LEFT)
            {
                p = &nodeStack.top(4)->lchild;
            }
            else if (direStack.top(3) == RIGHT)
            {
                p = &nodeStack.top(4)->rchild;
            }
            if (direStack.top(2) == LEFT)
            {
                if (direStack.top(1) == LEFT)
                {
                    rotate(tmp3, p, LL);
                }
                else
                {
                    rotate(tmp3, p, LR);
                }
                break;
            }
            else if (direStack.top(2) == RIGHT)
            {
                if (direStack.top(1) == RIGHT)
                {
                    rotate(tmp3, p, RR);
                }
                else
                {
                    rotate(tmp3, p, RL);
                }
                break;
            }
        }
        nodeStack.pop();
        nodeStack.pop();
        direStack.pop();
        direStack.pop();
    }
    if (m_root->color == RED)
        m_root->color = BLACK;
}

/*
删除元素：
    1. 当删除的结点为叶子结点或左右孩子有一个为NULL时可以直接删除，当删除的结点左右孩子都不为空时。
        从左子树（也可以右子树，这里统一选左子树）中找到最大的元素结点给删除的结点元素赋值，之后删除左子树最大的那个结点。
    2. 结点删除后需要重新平衡删除结点路径上的树。
    3. 删除的结点颜色是红色时，左右子树顶替删除位置后不用做修改。
    4. 删除的结点颜色是黑色时：
        （1）左右子树里有红色结点时，红色结点顶替删除位置后，红色改为黑色即可。
        //分析：（1）之后的情况里顶替结点都是黑色，由于从结点到叶子结点路径上的黑色数量相同，所有删除结点的兄弟结点必存在，父结点也必存在，应注意顶替结点和兄弟结点的孩子结点有可能为空结点，空结点也是黑色的
        （2）顶替结点的父结点为黑色，兄弟结点为红色，兄弟结点的左右子树都为黑色时：
            I. 顶替结点为夫结点的左孩子时，对父结点做RR左旋操作，父结点变为红色，兄弟结点变黑色
            II. 顶替结点为夫结点的右孩子时，对父结点做LL右旋操作，父结点变为红色，兄弟结点变黑色
            旋转完成后，对顶替结点重新做情况判断。
        （3）顶替结点的父结点为黑色，兄弟结点为黑色，兄弟结点的左右孩子也为黑色时，将兄弟结点改为红色，
            完成后将父结点当作新的顶替结点做情况判断，此时应注意删除路径上的结点数减少了一个，我们在删除路径上结点数量>1时才做情况分析，
            如果此时删除路径上只剩一个结点，那么就ok了。
        //上面的2 3情况要先做变形再重新分析，下面的4 5情况则可直接通过修改完成红黑树的平衡
        （4）顶替结点的父结点为红色，兄弟结点为黑色，兄弟结点的左右孩子全为黑色时，将父结点改为黑色，
            兄弟结点改为红色，此时已经完成整棵树的平衡。
        （5）父结点的颜色不做要求，假设为A颜色，兄弟结点为黑色，兄弟结点的左右孩子里有任意一个为红色结点时：
            I. 若顶替结点为父结点的左孩子：
                <1>. 如果兄弟结点的右孩子为红色，对父结点做RR左旋操作，交换父结点与兄弟结点的颜色，父结点变为黑色，兄弟结点变为A色，
                    兄弟结点的右孩子改为黑色。
                <2>. 如果兄弟结点的右孩子为黑色（此时兄弟结点的左孩子必为红色），对父结点做RL操作（先对兄弟结点右旋，再对父结点左旋），
                    兄弟结点的左孩子改为黑色，再交换父结点和兄弟结点的左孩子的颜色，父结点变为黑色，兄弟结点的左孩子变为A色。
            II. 若顶替结点为父结点的右孩子：
                <1>. 如果兄弟结点的左孩子为红色，对父结点做LL左旋操作，交换父结点与兄弟结点的颜色，父结点变为黑色，兄弟结点变为A色，
                    兄弟结点的左孩子改为黑色。
                <2>. 如果兄弟结点的左孩子为黑色（此时兄弟结点的右孩子必为红色），对父结点做LL操作（先对兄弟结点左旋，再对父结点右旋），
                    兄弟结点的右孩子改为黑色，再交换父结点和兄弟结点的右孩子的颜色，父结点变为黑色，兄弟结点的左孩子变为A色。
            （5）此时已经完成整棵树的平衡。

*/
template <typename Key, typename T>
void RedBlackTree<Key, T>::remove(const Key &key)
{
    if (m_size <= 1)
    {
        if (m_root != NULL && m_root->key == key)
        {
            delete m_root;
            m_root = NULL;
            m_size--;
        }
        return;
    }
    SeqStack<RedBlackTreeNode *> nodeStack;//保存从根结点到删除结点路径的栈
    SeqStack<DIRECTION> direStack;//保存从根结点到插入结点路径方向的栈
    DIRECTION lastDire;
    COLOR lastColor;
    RedBlackTreeNode *tmp = m_root, *tmp2, *tmp3, *tmp4;
    RedBlackTreeNode **p;

    direStack.push(MID);
    while (tmp != NULL)//查找要删除的结点和路径
    {
        nodeStack.push(tmp);
        if (key == tmp->key)
        {
            break;
        }
        else if (key < tmp->key)
        {
            tmp = tmp->lchild;
            direStack.push(LEFT);
        }
        else if (key > tmp->key)
        {
            tmp = tmp->rchild;
            direStack.push(RIGHT);
        }
    }
    if (tmp == NULL)
        return;
    tmp = nodeStack.top();
    if (tmp->lchild != NULL && tmp->rchild != NULL)//删除的结点左右孩子结点都不为空时，重定删除位置
    {
        //从左子树中找最大的元素与删除元素做交换
        tmp2 = tmp->lchild;
        direStack.push(LEFT);
        while (tmp2 != NULL)
        {
            nodeStack.push(tmp2);
            tmp2 = tmp2->rchild;
            direStack.push(RIGHT);
        }
        direStack.pop();
        tmp2 = nodeStack.top();
        tmp->key = tmp2->key;
        tmp->data = tmp2->data;
    }

    tmp = nodeStack.pop();//待删除结点
    lastColor = tmp->color;
    lastDire = direStack.top();
    if (lastDire == MID)//删除结点，并向栈中加入顶替结点
    {
        m_root = (tmp->lchild != NULL ? tmp->lchild : tmp->rchild);
        nodeStack.push(m_root);
    }
    else
    {
        tmp2 = nodeStack.top();//父结点
        if (lastDire == LEFT)
        {
            tmp2->lchild = (tmp->lchild != NULL ? tmp->lchild : tmp->rchild);
            nodeStack.push(tmp2->lchild);
        }
        else
        {
            tmp2->rchild = (tmp->lchild != NULL ? tmp->lchild : tmp->rchild);
            nodeStack.push(tmp2->rchild);
        }
    }
    delete tmp;
    m_size--;
    if (lastColor == RED)
        return;
    tmp = nodeStack.top();//顶替结点，注意顶替结点可能为NULL
    if (getColor(tmp) == RED)
    {
        tmp->color = BLACK;
        return;
    }

    //剩下的情形顶替结点的父结点一定存在，并且其兄弟结点也一定存在（因为左右子树的黑高相同，右子树必须有一个实黑）
    while (nodeStack.getSize() > 1)//重新平衡红黑树
    {
        lastDire = direStack.pop();
        tmp = nodeStack.pop();//顶替结点
        tmp2 = nodeStack.top();//父结点
        tmp3 = (lastDire == LEFT ? tmp2->rchild : tmp2->lchild);//兄弟结点
        if (tmp2->color == BLACK && tmp3->color == RED)
        {
            p = (direStack.top() == MID ? &m_root : (direStack.top() == LEFT ? &nodeStack.top(2)->lchild : &nodeStack.top(2)->rchild));
            if (lastDire == LEFT)
            {
                rotate(tmp2, p, RR);//对父结点做RR左旋
            }
            else
            {
                rotate(tmp2, p, LL);//对父结点做LL右旋
            }
            direStack.push(lastDire);
            direStack.push(lastDire);
            nodeStack.insert(nodeStack.getSize() - 1, tmp3);
            nodeStack.push(tmp);//树的形状改变后重新对顶替结点做判断
        }
        else if (tmp2->color == BLACK && tmp3->color == BLACK && getColor(tmp3->lchild) == BLACK && getColor(tmp3->rchild) == BLACK)
        {
            tmp3->color = RED;
        }
        else if (tmp2->color == RED && tmp3->color == BLACK && getColor(tmp3->lchild) == BLACK && getColor(tmp3->rchild) == BLACK)
        {
            tmp2->color = BLACK;
            tmp3->color = RED;
            break;
        }
        else if (tmp3->color == BLACK && (getColor(tmp3->lchild) == RED || getColor(tmp3->rchild) == RED))//兄弟结点的孩子里有红色结点
        {
            p = (direStack.top() == MID ? &m_root : (direStack.top() == LEFT ? &nodeStack.top(2)->lchild : &nodeStack.top(2)->rchild));
            if (lastDire == LEFT)
            {
                if (getColor(tmp3->rchild) == RED)
                {
                    //对父结点做RR左旋
                    *p = tmp3;
                    swapColor(tmp2->color, tmp3->color);
                    tmp3->rchild->color = BLACK;
                    tmp2->rchild = tmp3->lchild;
                    tmp3->lchild = tmp2;
                }
                else
                {
                    //对父结点做RL
                    tmp4 = tmp3->lchild;//兄弟结点的左孩子
                    *p = tmp4;
                    tmp4->color = BLACK;
                    swapColor(tmp2->color, tmp4->color);
                    tmp3->lchild = tmp4->rchild;
                    tmp4->rchild = tmp3;
                    tmp2->rchild = tmp4->lchild;
                    tmp4->lchild = tmp2;
                }
            }
            else
            {
                if (getColor(tmp3->lchild) == RED)
                {
                    //对父结点做LL左旋
                    *p = tmp3;
                    swapColor(tmp2->color, tmp3->color);
                    tmp3->lchild->color = BLACK;
                    tmp2->lchild = tmp3->rchild;
                    tmp3->rchild = tmp2;
                }
                else
                {
                    //对父结点做LR
                    tmp4 = tmp3->rchild;//兄弟结点的右孩子
                    *p = tmp4;
                    tmp4->color = BLACK;
                    swapColor(tmp2->color, tmp4->color);
                    tmp3->rchild = tmp4->lchild;
                    tmp4->lchild = tmp3;
                    tmp2->lchild = tmp4->rchild;
                    tmp4->rchild = tmp2;
                }
            }
            break;
        }
    }
}

template <typename Key, typename T>
void RedBlackTree<Key, T>::rotate(RedBlackTree<Key, T>::RedBlackTreeNode *root, RedBlackTree<Key, T>::RedBlackTreeNode **pchild, int mode)
{
    RedBlackTreeNode *tmp, *tmp2;
    switch (mode)
    {
    case LL:
        tmp = root->lchild;
        *pchild = tmp;
        tmp->color = BLACK;
        root->color = RED;
        root->lchild = tmp->rchild;
        tmp->rchild = root;
        break;
    case LR:
        tmp = root->lchild;
        tmp2 = tmp->rchild;
        *pchild = tmp2;
        tmp2->color = BLACK;
        root->color = RED;
        tmp->rchild = tmp2->lchild;
        tmp2->lchild = tmp;
        root->lchild = tmp2->rchild;
        tmp2->rchild = root;
        break;
    case RR:
        tmp = root->rchild;
        *pchild = tmp;
        tmp->color = BLACK;
        root->color = RED;
        root->rchild = tmp->lchild;
        tmp->lchild = root;
        break;
    case RL:
        tmp = root->rchild;
        tmp2 = tmp->lchild;
        *pchild = tmp2;
        tmp2->color = BLACK;
        root->color = RED;
        tmp->lchild = tmp2->rchild;
        tmp2->rchild = tmp;
        root->rchild = tmp2->lchild;
        tmp2->lchild = root;
        break;
    }
}

template <typename Key, typename T>
const T &RedBlackTree<Key, T>::value(const Key &key) const
{
    RedBlackTreeNode *tmp = m_root;
    while (tmp != NULL)
    {
        if (key == tmp->key)
        {
            return tmp->data;
        }
        else if (key < tmp->key)
        {
            tmp = tmp->lchild;
        }
        else if (key > tmp->key)
        {
            tmp = tmp->rchild;
        }
    }
    assert(tmp != NULL);
}

template <typename Key, typename T>
T &RedBlackTree<Key, T>::operator[](const Key &key)
{
    RedBlackTreeNode *tmp = m_root;
    while (tmp != NULL)
    {
        if (key == tmp->key)
        {
            return tmp->data;
        }
        else if (key < tmp->key)
        {
            tmp = tmp->lchild;
        }
        else if (key > tmp->key)
        {
            tmp = tmp->rchild;
        }
    }
    assert(tmp != NULL);
}

template <typename Key, typename T>
bool RedBlackTree<Key, T>::contains(const Key &key)
{
    RedBlackTreeNode *tmp = m_root;
    while (tmp != NULL)
    {
        if (key == tmp->key)
        {
            return true;
        }
        else if (key < tmp->key)
        {
            tmp = tmp->lchild;
        }
        else if (key > tmp->key)
        {
            tmp = tmp->rchild;
        }
    }
    return false;
}

template <typename Key, typename T>
void RedBlackTree<Key, T>::levelOrderTrav()
{
    LinkQueue<RedBlackTreeNode *> queue;
    if (m_root != NULL)
    {
        queue.enqueue(m_root);
    }
    RedBlackTreeNode *tmp;
    while (queue.getSize() > 0)
    {
        tmp = queue.dequeue();
        DEBUG << tmp->key;
        if (tmp->lchild != NULL)
            queue.enqueue(tmp->lchild);
        if (tmp->rchild != NULL)
            queue.enqueue(tmp->rchild);
    }
}

template <typename Key, typename T>
void RedBlackTree<Key, T>::preOrderTrav()
{
    RedBlackTree<Key, T>::preOrderTrav_R(m_root);
}

template <typename Key, typename T>
void RedBlackTree<Key, T>::inOrderTrav()
{
    RedBlackTree<Key, T>::inOrderTrav_R(m_root);
}

template <typename Key, typename T>
void RedBlackTree<Key, T>::postOrderTrav()
{
    RedBlackTree<Key, T>::postOrderTrav_R(m_root);
}

template <typename Key, typename T>
void RedBlackTree<Key, T>::print()
{
    QString start;
    LinkStack<RedBlackTreeNode *> nodeStack;
    LinkStack<int> levelStack;
    RedBlackTreeNode *node = m_root, *parent;
    int curLevel = 0, i;
    int len = (m_size < 256 ? 256 : m_size);
    int *endArr = new int[len];//保存各深度的节点是否到达末尾
    for (i = 0; i < len; i++)
        endArr[i] = 0;
    endArr[0] = 1;
    while (nodeStack.getSize() > 0 || node != NULL)
    {
        if (node != NULL)
        {
            if (curLevel == 0)//根节点
            {
                DEBUG << (node->color == RED ? "R " : "B ") << " " << node->key << " " << node->data;
            }
            else
            {
                start.clear();
                for (i = 1; i <= curLevel; i++)//打印出一行
                {
                    if (i == curLevel)
                    {
                        if (endArr[i] == 0)
                        {
                            start.append("├── ");
                        }
                        else
                        {
                            start.append("└── ");
                        }
                    }
                    else
                    {
                        if (endArr[i] == 0)
                        {
                            start.append("│   ");
                        }
                        else
                        {
                            start.append("    ");
                        }
                    }
                }
                DEBUG << start << (parent->lchild == node ? "l " : "r ") << (node->color == RED ? "R " : "B ") << node->key << " " << node->data;
            }
            nodeStack.push(node);
            levelStack.push(curLevel);
            curLevel++;
            if (node->rchild == NULL)//判断是不是最后一颗树
            {
                endArr[curLevel] = 1;
            }
            else
            {
                endArr[curLevel] = 0;
            }
            parent = node;
            node = node->lchild;
        }
        else
        {
            node = nodeStack.pop();
            curLevel = levelStack.pop();
            parent = node;
            node = node->rchild;
            curLevel++;
            endArr[curLevel] = 1;
        }
    }
    delete[] endArr;
}

template <typename Key, typename T>
void RedBlackTree<Key, T>::deleteTree(RedBlackTree<Key, T>::RedBlackTreeNode *root)
{
    if (root == NULL)
        return;
    deleteTree(root->lchild);
    deleteTree(root->rchild);
    delete root;
}

template <typename Key, typename T>
void RedBlackTree<Key, T>::copyTree(RedBlackTree<Key, T>::RedBlackTreeNode *&dstRoot, const RedBlackTree<Key, T>::RedBlackTreeNode *srcRoot)
{
    if (srcRoot != NULL)
    {
        dstRoot = new RedBlackTreeNode(srcRoot->key, srcRoot->data);
        dstRoot->color = srcRoot->color;
        copyTree(dstRoot->lchild, srcRoot->lchild);
        copyTree(dstRoot->rchild, srcRoot->rchild);
    }
}

template <typename Key, typename T>
int RedBlackTree<Key, T>::depth(RedBlackTree<Key, T>::RedBlackTreeNode *root)
{
    if (root == NULL)
        return 0;
    int depLeft = depth(root->lchild);
    int depRight = depth(root->rchild);
    return 1 + (depLeft > depRight ? depLeft : depRight);
}

template <typename Key, typename T>
void RedBlackTree<Key, T>::preOrderTrav_R(RedBlackTree<Key, T>::RedBlackTreeNode *node)
{
    if (node == NULL)
        return;
    DEBUG << node->key;
    preOrderTrav_R(node->lchild);//左子树
    preOrderTrav_R(node->rchild);//右子树
}

template <typename Key, typename T>
void RedBlackTree<Key, T>::inOrderTrav_R(RedBlackTree<Key, T>::RedBlackTreeNode *node)
{
    if (node == NULL)
        return;
    inOrderTrav_R(node->lchild);//左子树
    DEBUG << node->key;
    inOrderTrav_R(node->rchild);//右子树
}

template <typename Key, typename T>
void RedBlackTree<Key, T>::postOrderTrav_R(RedBlackTree<Key, T>::RedBlackTreeNode *node)
{
    if (node == NULL)
        return;
    postOrderTrav_R(node->lchild);//左子树
    postOrderTrav_R(node->rchild);//右子树
    DEBUG << node->key;
}

#endif // REDBLACKTREE_H
