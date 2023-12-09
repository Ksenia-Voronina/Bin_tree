#include <iostream>
#include <fstream>
#include <string>
#include "AVL_tree.h"

using namespace std;

void deleteTree(node* nd) {
    if (nd == nullptr) {
        return;
    }

    deleteTree(nd->left);
    deleteTree(nd->right);

    delete nd;
}

node* parseSubtree(const std::string& treeString, int& index) {
    if (index >= treeString.size()) {
        return nullptr;
    }

    // Пропуск пробелов
    while (index < treeString.size() && treeString[index] == ' ') {
        index++;
    }

    // Проверка на открывающую скобку
    if (index >= treeString.size() || treeString[index] != '(') {
        return nullptr;
    }

    // Пропуск открывающей скобки
    index++;

    // Создание узла
    node* nd = new node();

    // Парсинг значения узла
    std::string valueString;
    while (index < treeString.size() && treeString[index] != '(' && treeString[index] != ')') {
        valueString += treeString[index];
        index++;
    }
    nd->key = std::stoi(valueString);

    // Парсинг левого потомка
    nd->left = parseSubtree(treeString, index);
    if (nd->left == nullptr && index < treeString.size() && treeString[index] != ')') {
        deleteTree(nd);
        return nullptr;
    }

    // Парсинг правого потомка
    nd->right = parseSubtree(treeString, index);
    if (nd->right == nullptr && index < treeString.size() && treeString[index] != ')') {
        deleteTree(nd);
        return nullptr;
    }

    // Проверка на закрывающую скобку
    if (index >= treeString.size() || treeString[index] != ')') {
        deleteTree(nd);
        return nullptr;
    }

    // Пропуск закрывающей скобки
    index++;

    return nd;
}

node* parseTreeFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла" << std::endl;
        return nullptr;
    }

    std::string treeString;
    std::getline(file, treeString);
    file.close();

    // Рекурсивный парсинг скобочной записи и построение дерева
    int index = 0;
    node* root = parseSubtree(treeString, index);
    if (root == nullptr || index != treeString.size()) {
        std::cerr << "Ошибка парсинга дерева" << std::endl;
        deleteTree(root);
        return nullptr;
    }

    return root;
}

void dfs_preorder(node* tree) {
    if (tree == NULL)
        return;
    cout << tree->key << " ";
    dfs_preorder(tree->left);
    dfs_preorder(tree->right);
}

void dfs_postorder(node* tree) {
    if (tree == NULL)
        return;
    dfs_postorder(tree->left);
    dfs_postorder(tree->right);
    cout << tree->key << " ";
}

void dfs_inorder(node* tree) {
    if (tree == NULL)
        return;
    dfs_inorder(tree->left);
    cout << tree->key << " ";
    dfs_inorder(tree->right);
}

void bfs_(node* tree, int level) {
    //int h = height(tree);
    if (tree == nullptr) 
        return;
    if (level == 1) {
        std::cout << tree->key << " ";
    }
    else if (level > 1) {
        bfs_(tree->left, level - 1);
        bfs_(tree->right, level - 1);
    }
}

void bfs(node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        bfs_(root, i);
    }
}


int main() {
    setlocale(LC_ALL, "Russian");
    string filename;
    cout << "Введите имя файла: ";
    getline(cin, filename);
    cout << "\n";
    node* root = parseTreeFromFile(filename);
    string cmd;
    bin_tree tree;
    while (true) {
        string cmd;
        while (true) {
            cout << "Номера команд: \n\n";
            cout << "1) dfs preorder\n";
            cout << "2) dfs_postorder\n";
            cout << "3) dfs_inorder\n";
            cout << "4) bfs\n";
            cout << "0) выход\n\nВведите номер команды: ";

            getline(std::cin, cmd);

            if (cmd == "1") {
                cout << "\n";
                dfs_preorder(root);
                cout << "\n\n";
            }
            else if (cmd == "2") {
                cout << "\n";
                dfs_postorder(root);
                cout << "\n\n";
            }            
            else if (cmd == "3") {
                cout << "\n";
                dfs_inorder(root);
                cout << "\n\n";
            } 
            else if (cmd == "4") {
                cout << "\n";
                bfs(root);
                cout << "\n\n";
            }
            else if (cmd == "0") {
                return 0;
            }
            else {
                std::cout << "Неизвестная команда\n\n";
            }
        }
    }
    return 0;
}



