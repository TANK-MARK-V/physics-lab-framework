#pragma once
#include <stdexcept>
#include <string>

namespace lab_comps {

// Исключение для неверной точности
class InvalidPrecisionError : public std::invalid_argument {
public:
    explicit InvalidPrecisionError(int precision)
        : std::invalid_argument("Ошибка: точность не может быть отрицательной (" + std::to_string(precision) + ")") {}
};

} // namespace lab_comps