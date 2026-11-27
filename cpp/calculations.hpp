#pragma once

#include <vector>
#include <stdexcept>
#include <concepts>
#include <iostream>
#include <span>
#include <numeric>

namespace lab_comps {

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Изменили параметр на std::span!
template <Numeric T>
[[nodiscard]] double Average(std::span<const T> data) {
    if (data.empty()) {
        throw std::invalid_argument("Average: массив пуст!");
    }
    
    double sum = 0.0;
    for (const auto& val : data) {
        sum += static_cast<double>(val);
    }
    
    return sum / static_cast<double>(data.size());
}

} // namespace lab_comps