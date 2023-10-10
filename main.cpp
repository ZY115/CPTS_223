#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "AVLTree.h"
#include "AVLNode.h"

int main() {
    //  Create three data sequences
    std::vector<int> ascending;
    std::vector<int> descending;
    std::vector<int> randomSeq;

    for (int i = 1; i <= 100; i += 2) {
        ascending.push_back(i);
        descending.insert(descending.begin(), i);
        randomSeq.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(randomSeq.begin(), randomSeq.end(), g);  // Modified here

    //  Create three AVL trees
    AVLTree<int> tree1, tree2, tree3;

    for (int val : ascending) {
        tree1.insert(val);
    }
    for (int val : descending) {
        tree2.insert(val);
    }
    for (int val : randomSeq) {
        tree3.insert(val);
    }

    std::cout << "Tree1 height: " << tree1.height() << std::endl;
    std::cout << "Tree2 height: " << tree2.height() << std::endl;
    std::cout << "Tree3 height: " << tree3.height() << std::endl;

    std::cout << "Tree1 validation: " << tree1.validate() << std::endl;
    std::cout << "Tree2 validation: " << tree2.validate() << std::endl;
    std::cout << "Tree3 validation: " << tree3.validate() << std::endl;

    //  contains check
    for (int i = 1; i <= 100; ++i) {
        bool res1 = tree1.contains(i);
        bool res2 = tree2.contains(i);
        bool res3 = tree3.contains(i);

        if ((i % 2 == 0 && (res1 || res2 || res3)) ||
            (i % 2 != 0 && (!res1 || !res2 || !res3))) {
            std::cout << "My AVL tree implementation is wrong" << std::endl;
            break;
        }
    }

    return 0;
}
