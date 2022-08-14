// Red_Black_tree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
//#include "RB_tree.h"
//#include "RB_tree.cpp"

#include "RB_tree_with_size.h"
#include "RB_tree_with_size.cpp"

int main()
{
    RB_tree_with_size<int> tree(-1);
    tree.RB_Insert(5);
    tree.RB_Insert(34);
    tree.RB_Insert(256);
    tree.RB_Insert(29);
    tree.RB_Insert(72);
    tree.RB_Insert(5);
    tree.RB_Insert(25);
    tree.RB_Insert(6);

    //std::cout << tree.root->left_son->m_key;
    tree.RB_Inorder_Walk(dynamic_cast<RB_tree_with_size<int>::Object_s<int>*>(tree.root));
    std::cout << '\n' << tree.Select_from_RB(tree.root, 2)->m_key;
    tree.RB_Delete(dynamic_cast<RB_tree_with_size<int>::Object_s<int>*>(tree.root));
    tree.RB_Inorder_Walk(dynamic_cast<RB_tree_with_size<int>::Object_s<int>*>(tree.root));

    /*RB_tree<int> tree(-1);
    tree.RB_Insert(5);
    tree.RB_Insert(34);
    tree.RB_Insert(256);
    tree.RB_Insert(29);
    tree.RB_Insert(72);
    tree.RB_Insert(5);
    tree.RB_Insert(25);
    tree.RB_Insert(6);

    //std::cout << tree.root->left_son->m_key;
    tree.RB_Inorder_Walk(tree.root);
    std::cout << '\n';
    tree.RB_Delete(tree.root);
    tree.RB_Inorder_Walk(tree.root);*/
}



