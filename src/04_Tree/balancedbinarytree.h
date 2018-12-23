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
    void balance(BalancedBinaryTree<T>::BalancedBinaryTreeNode *root, BalancedBinaryTree<T>::BalancedBinaryTreeNode **pchild, int mode);//平衡化，pchild为root的引用
    bool contains(const T &t);//查找一个元素，存在返回true，不存在返回false
    void levelOrderTrav();//层次遍历
    void preOrderTrav();//先序遍历
    void inOrderTrav();//中序遍历
    void postOrderTrav();//后序遍历
    void print();

    static void deleteTree(BalancedBinaryTree<T>::BalancedBinaryTreeNode *root);
    static void copyTree(BalancedBinaryTree<T>::BalancedBinaryTreeNode *&dstRoot, const BalancedBinaryTree<T>::BalancedBinaryTreeNode *srcRoot);
    static int depth(BalancedBinaryTree<T>::BalancedBinaryTreeNode *root);
    static BalancedBinaryTree<T>::BalancedBinaryTreeNode *locate(BalancedBinaryTree<T>::BalancedBinaryTreeNode *node, int curPos, int pos);//定位结点
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
    return BalancedBinaryTree::depth(m_root);
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
    SeqStack<BalancedBinaryTreeNode *> stack;//保存从根结点到插入结点路径的栈
    BalancedBinaryTreeNode *tmp = m_root, *tmp2;
    BalancedBinaryTreeNode **p;
    bool isIncreaseHeight = true;
    while (tmp != NULL)//查找要插入的结点和路径
    {
        stack.push(tmp);
        if (t == tmp->data)
        {
            return;
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
    tmp = stack.top();
    if (t < tmp->data)
    {
        tmp->lchild = new BalancedBinaryTreeNode(t);
    }
    else
    {
        tmp->rchild = new BalancedBinaryTreeNode(t);
    }
    while (isIncreaseHeight && stack.getSize() > 0)//重新平衡二叉树
    {
        tmp = stack.pop();
        switch (tmp->bf)
        {
        case 1:
            if (t < tmp->data)
            {
                if (stack.getSize() > 0)
                {
                    tmp2 = stack.pop();
                    if (t < tmp2->data)
                    {
                        p = &tmp2->lchild;
                    }
                    else
                    {
                        p = &tmp2->rchild;
                    }
                }
                else
                    p = &m_root;
                if (t < tmp->lchild->data)//LL
                {
                    balance(tmp, p, LL);
                }
                else if (t > tmp->lchild->data)//LR
                {
                    balance(tmp, p, LR);
                }
            }
            else
            {
                tmp->bf = 0;
            }
            isIncreaseHeight = false;
            break;
        case 0:
            if (t < tmp->data)
            {
                tmp->bf = 1;
            }
            else
            {
                tmp->bf = -1;
            }
            break;
        case -1:
            if (t < tmp->data)
            {
                tmp->bf = 0;
            }
            else
            {
                if (stack.getSize() > 0)
                {
                    tmp2 = stack.pop();
                    if (t < tmp2->data)
                    {
                        p = &tmp2->lchild;
                    }
                    else
                    {
                        p = &tmp2->rchild;
                    }
                }
                else
                    p = &m_root;
                if (t < tmp->rchild->data)//RL
                {
                    balance(tmp, p, RL);
                }
                else if (t > tmp->rchild->data)//RR
                {
                    balance(tmp, p, RR);
                }
            }
            isIncreaseHeight = false;
            break;
        }
    }
    m_size++;
}

/*
删除元素：
    当删除的结点为叶子结点或左右子树有一个为NULL时可以直接删除，当删除的结点左右子树都不为空时。
        如果左子树深度>=右子树深度，
        从左子树中找到最大的元素结点给删除的结点元素赋值，之后删除左子树最大的那个结点；
        如果左子树深度<右子树深度，
        从右子树中找到最大的元素结点给删除的结点元素赋值，之后删除右子树最大的那个结点。
    结点删除后需要重新平衡删除结点路径上的树。
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
    SeqStack<BalancedBinaryTreeNode *> stack;//保存从根结点到删除结点路径的栈
    BalancedBinaryTreeNode *tmp = m_root, *tmp2, *tmp3;
    BalancedBinaryTreeNode **p;
    bool isDecreaseHeight = true, fromLeft;
    while (tmp != NULL)//查找要删除的结点和路径
    {
        stack.push(tmp);
        if (t == tmp->data)
        {
            break;
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
    if (tmp == NULL)
        return;
    tmp = stack.top();
    if (tmp->lchild != NULL && tmp->rchild != NULL)//删除的结点左右孩子结点都不为空时，重定删除位置
    {
        switch (tmp->bf)
        {
        case 1://平衡因子为1或0时，从左子树中找最大的元素与删除元素做交换
        case 0:
            tmp2 = tmp->lchild;
            while (tmp2 != NULL)
            {
                stack.push(tmp2);
                tmp2 = tmp2->rchild;
            }
            break;
        case -1://平衡因子为-1时，从右子树中找最小的元素与删除元素做交换
            tmp2 = tmp->rchild;
            while (tmp2 != NULL)
            {
                stack.push(tmp2);
                tmp2 = tmp2->lchild;
            }
            break;
        }
        tmp2 = stack.top();
        tmp->data = tmp2->data;
    }

    tmp = stack.pop();
    tmp2 = stack.top();
    if (tmp->lchild == NULL && tmp->rchild == NULL)//删除结点
    {
        if (tmp2->lchild == tmp)
        {
            tmp2->lchild = NULL;
            fromLeft = true;
        }
        else
        {
            tmp2->rchild = NULL;
            fromLeft = false;
        }
        delete tmp;
    }
    else if (tmp->lchild != NULL && tmp->rchild == NULL)
    {
        if (tmp2->lchild == tmp)
        {
            tmp2->lchild = tmp->lchild;
            fromLeft = true;
        }
        else
        {
            tmp2->rchild = tmp->lchild;
            fromLeft = false;
        }
        delete tmp;
    }
    else if (tmp->lchild == NULL && tmp->rchild != NULL)
    {
        if (tmp2->lchild == tmp)
        {
            tmp2->lchild = tmp->rchild;
            fromLeft = true;
        }
        else
        {
            tmp2->rchild = tmp->rchild;
            fromLeft = false;
        }
        delete tmp;
    }

    while (isDecreaseHeight && stack.getSize() > 0)//重新平衡二叉树
    {
        tmp = stack.pop();
        switch (tmp->bf)
        {
        case 1:
            if (fromLeft)
            {
                tmp->bf = 0;
                if (stack.getSize() > 0)
                {
                    fromLeft = stack.top()->lchild == tmp;
                }
            }
            else
            {
                if (stack.getSize() > 0)
                {
                    tmp3 = stack.pop();
                    if (tmp3->lchild == tmp)
                    {
                        p = &tmp3->lchild;
                    }
                    else
                    {
                        p = &tmp3->rchild;
                    }
                }
                else
                    p = &m_root;
                tmp2 = tmp->lchild;
                switch (tmp2->bf)
                {
                case 1:
                case 0:
                    balance(tmp, p, LL);
                    break;
                case -1:
                    balance(tmp, p, LR);
                    break;
                }
                isDecreaseHeight = false;
            }
            break;
        case 0:
            if (fromLeft)
            {
                tmp->bf = -1;
            }
            else
            {
                tmp->bf = 1;
            }
            isDecreaseHeight = false;
            break;
        case -1:
            if (fromLeft)
            {
                if (stack.getSize() > 0)
                {
                    tmp3 = stack.pop();
                    if (tmp3->lchild == tmp)
                    {
                        p = &tmp3->lchild;
                    }
                    else
                    {
                        p = &tmp3->rchild;
                    }
                }
                else
                    p = &m_root;
                tmp2 = tmp->rchild;
                switch (tmp2->bf)
                {
                case -1:
                case 0:
                    balance(tmp, p, RR);
                    break;
                case 1:
                    balance(tmp, p, RL);
                    break;
                }
                isDecreaseHeight = false;
            }
            else
            {
                tmp->bf = 0;
                if (stack.getSize() > 0)
                {
                    fromLeft = stack.top()->lchild == tmp;
                }
            }
            break;
        }
    }
    m_size--;
}

template <typename T>
void BalancedBinaryTree<T>::balance(BalancedBinaryTree<T>::BalancedBinaryTreeNode *root, BalancedBinaryTree<T>::BalancedBinaryTreeNode **pchild, int mode)
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
    QString info = "\n", direction;
    LinkStack<BalancedBinaryTreeNode *> nodeStack;
    LinkStack<int> levelStack;
    BalancedBinaryTreeNode *node = m_root, *parent;
    int curLevel = 0, i;
    int endArr[1024] = {0};//保存各深度的节点是否到达末尾
    endArr[0] = 1;
    while (nodeStack.getSize() > 0 || node != NULL)
    {
        if (node != NULL)
        {
            if (curLevel == 0)//根节点
            {
                if (is_char<T>())
                {
                    info.append(QString("%1 ").arg(node->bf) + QString(node->data) + "\n");
                }
                else
                {
                    info.append(QString("%1 ").arg(node->bf) + QString::number(node->data) + "\n");
                }
            }
            else
            {
                for (i = 1; i <= curLevel; i++)//打印出一行
                {
                    if (i == curLevel)
                    {
                        if (endArr[i] == 0)
                        {
                            info.append("├── ");
                        }
                        else
                        {
                            info.append("└── ");
                        }
                    }
                    else
                    {
                        if (endArr[i] == 0)
                        {
                            info.append("│   ");
                        }
                        else
                        {
                            info.append("    ");
                        }
                    }
                }
                direction = (parent->lchild == node ? "l " : "r ");
                if (is_char<T>())
                {
                    info.append(direction + QString("%1 ").arg(node->bf) + QString(node->data) + "\n");
                }
                else
                {
                    info.append(direction + QString("%1 ").arg(node->bf) + QString::number(node->data) + "\n");
                }
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
//    DEBUG << info;
    QStringList list = info.split('\n');
    for (i = 0; i < list.count(); i++)
    {
        if (!list.at(i).isEmpty())
            DEBUG << list.at(i);
    }
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
typename BalancedBinaryTree<T>::BalancedBinaryTreeNode *BalancedBinaryTree<T>::locate(BalancedBinaryTree<T>::BalancedBinaryTreeNode *node, int curPos, int pos)
{
    if (pos == 0 || node == NULL || pos < curPos)
        return NULL;
    if (pos == curPos)
        return node;
    BalancedBinaryTreeNode *p;
    p = locate(node->lchild, curPos * 2, pos);
    if (p == NULL)
    {
        p = locate(node->rchild, curPos * 2 + 1, pos);
    }
    return p;
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
