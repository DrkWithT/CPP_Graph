#pragma once

#include <type_traits>
#include <concepts>

namespace CPPGraph::Meta {
    enum class Cyclicity {
        yes,
        no
    };

    template <typename Tp>
    using bared_type_of = std::remove_reference_t<std::remove_cv_t<Tp>>;

    template <typename ItemT>
    concept ComparableKind = requires(ItemT&& lhs, ItemT&& rhs) {
        {lhs == rhs} -> std::same_as<bool>;
        {lhs != rhs} -> std::same_as<bool>;
    };

    template <typename ItemT>
    constexpr bool is_valid_item_v = std::is_trivially_copyable_v<ItemT>;

    template <template <typename> typename T, typename ItemT>
    concept GraphKind = requires(T<ItemT>&& arg, ItemT&& item, ItemT&& other, Cyclicity cycles) {
        {arg.empty()} -> std::same_as<bool>;
        {arg.first()} -> std::same_as<ItemT&>;
        {arg.add(item)} -> std::same_as<bool>;
        {arg.connect(item, other, cycles)} -> std::same_as<bool>;
        {arg.remove(item)} -> std::same_as<bool>;
    };
}