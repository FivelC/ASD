#include "../lib_binarysearchtree/binarysearchtree.h"
int main() {
    BSTree<int, std::string> tree;

    std::cout << "=== insert: 5 1 3 7 2 4 ===\n";
    tree.insert(5, "five");
    tree.insert(1, "one");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(4, "four");
    tree.print_tree();

    std::cout << "\n=== find(3) ===" << '\n';
    std::string* v = tree.find(3);
    std::cout << (v ? *v : "not found") << '\n';

    std::cout << "\n=== erase(1) ===\n";
    tree.erase(1);
    tree.print_tree();

    std::cout << "\n=== erase(3)===\n";
    tree.erase(3);
    tree.print_tree();

    std::cout << "\n=== erase(7)===\n";
    tree.erase(7);
    tree.print_tree();

    std::cout << "\n======\n";
    tree.print_tree();

    return 0;
}