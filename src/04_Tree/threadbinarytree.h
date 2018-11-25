#ifndef THREADBINARYTREE_H
#define THREADBINARYTREE_H

/*
标志域含义：
    ltag为0 表示lchild的左孩子
    ltag为1 表示lchild的前驱
    rtag为0 表示rchild的左孩子
    rtag为1 表示rchild的后继
*/
template <typename T>
class ThreadBinaryTree
{
public:
    class ThreadBinaryTreeNode
    {
    public:
        T data;
        ThreadBinaryTreeNode* lchild;
        ThreadBinaryTreeNode* rchild;
        int ltag, rtag;
    };

    ThreadBinaryTree(){}
};

#endif // THREADBINARYTREE_H
