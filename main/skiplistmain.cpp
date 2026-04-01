#include <iostream>
#include <string>
#include "../lib_skiplist/skiplist.h"

int main() {
    skipList<int, std::string> myMap;

    std::cout << "=== Testing Insertion ===" << std::endl;
    myMap.insert(10, "Ten");
    myMap.insert(20, "Twenty");
    myMap.insert(5, "Five");
    myMap.insert(15, "Fifteen");
    myMap.insert(25, "Twenty-Five");

    myMap.insert(10, "TEN_UPDATED");

    myMap.display();

    std::cout << "=== Testing Search ===" << std::endl;
    int testKeys[] = { 5, 10, 100 };

    for (int key : testKeys) {
        if (myMap.search(key)) {
            std::cout << "Key " << key << " found in list." << std::endl;
        }
        else {
            std::cout << "Key " << key << " NOT found." << std::endl;
        }
    }

    std::cout << "\n==========================" << std::endl;
    skipList<double, int> intMap;
    intMap.insert(1.1, 1);
    intMap.insert(2.2, 2);
    intMap.insert(0.5, 0);
    intMap.display();
    std::cout << "\n==========================" << std::endl;
    skipList<double, int> intMap2;
    intMap2.display();
    return 0;
}