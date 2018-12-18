#include "chapter4_part1.h"
#include "src/04_Tree/binarytree.h"
#include "src/04_Tree/threadbinarytree.h"

/*
二叉树demo
*/
void Chapter4_Part1::practice_000()
{
//    BinaryTree<int> bt1;
//    bt1.insert(20);
//    bt1.insert(15);
//    bt1.insert(7);
//    bt1.insert(30);
//    bt1.insert(2);
//    bt1.insert(25);
//    bt1.insert(11);
//    BinaryTree<int>::preOrderTrav_R(bt1.root());
//    DEBUG<<"--------------------";
//    BinaryTree<int>::inOrderTrav_R(bt1.root());
//    DEBUG<<"--------------------";
//    bt1.inOrderTrav();
//    DEBUG<<"--------------------";
//    BinaryTree<int>::postOrderTrav_R(bt1.root());
//    DEBUG<<"--------------------";

    BinaryTree<int> bt2;
    bt2.insert(1, 2);
    bt2.insert(3, 4);
    bt2.insert(2, 10);
    bt2.insert(4, 11);
    bt2.insert(5, 0);
    bt2.insert(5, 999);//插入失败
    bt2.insert(13, 999);//插入失败
    bt2.insert(10, 23);
    BinaryTree<int>::preOrderTrav_R(bt2.root());
    DEBUG<<"--------------------";
    bt2.preOrderTrav();
    DEBUG<<"--------------------";
//    BinaryTree<int>::inOrderTrav_R(bt2.root());
//    DEBUG<<"--------------------";
//    bt2.inOrderTrav();
//    DEBUG<<"--------------------";
//    BinaryTree<int>::postOrderTrav_R(bt2.root());
//    DEBUG<<"--------------------";
//    bt2.postOrderTrav();
//    DEBUG<<"--------------------";
    DEBUG << "叶子节点个数: " << bt2.leafCount();
    DEBUG << "深度: " << bt2.depth();
//    bt2.levelOrderTrav();

//    BinaryTree<int> bt3;
//    BinaryTree<int>::copyTree(bt3.m_root, bt2.root());
//    BinaryTree<int>::postOrderTrav_R(bt3.root());
//    DEBUG<<"--------------------";
//    bt3.postOrderTrav();
//    DEBUG<<"--------------------";
//    DEBUG << "叶子节点个数: " << bt3.leafCount();
    //    DEBUG << "深度: " << bt3.depth();
}

/*
线索二叉树demo
*/
void Chapter4_Part1::practice_001()
{
    BinaryTree<char> bt1;
    ThreadBinaryTree<char> tbt1;

    bt1.insert(1, 'A');
    bt1.insert(2, 'B');
    bt1.insert(3, 'C');
    bt1.insert(4, 'D');
    bt1.insert(5, 'E');
    bt1.insert(6, 'F');
    bt1.insert(7, 'G');
    bt1.insert(8, 'H');
    bt1.insert(15, 'I');
    DEBUG<<"bt1 size:"<<bt1.getSize();
    DEBUG<<"bt1 depth:"<<bt1.depth();
    bt1.inOrderTrav();

    DEBUG<<"--------------------";
    ThreadBinaryTree<char>::BinTreeToThrBinTree(tbt1, bt1);
    DEBUG<<"tbt1 size:"<<tbt1.getSize();
    DEBUG<<"tbt1 depth:"<<tbt1.depth();
    tbt1.inOrderTrav();

}
