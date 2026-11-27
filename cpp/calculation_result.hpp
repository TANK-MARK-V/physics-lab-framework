#pragma once

#include <variant>
#include <string>
#include <iostream>
#include "physical_quantity.hpp"

namespace lab_comps {

// 1. Вариант: просто число
struct NumberResult {
    double value;
};

// 2. Вариант: число с погрешностью
struct ErrorResult {
    PhysicalQuantity quantity;
};

// 3. Вариант: текст ошибки
struct TextResult {
    std::string message;
};

// Сам variant
using CalculationResult = std::variant<NumberResult, ErrorResult, TextResult>;

// Функция для обработки через std::visit
inline void PrintResult(const CalculationResult& result) {
    std::visit([](const auto& res) {
        // Обобщенная лямбда (auto) — подходит для всех трех типов
        using T = std::decay_t<decltype(res)>;
        
        if constexpr (std::is_same_v<T, NumberResult>) {
            std::cout << "Результат (число): " << res.value << "\n";
        } 
        else if constexpr (std::is_same_v<T, ErrorResult>) {
            std::cout << "Результат (с погрешностью): " << res.quantity << "\n";
        } 
        else if constexpr (std::is_same_v<T, TextResult>) {
            std::cout << "Результат (ошибка): " << res.message << "\n";
        }
    }, result);
}

} // namespace lab_comps