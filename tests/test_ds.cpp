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

    /**
     * @brief Represents a BT graph.
     *    10
     *   /  \
     *  5    15
     */
    Model::Graph<int> tree;

    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.connect(10, 5, Meta::Cyclicity::no);
    tree.connect(10, 15, Meta::Cyclicity::no);

    auto print_fn = [](int arg) {
        std::cout << arg << '\n';
    };

    /**
     * @brief Represents a K4 graph AKA a 4-node diamond.
     *     1
     *   / | \
     *  2  -  3
     *   \ | /
     *     4
     */
    Model::Graph<int> k4_diamond;

    k4_diamond.add(1);
    k4_diamond.add(2);
    k4_diamond.add(3);
    k4_diamond.add(4);
    k4_diamond.connect(1, 2, Meta::Cyclicity::yes);
    k4_diamond.connect(1, 3, Meta::Cyclicity::yes);
    k4_diamond.connect(2, 3, Meta::Cyclicity::yes);
    k4_diamond.connect(2, 4, Meta::Cyclicity::yes);
    k4_diamond.connect(3, 4, Meta::Cyclicity::yes);

    Algorithms::breadthTraversal(tree, print_fn);
    Algorithms::depthTraversal(k4_diamond, print_fn);
}
