#pragma once

#include <set>
#include <queue>
#include "meta/utilities.hpp"

namespace CPPGraph::Algorithms {
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
}