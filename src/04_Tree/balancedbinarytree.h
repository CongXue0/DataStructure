#ifndef BALANCEDBINARYTREE_H
#define BALANCEDBINARYTREE_H

#include "src/utils/tool.h"
#include "src/02_StackAndQueue/linkstack.h"
#include "src/02_StackAndQueue/linkqueue.h"
#include "src/02_StackAndQueue/seqstack.h"

#define AVLTree BalancedBinaryTree

/*
平衡二叉树（AVL树）
平衡二叉树的任意结点的左右子树高度差<=1，平衡二叉树左子树所有结点元素均小于当前结点元素，
    平衡二叉树右子树所有结点元素均大于当前结点元素
*/
template <typename T>
class BalancedBinaryTree
{
public:
    enum DIRECTION
    {
        MID, LEFT, RIGHT
    };
    enum ROTATE
    {
        LL, LR, RR, RL
    };
    class BalancedBinaryTreeNode
    {
    public:
        BalancedBinaryTreeNode() : bf(0), lchild(NULL), rchild(NULL) {}
        BalancedBinaryTreeNode(const T &t) : data(t), bf(0), lchild(NULL), rchild(NULL) {}
        T data;
        int bf;//平衡因子 左子树深度减去右子树深度
        BalancedBinaryTreeNode *lchild;
        BalancedBinaryTreeNode *rchild;
    };
    BalancedBinaryTree();
    ~BalancedBinaryTree();
    int getSize();//元素个数
    void clear();
    int depth();
    int leafCount();//叶子结点个数
    BalancedBinaryTree<T>::BalancedBinaryTreeNode *root();
    void append(const T &t);//往集合中添加元素t
    void remove(const T &t);//删除等于t的元素
    void rotate(BalancedBinaryTree<T>::BalancedBinaryTreeNode *root, BalancedBinaryTree<T>::BalancedBinaryTreeNode **pchild, int mode);//对root做旋转操作，pchild为root的引用
    bool contains(const T &t);//查找一个元素，存在返回true，不存在返回false
    void levelOrderTrav();//层次遍历
    void preOrderTrav();//先序遍历
    void inOrderTrav();//中序遍历
    void postOrderTrav();//后序遍历
    void print();

    static void deleteTree(BalancedBinaryTree<T>::BalancedBinaryTreeNode *root);
    static void copyTree(BalancedBinaryTree<T>::BalancedBinaryTreeNode *&dstRoot, const BalancedBinaryTree<T>::BalancedBinaryTreeNode *srcRoot);
    static int depth(BalancedBinaryTree<T>::BalancedBinaryTreeNode *root);
    static void preOrderTrav_R(BalancedBinaryTree<T>::BalancedBinaryTreeNode *node);//先序遍历
    static void inOrderTrav_R(BalancedBinaryTree<T>::BalancedBinaryTreeNode *node);//中序遍历
    static void postOrderTrav_R(BalancedBinaryTree<T>::BalancedBinaryTreeNode *node);//后序遍历

public:
    BalancedBinaryTreeNode *m_root;
    int m_size;
};

template <typename T>
BalancedBinaryTree<T>::BalancedBinaryTree()
{
    m_root = NULL;
    m_size = 0;
}

template <typename T>
BalancedBinaryTree<T>::~BalancedBinaryTree()
{
    clear();
}

template <typename T>
int BalancedBinaryTree<T>::getSize()
{
    return m_size;
}

template <typename T>
void BalancedBinaryTree<T>::clear()
{
    BalancedBinaryTree<T>::deleteTree(m_root);
    m_root = NULL;
    m_size = 0;
}

template <typename T>
int BalancedBinaryTree<T>::depth()
{
    return BalancedBinaryTree<T>::depth(m_root);
}

template <typename T>
int BalancedBinaryTree<T>::leafCount()
{
    return (m_size > 0 ? m_size + 1 : 0);
}

template <typename T>
typename BalancedBinaryTree<T>::BalancedBinaryTreeNode *BalancedBinaryTree<T>::root()
{
    return m_root;
}

