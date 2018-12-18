#ifndef THREADBINARYTREE_H
#define THREADBINARYTREE_H

#include "src/04_Tree/binarytree.h"

/*
线索二叉树（中序遍历）
标志域含义：
    ltag为0 表示lchild的左孩子
    ltag为1 表示lchild的前驱
    rtag为0 表示rchild的左孩子
    rtag为1 表示rchild的后继
m_head的左孩子指向root结点，右孩子指向中序遍历最后一个结点，为空树时左右孩子指向自身
*/
template <typename T>
class ThreadBinaryTree
{
public:
    class ThreadBinaryTreeNode
    {
    public:
        ThreadBinaryTreeNode() : lchild(NULL), rchild(NULL), ltag(0), rtag(0) {}
        ThreadBinaryTreeNode(const T &t) : data(t), lchild(NULL), rchild(NULL), ltag(0), rtag(0) {}
        T data;
        ThreadBinaryTreeNode *lchild;
        ThreadBinaryTreeNode *rchild;
        unsigned char ltag, rtag;
    };
    ThreadBinaryTree();
    ~ThreadBinaryTree();
    int getSize();
    void clear();
    int depth();
    ThreadBinaryTree<T>::ThreadBinaryTreeNode *root();
    void inOrderTrav();//中序遍历

    static void deleteTree(ThreadBinaryTree<T>::ThreadBinaryTreeNode *root);
    static int depth(ThreadBinaryTree<T>::ThreadBinaryTreeNode *root);
    static void BinTreeToThrBinTree(ThreadBinaryTree<T> &tbt, BinaryTree<T> &bt);//将二叉树转成线索二叉树
    static void copyFromBinTree(ThreadBinaryTree<T>::ThreadBinaryTreeNode *&dstRoot, const typename BinaryTree<T>::BinaryTreeNode *srcRoot);//从二叉树拷贝树的结构到线索二叉树
    static void inThreading(ThreadBinaryTree<T>::ThreadBinaryTreeNode *node);//二叉树线索化

public:
    ThreadBinaryTreeNode *m_head;
    int m_size;
    static ThreadBinaryTreeNode *m_pre;//线索化时记录刚访问过的结点，初始为NULL

};

template <typename T>
typename ThreadBinaryTree<T>::ThreadBinaryTreeNode *ThreadBinaryTree<T>::m_pre;

template <typename T>
ThreadBinaryTree<T>::ThreadBinaryTree()
{
    m_head = new ThreadBinaryTreeNode();
    m_head->lchild = m_head;
    m_head->ltag = 0;
    m_head->rchild = m_head;
    m_head->rtag = 1;
    m_size = 0;
}

template <typename T>
ThreadBinaryTree<T>::~ThreadBinaryTree()
{
    clear();
    delete m_head;
}

template <typename T>
int ThreadBinaryTree<T>::getSize()
{
    return m_size;
}

template <typename T>
void ThreadBinaryTree<T>::clear()
{
    if (m_size > 0)
    {
        ThreadBinaryTree<T>::deleteTree(m_head->lchild);
    }
    m_size = 0;
    m_head->lchild = m_head;
    m_head->rchild = m_head;
}

template <typename T>
int ThreadBinaryTree<T>::depth()
{
    if (m_size > 0)
    {
        return ThreadBinaryTree<T>::depth(m_head->lchild);
    }
    return 0;
}

template <typename T>
typename ThreadBinaryTree<T>::ThreadBinaryTreeNode *ThreadBinaryTree<T>::root()
{
    return m_head->lchild;
}

template <typename T>
void ThreadBinaryTree<T>::inOrderTrav()
{
    ThreadBinaryTreeNode *p = m_head->lchild;
    while (p != m_head)
    {
        while (p->ltag == 0)//找到最左边的树
        {
            p = p->lchild;
        }
        DEBUG<<p->data;
        while (p->rtag == 1 && p->rchild != m_head)//打印前驱，直到右子树不是前驱
        {
            p = p->rchild;
            DEBUG<<p->data;
        }
        p = p->rchild;//指向当前结点的右子树
    }
}

template <typename T>
void ThreadBinaryTree<T>::deleteTree(ThreadBinaryTree<T>::ThreadBinaryTreeNode *root)
{
    if (root == NULL)
        return;
    deleteTree(root->ltag == 0 ? root->lchild : NULL);
    deleteTree(root->rtag == 0 ? root->rchild : NULL);
    delete root;
}

template <typename T>
int ThreadBinaryTree<T>::depth(ThreadBinaryTree<T>::ThreadBinaryTreeNode *root)
{
    if (root == NULL)
        return 0;
    int depLeft = depth(root->ltag == 0 ? root->lchild : NULL);
    int depRight = depth(root->rtag == 0 ? root->rchild : NULL);
    return 1 + (depLeft > depRight ? depLeft : depRight);
}

template <typename T>
void ThreadBinaryTree<T>::BinTreeToThrBinTree(ThreadBinaryTree<T> &tbt, BinaryTree<T> &bt)
{
    copyFromBinTree(tbt.m_head->lchild, bt.m_root);
    tbt.m_size = bt.m_size;
    m_pre = NULL;//使用一个辅助全局变量
    inThreading(tbt.m_head->lchild);

    ThreadBinaryTreeNode *tmp = tbt.m_head->lchild;
    if (tmp != NULL)
    {
        while (tmp->lchild != NULL)
        {
            tmp = tmp->lchild;
        }
        tmp->ltag = 1;
        tmp->lchild = tbt.m_head;//最先遍历的结点的前驱指向头结点

        tmp = tbt.m_head->lchild;
        while (tmp->rchild != NULL)
        {
            tmp = tmp->rchild;
        }
        tmp->rtag = 1;
        tmp->rchild = tbt.m_head;//最后遍历的结点的前驱指向头结点
        tbt.m_head->rchild = tmp;//头结点的右子树指向最后遍历的结点
    }
}

template <typename T>
void ThreadBinaryTree<T>::copyFromBinTree(ThreadBinaryTree<T>::ThreadBinaryTreeNode *&dstRoot, const typename BinaryTree<T>::BinaryTreeNode *srcRoot)
{
    if (srcRoot != NULL)
    {
        dstRoot = new ThreadBinaryTreeNode(srcRoot->data);
        copyFromBinTree(dstRoot->lchild, srcRoot->lchild);
        copyFromBinTree(dstRoot->rchild, srcRoot->rchild);
    }
}

template <typename T>
void ThreadBinaryTree<T>::inThreading(ThreadBinaryTree<T>::ThreadBinaryTreeNode *node)
{
    if (node == NULL)
        return;
    inThreading(node->lchild);//线索化左子树
    if (node->lchild == NULL)//左子树为空，标记为前驱线索
    {
        node->ltag = 1;
        node->lchild = m_pre;
    }
    if (m_pre != NULL && m_pre->rchild == NULL)
    {
        m_pre->rtag = 1;
        m_pre->rchild = node;
    }
    m_pre = node;
    inThreading(node->rchild);//线索化右子树
}

#endif // THREADBINARYTREE_H
