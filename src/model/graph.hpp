#pragma once

#include <algorithm>
#include <optional>
#include <forward_list>
#include <vector>
#include "meta/utilities.hpp"

namespace CPPGraph::Model {
    template <typename ItemT> requires (Meta::is_valid_item_v<ItemT> && Meta::ComparableKind<ItemT>)
    class Graph {
    private:
        /// @todo make graph storages configurable?? It may need a type erased storage wrapping the underlying data structure taking scoped enum NTTPs.
        std::vector<ItemT> m_items;
        std::vector<std::forward_list<unsigned int>> m_nodes;

    public:
        Graph()
        : m_items {}, m_nodes {} {}

        [[nodiscard]] constexpr bool empty() const noexcept {
            return m_items.empty();
        }

        ItemT& first() {
            return m_items.at(0);
        }

        bool add(ItemT arg) {
            if (std::find(m_items.cbegin(), m_items.cend(), arg) != m_items.cend() && (!m_items.empty() || !m_nodes.empty())) {
                return false;
            }

            m_items.emplace_back(arg);
            m_nodes.emplace_back(std::forward_list<unsigned int> {});

            return true;
        }

        bool connect(ItemT src, ItemT dest, Meta::Cyclicity allow_cycle) {
            using IndexOpt = std::optional<unsigned int>;

            auto index_of = [this](ItemT arg) -> IndexOpt {
                auto index = 0U;

                for (const auto& temp : m_items) {
                    if (arg == temp) {
                        break;
                    }

                    index++;
                }

                if (index < m_nodes.size()) {
                    return index;
                }

                return {};
            };

            IndexOpt src_index = index_of(src);
            IndexOpt dest_index = index_of(dest);

            if (allow_cycle == Meta::Cyclicity::yes) {
                m_nodes[src_index.value()].emplace_front(dest_index.value());
                m_nodes[dest_index.value()].emplace_front(src_index.value());
            } else {
                m_nodes[src_index.value()].emplace_front(dest_index.value());
            }

            return true;
        }

        bool remove(ItemT arg) {
            using IndexOpt = std::optional<unsigned int>;

            auto index_of = [this](ItemT arg) -> IndexOpt {
                auto index = 0U;

                for (const auto& temp : m_items) {
                    if (arg == temp) {
                        break;
                    }

                    index++;
                }

                return (index < m_nodes.size())
                    ? IndexOpt {index}
                    : IndexOpt {std::nullopt};
            };

            IndexOpt arg_index = index_of(arg);

            if (!arg_index) {
                return false;
            }

            m_items.erase(m_items.begin() + arg_index.value());
            m_nodes.erase(m_nodes.begin() + arg_index.value());

            return true;
        }

        std::vector<ItemT> neighborsOf(ItemT arg) {
            using IndexOpt = std::optional<unsigned int>;

            auto index_of = [this](ItemT arg) -> IndexOpt {
                auto index = 0U;

                for (const auto& temp : m_items) {
                    if (arg == temp) {
                        break;
                    }

                    index++;
                }

                return (index < m_nodes.size())
                    ? IndexOpt {index}
                    : IndexOpt {};
            };

            IndexOpt arg_index = index_of(arg);

            if (!arg_index) {
                return {};
            }

            std::vector<ItemT> result;

            for (const auto neighbor_pos : m_nodes.at(arg_index.value())) {
                result.emplace_back(m_items[neighbor_pos]);
            }

            return result;
        }
    };
}