/*
插入元素：
    1. 先找到要插入的位置插入元素
    2. 自下而上更新路径上结点的bf平衡因子，直到找到第一颗需要旋转的树的结点进行旋转操作
        ，或者更新完路径上所有平衡因子
    3. 当前结点的平衡被改变，当左子树深度与右子树深度的差值绝对值大于1时需要做旋转。
        当左子树深度增长1：（1）增长方向来源于左子树的左孩子，对当前结点使用LL操作。（2）增长方向来源于左子树的右孩子，对当前结点使用LR操作。
*/
template <typename T>
void BalancedBinaryTree<T>::append(const T &t)
{
    if (m_root == NULL)
    {
        m_root = new BalancedBinaryTreeNode(t);
        m_size++;
        return;
    }
    SeqStack<BalancedBinaryTreeNode *> nodeStack;//保存从根结点到插入结点路径的栈
    SeqStack<DIRECTION> direStack;//保存从根结点到插入结点路径方向的栈
    DIRECTION lastDire;
    BalancedBinaryTreeNode *tmp = m_root, *tmp2;
    BalancedBinaryTreeNode **p;
    bool isIncreaseHeight = true;

    direStack.push(MID);
    while (tmp != NULL)//查找要插入的结点和路径
    {
        nodeStack.push(tmp);
        if (t == tmp->data)
        {
            return;
        }
        else if (t < tmp->data)
        {
            tmp = tmp->lchild;
            direStack.push(LEFT);
        }
        else if (t > tmp->data)
        {
            tmp = tmp->rchild;
            direStack.push(RIGHT);
        }
    }
    tmp = nodeStack.top();
    if (direStack.top() == LEFT)
    {
        tmp->lchild = new BalancedBinaryTreeNode(t);
        nodeStack.push(tmp->lchild);
    }
    else
    {
        tmp->rchild = new BalancedBinaryTreeNode(t);
        nodeStack.push(tmp->rchild);
    }
    m_size++;
    while (isIncreaseHeight && nodeStack.getSize() > 1)//重新平衡二叉树
    {
        tmp = nodeStack.pop();//增长结点
        tmp2 = nodeStack.top();//父节点
        switch (tmp2->bf)
        {
        case 1:
            if (direStack.top(1) == LEFT)
            {
                p = (direStack.top(2) == MID ? &m_root : (direStack.top(2) == LEFT ? &nodeStack.top(2)->lchild : &nodeStack.top(2)->rchild));//父节点的引用
                if (lastDire == LEFT)//LL
                {
                    rotate(tmp2, p, LL);
                }
                else//LR
                {
                    rotate(tmp2, p, LR);
                }
            }
            else
            {
                tmp2->bf = 0;
            }
            isIncreaseHeight = false;
            break;
        case 0:
            if (direStack.top(1) == LEFT)
            {
                tmp2->bf = 1;
            }
            else
            {
                tmp2->bf = -1;
            }
            break;
        case -1:
            if (direStack.top(1) == LEFT)
            {
                tmp2->bf = 0;
            }
            else
            {
                p = (direStack.top(2) == MID ? &m_root : (direStack.top(2) == LEFT ? &nodeStack.top(2)->lchild : &nodeStack.top(2)->rchild));//父节点的引用
                if (lastDire == LEFT)//RL
                {
                    rotate(tmp2, p, RL);
                }
                else//RR
                {
                    rotate(tmp2, p, RR);
                }
            }
            isIncreaseHeight = false;
            break;
        }
        lastDire = direStack.pop();
    }
}

