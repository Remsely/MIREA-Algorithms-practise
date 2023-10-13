#include <iostream>
#include <windows.h>

using namespace std;


struct TreeNode { // Узел бинарного дерева
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};


class BinarySearchTree {
private:
    TreeNode *root; // Корневой узел дерева

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) { // Метод для вставки нового элемента в бинарное дерево поиска
        root = insertRecursive(root, value);
    }

    TreeNode *insertRecursive(TreeNode *current, int value) {
        // Рекурсивное добавление элемента в дерево с учетом порядка ключей (меньшие значения слева, большие справа)
        if (current == nullptr) {
            return new TreeNode(value);
        }

        if (value < current->data)
            current->left = insertRecursive(current->left, value);
        else if (value > current->data)
            current->right = insertRecursive(current->right, value);

        return current;
    }

    void inorderTraversal(TreeNode *node) { // Симметричный обход дерева
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

    void postorderTraversal(TreeNode *node) { // Обратный обход дерева
        if (node != nullptr) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            cout << node->data << " ";
        }
    }

    int sumLeafValues(TreeNode *node) { // Рекурсивное вычисление суммы значений листьев дерева
        if (node == nullptr)
            return 0;

        if (node->left == nullptr && node->right == nullptr)
            return node->data;

        return sumLeafValues(node->left) + sumLeafValues(node->right);
    }

    int treeHeight(TreeNode *node) { // Рекурсивное нахождение высоты дерева
        if (node == nullptr)
            return 0;

        int leftHeight = treeHeight(node->left);
        int rightHeight = treeHeight(node->right);

        return 1 + max(leftHeight, rightHeight);
    }

    static void displayTreeMenu() {
        cout << "-------------------------------" << endl;
        cout << "Выберите действие:" << endl;
        cout << "1) Вставка элемента" << endl;
        cout << "2) Обратный обход" << endl;
        cout << "3) Симметричный обход" << endl;
        cout << "4) Найти сумму значений листьев" << endl;
        cout << "5) Найти высоту дерева" << endl;
        cout << "0) Завершить реаботу программы" << endl;
        cout << "-------------------------------" << endl;
    }

    void runProgram() {
        int choice;

        do {
            displayTreeMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    int value;
                    cout << "Введите значение: ";
                    cin >> value;
                    insert(value);
                    break;
                case 2:
                    cout << "Обратный обход: " << endl;
                    postorderTraversal(root);
                    cout << endl;
                    break;
                case 3:
                    cout << "Симметричный обход: " << endl;
                    inorderTraversal(root);
                    cout << endl;
                    break;
                case 4:
                    cout << "Сумма значений листьев: " << sumLeafValues(root) << endl;
                    break;
                case 5:
                    cout << "Высота дерева: " << treeHeight(root) << endl;
                    break;
                case 0:
                    cout << "Завершение работы программы!" << endl;
                    break;
                default:
                    cout << "Вы ввели некорректную команду! Попробуйте снова..." << endl;
                    break;
            }
        } while (choice != 0);
    }
};


int main() {
    SetConsoleOutputCP(CP_UTF8);
    BinarySearchTree tree;
    tree.runProgram();
    return 0;
}
