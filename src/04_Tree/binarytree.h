#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "src/utils/tool.h"
#include "src/02_StackAndQueue/linkstack.h"
#include "src/02_StackAndQueue/linkqueue.h"

template <typename T>
class BinaryTree
{
public:
    class BinaryTreeNode
    {
    public:
        BinaryTreeNode() : lchild(NULL), rchild(NULL) {}
        BinaryTreeNode(const T &t) : data(t), lchild(NULL), rchild(NULL) {}
        T data;
        BinaryTreeNode *lchild;
        BinaryTreeNode *rchild;
    };
    BinaryTree();
    ~BinaryTree();
    int getSize();//元素个数
    void clear();
    int depth();
    int leafCount();//叶子结点个数
    BinaryTree<T>::BinaryTreeNode *root();
    void insert(const T &t);//找第一个空闲的标号位置插入
    void insert(int pos, const T &t);//根据标号插入，根节点标号为1
    void levelOrderTrav();//层次遍历
    void preOrderTrav();//先序遍历
    void inOrderTrav();//中序遍历
    void postOrderTrav();//后序遍历
    void print();

    static void deleteTree(BinaryTree<T>::BinaryTreeNode *root);
    static void copyTree(BinaryTree<T>::BinaryTreeNode *&dstRoot, const BinaryTree<T>::BinaryTreeNode *srcRoot);
    static int depth(BinaryTree<T>::BinaryTreeNode *root);
//    static int countLeaf(BinaryTree<T>::BinaryTreeNode *node);
    static void insert(BinaryTree<T>::BinaryTreeNode *&node , const T &t);//有序插入t
    static BinaryTree<T>::BinaryTreeNode *locate(BinaryTree<T>::BinaryTreeNode *node, int curPos, int pos);//定位结点
    static void preOrderTrav_R(BinaryTree<T>::BinaryTreeNode *node);//先序遍历
    static void inOrderTrav_R(BinaryTree<T>::BinaryTreeNode *node);//中序遍历
    static void postOrderTrav_R(BinaryTree<T>::BinaryTreeNode *node);//后序遍历

public:
    BinaryTreeNode *m_root;
    int m_size;
};

template <typename T>
BinaryTree<T>::BinaryTree()
{
    m_root = NULL;
    m_size = 0;
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    clear();
}

template <typename T>
int BinaryTree<T>::getSize()
{
    return m_size;
}

template <typename T>
void BinaryTree<T>::clear()
{
    BinaryTree<T>::deleteTree(m_root);
    m_root = NULL;
    m_size = 0;
}

template <typename T>
int BinaryTree<T>::depth()
{
    return BinaryTree::depth(m_root);
}

template <typename T>
int BinaryTree<T>::leafCount()
{
    return (m_size > 0 ? m_size + 1 : 0);
//    return BinaryTree<T>::countLeaf(m_root);
}

template <typename T>
typename BinaryTree<T>::BinaryTreeNode *BinaryTree<T>::root()
{
    return m_root;
}

template <typename T>
void BinaryTree<T>::insert(const T &t)
{
    BinaryTree<T>::insert(m_root, t);
    m_size++;
}

template <typename T>
void BinaryTree<T>::insert(int pos, const T &t)
{
    if (pos == 1 && m_root == NULL)
    {
        m_root = new BinaryTreeNode(t);
        m_size++;
        return;
    }

    int tmpPos = pos / 2;
    BinaryTreeNode *ret = locate(m_root, 1, tmpPos);
    if (ret != NULL)
    {
        if (pos % 2 == 0)
        {
            if (ret->lchild == NULL)
            {
                ret->lchild = new BinaryTreeNode(t);
                m_size++;
            }
        }
        else
        {
            if (ret->rchild == NULL)
            {
                ret->rchild = new BinaryTreeNode(t);
                m_size++;
            }
        }
    }
}

