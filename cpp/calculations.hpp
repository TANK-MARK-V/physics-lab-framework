#pragma once

#include <vector>
#include <stdexcept>
#include <concepts>
#include <iostream>

namespace lab_comps {

// Концепт: тип должен быть целым или числом с плавающей точкой
template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Шаблонная функция: вычисление среднего значения
template <Numeric T>
[[nodiscard]] double Average(const std::vector<T>& data) {
    if (data.empty()) {
        throw std::invalid_argument("Average: вектор пуст!");
    }
    
    double sum = 0.0;
    for (const auto& val : data) {
        sum += static_cast<double>(val);
    }
    
    return sum / static_cast<double>(data.size());
}

// Перегрузка для вычисления среднего значения из вектора double и double погрешности
// (Просто для демонстрации, что шаблон работает и с нашими типами, если мы расширим концепт)
template <Numeric T>
[[nodiscard]] double Average(const std::vector<T>& values, const std::vector<T>& errors) {
    if (values.empty() || values.size() != errors.size()) {
        throw std::invalid_argument("Average: некорректные размеры векторов!");
    }
    // В реальной физике тут было бы более сложное вычисление, но пока так
    return Average(values); 
}

} // namespace lab_comps