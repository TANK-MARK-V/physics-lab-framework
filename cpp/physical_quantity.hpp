#pragma once

#include <iostream>
#include <compare>
#include <cmath>

namespace lab_comps {

class PhysicalQuantity {
private:
    double m_value;
    double m_error;

public:
    // Конструктор с параметрами по умолчанию
    PhysicalQuantity(double value = 0.0, double error = 0.0);
    
    // Деструктор
    ~PhysicalQuantity();

    // Геттеры
    [[nodiscard]] double GetValue() const { return m_value; }
    [[nodiscard]] double GetError() const { return m_error; }

    // Составное присваивание (метод)
    PhysicalQuantity& operator+=(const PhysicalQuantity& other) {
        m_value += other.m_value;
        m_error += other.m_error;
        return *this;
    }

    // Бинарное сложение (дружественная функция)
    friend PhysicalQuantity operator+(PhysicalQuantity left, const PhysicalQuantity& right) {
        left += right;
        return left;
    }

    // Оператор сравнения "космический корабль" (C++20)
    // Автоматически даёт ==, !=, <, <=, >, >=
    auto operator<=>(const PhysicalQuantity&) const = default;

    // Дружественная функция вывода в поток
    friend std::ostream& operator<<(std::ostream& out, const PhysicalQuantity& pq) {
        out << pq.m_value << " ± " << pq.m_error;
        return out;
    }
};

} // namespace lab_comps