template <typename T>
void BinaryTree<T>::levelOrderTrav()
{
    LinkQueue<BinaryTreeNode *> queue;
    if (m_root != NULL)
    {
        queue.enqueue(m_root);
    }
    BinaryTreeNode *tmp;
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
void BinaryTree<T>::preOrderTrav()
{
    LinkStack<BinaryTreeNode *> stack;
    BinaryTreeNode *node = m_root;
//    while (stack.getSize() > 0 || node != NULL)
//    {
//        if (node != NULL)
//        {
//            DEBUG << node->data << " ";
//            stack.push(node);
//            node = node->lchild;
//        }
//        else
//        {
//            node = stack.pop();
//            node = node->rchild;
//        }
//    }

//    if (m_root != NULL)
//        stack.push(m_root);
//    BinaryTreeNode *tmp;
//    while (stack.getSize() > 0)
//    {
//        tmp = stack.pop();
//        DEBUG<<tmp->data<<" ";
//        if (tmp->rchild != NULL)
//            stack.push(tmp->rchild);
//        if (tmp->lchild != NULL)
//            stack.push(tmp->lchild);
//    }

    while (true)
    {
        while (node != NULL)//延左分支入栈
        {
            DEBUG << node->data << " ";
            if (node->rchild != NULL)
                stack.push(node->rchild);
            node = node->lchild;
        }
        if (stack.getSize() == 0)
            break;
        node = stack.pop();
    }
}

template <typename T>
void BinaryTree<T>::inOrderTrav()
{
    LinkStack<BinaryTreeNode *> stack;
    BinaryTreeNode *node = m_root;
//    while (stack.getSize() > 0 || node != NULL)
//    {
//        if (node != NULL)
//        {
//            stack.push(node);
//            node = node->lchild;
//        }
//        else
//        {
//            node = stack.pop();
//            DEBUG << node->data << " ";
//            node = node->rchild;
//        }
//    }

    while (true)
    {
        while (node != NULL)//延左分支入栈
        {
            stack.push(node);
            node = node->lchild;
        }
        if (stack.getSize() == 0)
            break;
        node = stack.pop();
        DEBUG << node->data << " ";
        node = node->rchild;
    }
}

template <typename T>
void BinaryTree<T>::postOrderTrav()
{
    LinkStack<BinaryTreeNode *> stack;
    BinaryTreeNode *node = m_root;
    BinaryTreeNode *tmp = NULL;
    while (stack.getSize() > 0 || node != NULL)
    {
        if (node != NULL)
        {
            stack.push(node);
            node = node->lchild;
        }
        else
        {
            node = stack.top();
            if (node->rchild != NULL && node->rchild != tmp)
            {
                node = node->rchild;
                stack.push(node);
                node = node->lchild;
            }
            else
            {
                DEBUG << node->data << " ";
                stack.pop();
                tmp = node;
                node = NULL;
            }
        }
    }
}

template <typename T>
void BinaryTree<T>::print()
{
    QString info = "\n", direction;
    LinkStack<BinaryTreeNode *> nodeStack;
    LinkStack<int> levelStack;
    BinaryTreeNode *node = m_root, *parent;
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
                    info.append(QString(node->data) + "\n");
                }
                else
                {
                    info.append(QString::number(node->data) + "\n");
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
                    info.append(direction + QString(node->data) + "\n");
                }
                else
                {
                    info.append(direction + QString::number(node->data) + "\n");
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
void BinaryTree<T>::deleteTree(BinaryTree<T>::BinaryTreeNode *root)
{
    if (root == NULL)
        return;
    deleteTree(root->lchild);
    deleteTree(root->rchild);
    delete root;
}

template <typename T>
void BinaryTree<T>::copyTree(BinaryTree<T>::BinaryTreeNode *&dstRoot, const BinaryTree<T>::BinaryTreeNode *srcRoot)
{
    if (srcRoot != NULL)
    {
        dstRoot = new BinaryTreeNode(srcRoot->data);
        copyTree(dstRoot->lchild, srcRoot->lchild);
        copyTree(dstRoot->rchild, srcRoot->rchild);
    }
}

template <typename T>
int BinaryTree<T>::depth(BinaryTree<T>::BinaryTreeNode *root)
{
    if (root == NULL)
        return 0;
    int depLeft = depth(root->lchild);
    int depRight = depth(root->rchild);
    return 1 + (depLeft > depRight ? depLeft : depRight);
}

//template <typename T>
//int BinaryTree<T>::countLeaf(BinaryTree<T>::BinaryTreeNode *node)
//{
//    if (node == NULL)
//        return 0;
//    if (node->lchild == NULL && node->rchild == NULL)
//        return 1;
//    return countLeaf(node->lchild) + countLeaf(node->rchild);
//}

template <typename T>
void BinaryTree<T>::insert(BinaryTree<T>::BinaryTreeNode *&node , const T &t)
{
    if (node == NULL)
    {
        node = new BinaryTreeNode(t);
        return;
    }
    if (t < node->data)
    {
        insert(node->lchild, t);
    }
    else if (t > node->data)
    {
        insert(node->rchild, t);
    }
}

template <typename T>
typename BinaryTree<T>::BinaryTreeNode *BinaryTree<T>::locate(BinaryTree<T>::BinaryTreeNode *node, int curPos, int pos)
{
    if (pos == 0 || node == NULL || pos < curPos)
        return NULL;
    if (pos == curPos)
        return node;
    BinaryTreeNode *p;
    p = locate(node->lchild, curPos * 2, pos);
    if (p == NULL)
    {
        p = locate(node->rchild, curPos * 2 + 1, pos);
    }
    return p;
}

template <typename T>
void BinaryTree<T>::preOrderTrav_R(BinaryTree<T>::BinaryTreeNode *node)
{
    if (node == NULL)
        return;
    DEBUG << node->data << " ";
    preOrderTrav_R(node->lchild);//左子树
    preOrderTrav_R(node->rchild);//右子树
}

template <typename T>
void BinaryTree<T>::inOrderTrav_R(BinaryTree<T>::BinaryTreeNode *node)
{
    if (node == NULL)
        return;
    inOrderTrav_R(node->lchild);//左子树
    DEBUG << node->data << " ";
    inOrderTrav_R(node->rchild);//右子树
}

template <typename T>
void BinaryTree<T>::postOrderTrav_R(BinaryTree<T>::BinaryTreeNode *node)
{
    if (node == NULL)
        return;
    postOrderTrav_R(node->lchild);//左子树
    postOrderTrav_R(node->rchild);//右子树
    DEBUG << node->data << " ";
}

#endif // BINARYTREE_H
