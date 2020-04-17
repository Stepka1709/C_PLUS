/*
Найти запись с ключом, ближайшим к среднему значению между максимальным и минимальным значениями ключей.
*/

#include <iostream>
#include <Windows.h>
#include "CTree.h"

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    CTree* tree = new CTree("tree_two.txt", "tree");

    tree->find_key(); 
    tree->view_all();

    delete tree;
    tree = NULL;
}
