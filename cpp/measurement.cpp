#pragma once

#include <string>

namespace lab_comps {

// Структура для демонстрации алгоритмов
struct Measurement {
    std::string student;   // Кто делал
    std::string parameter; // Что измерял
    double value;          // Значение
    double error;          // Погрешность
    bool processed;        // Обработано ли
};

} // namespace lab_comps