/*
删除元素：
    1. 当删除的结点为叶子结点或左右子树有一个为NULL时可以直接删除，当删除的结点左右子树都不为空时。
        如果左子树深度>=右子树深度，
        从左子树中找到最大的元素结点给删除的结点元素赋值，之后删除左子树最大的那个结点；
        如果左子树深度<右子树深度，
        从右子树中找到最大的元素结点给删除的结点元素赋值，之后删除右子树最大的那个结点。
    2. 结点删除后需要重新平衡删除结点路径上的树。
    3. 从删除路径上更新结点的平衡因子，如果新的平衡因子的绝对值大于1意味着平衡被打破需要做旋转。
        当前结点的平衡因子为2（左子树比右子树长2）需要做旋转：（1）左子树的平衡因子为1或0，对当前结点使用LL操作。（2）左子树的平衡因子为-1，对当前结点使用LR操作。
        当前结点的平衡因子为-2（右子树比左子树长2）需要做旋转：（1）右子树的平衡因子为-1或0，对当前结点使用RR操作。（2）左子树的平衡因子为1，对当前结点使用RL操作。
*/
template <typename T>
void BalancedBinaryTree<T>::remove(const T &t)
{
    if (m_size <= 1)
    {
        if (m_root != NULL && m_root->data == t)
        {
            delete m_root;
            m_root = NULL;
            m_size--;
        }
        return;
    }
    SeqStack<BalancedBinaryTreeNode *> nodeStack;//保存从根结点到删除结点路径的栈
    SeqStack<DIRECTION> direStack;//保存从根结点到插入结点路径方向的栈
    DIRECTION lastDire;
    BalancedBinaryTreeNode *tmp = m_root, *tmp2;
    BalancedBinaryTreeNode **p;
    bool isDecreaseHeight = true;

    direStack.push(MID);
    while (tmp != NULL)//查找要删除的结点和路径
    {
        nodeStack.push(tmp);
        if (t == tmp->data)
        {
            break;
        }
        else if (t < tmp->data)
        {
            tmp = tmp->lchild;
            direStack.push(LEFT);
        }
        else if (t > tmp->data)
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
        switch (tmp->bf)
        {
        case 1://平衡因子为1或0时，从左子树中找最大的元素与删除元素做交换
        case 0:
            tmp2 = tmp->lchild;
            direStack.push(LEFT);
            while (tmp2 != NULL)
            {
                nodeStack.push(tmp2);
                tmp2 = tmp2->rchild;
                direStack.push(RIGHT);
            }
            direStack.pop();
            break;
        case -1://平衡因子为-1时，从右子树中找最小的元素与删除元素做交换
            tmp2 = tmp->rchild;
            direStack.push(RIGHT);
            while (tmp2 != NULL)
            {
                nodeStack.push(tmp2);
                tmp2 = tmp2->lchild;
                direStack.push(LEFT);
            }
            direStack.pop();
            break;
        }
        tmp2 = nodeStack.top();
        tmp->data = tmp2->data;
    }

    tmp = nodeStack.pop();//待删除结点
    lastDire = direStack.pop();
    if (lastDire == MID)
    {
        m_root = (tmp->lchild != NULL ? tmp->lchild : tmp->rchild);
    }
    else
    {
        tmp2 = nodeStack.top();//父结点
        if (lastDire == LEFT)
        {
            tmp2->lchild = (tmp->lchild != NULL ? tmp->lchild : tmp->rchild);
        }
        else
        {
            tmp2->rchild = (tmp->lchild != NULL ? tmp->lchild : tmp->rchild);
        }
    }
    delete tmp;
    m_size--;

    while (isDecreaseHeight && nodeStack.getSize() > 0)//重新平衡二叉树
    {
        tmp2 = nodeStack.pop();
        switch (tmp2->bf)
        {
        case 1:
            if (lastDire == LEFT)
            {
                tmp2->bf = 0;
                lastDire = direStack.pop();
            }
            else
            {
                lastDire = direStack.pop();
                p = (lastDire == MID ? &m_root : (lastDire == LEFT ? &nodeStack.top()->lchild : &nodeStack.top()->rchild));//tmp2的引用
                tmp = tmp2->lchild;
                switch (tmp->bf)
                {
                case 1:
                case 0:
                    rotate(tmp2, p, LL);
                    break;
                case -1:
                    rotate(tmp2, p, LR);
                    break;
                }
                isDecreaseHeight = false;
            }
            break;
        case 0:
            if (lastDire == LEFT)
            {
                tmp2->bf = -1;
            }
            else
            {
                tmp2->bf = 1;
            }
            isDecreaseHeight = false;
            break;
        case -1:
            if (lastDire == LEFT)
            {
                lastDire = direStack.pop();
                p = (lastDire == MID ? &m_root : (lastDire == LEFT ? &nodeStack.top()->lchild : &nodeStack.top()->rchild));//tmp2的引用
                tmp = tmp2->rchild;
                switch (tmp->bf)
                {
                case -1:
                case 0:
                    rotate(tmp2, p, RR);
                    break;
                case 1:
                    rotate(tmp2, p, RL);
                    break;
                }
                isDecreaseHeight = false;
            }
            else
            {
                tmp2->bf = 0;
                lastDire = direStack.pop();
            }
            break;
        }
    }
}

template <typename T>
void BalancedBinaryTree<T>::rotate(BalancedBinaryTree<T>::BalancedBinaryTreeNode *root, BalancedBinaryTree<T>::BalancedBinaryTreeNode **pchild, int mode)
{
    BalancedBinaryTreeNode *tmp, *tmp2;
    switch (mode)
    {
    case LL:
        tmp = root->lchild;
        *pchild = tmp;
        tmp->bf = 0;
        root->bf = 0;
        root->lchild = tmp->rchild;
        tmp->rchild = root;
        break;
    case LR:
        tmp = root->lchild;
        tmp2 = tmp->rchild;
        *pchild = tmp2;
        if (tmp2->bf == 0)
        {
            tmp2->bf = 0;
            tmp->bf = 0;
            root->bf = 0;
        }
        else if (tmp2->bf == 1)
        {
            tmp2->bf = 0;
            tmp->bf = 0;
            root->bf = -1;
        }
        else if (tmp2->bf == -1)
        {
            tmp2->bf = 0;
            tmp->bf = 1;
            root->bf = 0;
        }
        tmp->rchild = tmp2->lchild;
        tmp2->lchild = tmp;
        root->lchild = tmp2->rchild;
        tmp2->rchild = root;
        break;
    case RR:
        tmp = root->rchild;
        *pchild = tmp;
        tmp->bf = 0;
        root->bf = 0;
        root->rchild = tmp->lchild;
        tmp->lchild = root;
        break;
    case RL:
        tmp = root->rchild;
        tmp2 = tmp->lchild;
        *pchild = tmp2;
        if (tmp2->bf == 0)
        {
            tmp2->bf = 0;
            tmp->bf = 0;
            root->bf = 0;
        }
        else if (tmp2->bf == 1)
        {
            tmp2->bf = 0;
            tmp->bf = -1;
            root->bf = 0;
        }
        else if (tmp2->bf == -1)
        {
            tmp2->bf = 0;
            tmp->bf = 0;
            root->bf = 1;
        }
        tmp->lchild = tmp2->rchild;
        tmp2->rchild = tmp;
        root->rchild = tmp2->lchild;
        tmp2->lchild = root;
        break;
    }
}

