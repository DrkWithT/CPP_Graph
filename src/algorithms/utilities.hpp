#pragma once

#include <set>
#include <queue>
#include "meta/utilities.hpp"

namespace CPPGraph::Algorithms {
    namespace Helpers {
        template <template <typename> typename GraphP, typename ItemP, typename FuncP> requires (Meta::GraphKind<GraphP, ItemP>)
        void helpDFT(GraphP<ItemP>& graph, std::set<ItemP>& visited, const ItemP& sub_node, const FuncP& fn)  {
            fn(sub_node);
            visited.emplace(sub_node);

            auto neighbors = graph.neighborsOf(sub_node);

            for (const auto& temp_neighbor : neighbors) {
                if (!visited.contains(temp_neighbor)) {
                    helpDFT(graph, visited, temp_neighbor, fn);
                }
            }
        }
    };

    template <template <typename> typename GraphP, typename ItemP, typename FuncP> requires (Meta::GraphKind<GraphP, ItemP>)
    void breadthTraversal(GraphP<ItemP>& graph, const FuncP& fn) {
        std::set<ItemP> visited;
        std::queue<ItemP> pending;

        pending.push(graph.first());

        while (!pending.empty()) {
            auto current = pending.front();
            pending.pop();

            fn(current);
            visited.emplace(current);

            auto neighbors = graph.neighborsOf(current);

            for (const auto& temp_neighbor : neighbors) {
                if (!visited.contains(temp_neighbor)) {
                    pending.push(temp_neighbor);
                }
            }
        }
    }

    template <template <typename> typename GraphP, typename ItemP, typename FuncP> requires (Meta::GraphKind<GraphP, ItemP>)
    void depthTraversal(GraphP<ItemP>& graph, const FuncP& fn) {
        std::set<ItemP> visited;

        Helpers::helpDFT(graph, visited, graph.first(), fn);
    }
}