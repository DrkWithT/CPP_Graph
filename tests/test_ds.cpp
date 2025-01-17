/**
 * @file test_ds.cpp
 * @author DrkWithT
 * @brief Implements unit test for graph data structure.
 * @date 2025-01-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include "meta/utilities.hpp"
#include "model/graph.hpp"
#include "algorithms/utilities.hpp"

int main() {
    using namespace CPPGraph;

    Model::Graph<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.connect(10, 5, Meta::Cyclicity::no);
    tree.connect(10, 15, Meta::Cyclicity::no);
    std::cout << "foo 1" << '\n';

    auto print_fn = [](int arg) {
        std::cout << arg << '\n';
    };

    Algorithms::breadthTraversal(tree, print_fn);
    std::cout << "foo 2" << '\n';
}