template <typename T>
bool BalancedBinaryTree<T>::contains(const T &t)
{
    BalancedBinaryTreeNode *tmp = m_root;
    while (tmp != NULL)
    {
        if (t == tmp->data)
        {
            return true;
        }
        else if (t < tmp->data)
        {
            tmp = tmp->lchild;
        }
        else if (t > tmp->data)
        {
            tmp = tmp->rchild;
        }
    }
    return false;
}

template <typename T>
void BalancedBinaryTree<T>::levelOrderTrav()
{
    LinkQueue<BalancedBinaryTreeNode *> queue;
    if (m_root != NULL)
    {
        queue.enqueue(m_root);
    }
    BalancedBinaryTreeNode *tmp;
    while (queue.getSize() > 0)
    {
        tmp = queue.dequeue();
        DEBUG << tmp->data << " ";
        if (tmp->lchild != NULL)
            queue.enqueue(tmp->lchild);
        if (tmp->rchild != NULL)
            queue.enqueue(tmp->rchild);
    }
}

template <typename T>
void BalancedBinaryTree<T>::preOrderTrav()
{
    BalancedBinaryTree<T>::preOrderTrav_R(m_root);
}

template <typename T>
void BalancedBinaryTree<T>::inOrderTrav()
{
    BalancedBinaryTree<T>::inOrderTrav_R(m_root);
}

template <typename T>
void BalancedBinaryTree<T>::postOrderTrav()
{
    BalancedBinaryTree<T>::postOrderTrav_R(m_root);
}

template <typename T>
void BalancedBinaryTree<T>::print()
{
    QString start;
    LinkStack<BalancedBinaryTreeNode *> nodeStack;
    LinkStack<int> levelStack;
    BalancedBinaryTreeNode *node = m_root, *parent;
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
                DEBUG << node->bf << " " << node->data;
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
                DEBUG << start << (parent->lchild == node ? "l " : "r ") << node->bf << " " << node->data;
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

template <typename T>
void BalancedBinaryTree<T>::deleteTree(BalancedBinaryTree<T>::BalancedBinaryTreeNode *root)
{
    if (root == NULL)
        return;
    deleteTree(root->lchild);
    deleteTree(root->rchild);
    delete root;
}

template <typename T>
void BalancedBinaryTree<T>::copyTree(BalancedBinaryTree<T>::BalancedBinaryTreeNode *&dstRoot, const BalancedBinaryTree<T>::BalancedBinaryTreeNode *srcRoot)
{
    if (srcRoot != NULL)
    {
        dstRoot = new BalancedBinaryTreeNode(srcRoot->data);
        dstRoot->bf = srcRoot->bf;
        copyTree(dstRoot->lchild, srcRoot->lchild);
        copyTree(dstRoot->rchild, srcRoot->rchild);
    }
}

template <typename T>
int BalancedBinaryTree<T>::depth(BalancedBinaryTree<T>::BalancedBinaryTreeNode *root)
{
    if (root == NULL)
        return 0;
    int depLeft = depth(root->lchild);
    int depRight = depth(root->rchild);
    return 1 + (depLeft > depRight ? depLeft : depRight);
}

template <typename T>
void BalancedBinaryTree<T>::preOrderTrav_R(BalancedBinaryTree<T>::BalancedBinaryTreeNode *node)
{
    if (node == NULL)
        return;
    DEBUG << node->data << " ";
    preOrderTrav_R(node->lchild);//左子树
    preOrderTrav_R(node->rchild);//右子树
}

template <typename T>
void BalancedBinaryTree<T>::inOrderTrav_R(BalancedBinaryTree<T>::BalancedBinaryTreeNode *node)
{
    if (node == NULL)
        return;
    inOrderTrav_R(node->lchild);//左子树
    DEBUG << node->data << " ";
    inOrderTrav_R(node->rchild);//右子树
}

template <typename T>
void BalancedBinaryTree<T>::postOrderTrav_R(BalancedBinaryTree<T>::BalancedBinaryTreeNode *node)
{
    if (node == NULL)
        return;
    postOrderTrav_R(node->lchild);//左子树
    postOrderTrav_R(node->rchild);//右子树
    DEBUG << node->data << " ";
}

#endif // BALANCEDBINARYTREE_H
