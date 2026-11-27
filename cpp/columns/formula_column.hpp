#pragma once

#include "base_column.hpp"
#include "icalculable.hpp"
#include <memory>
#include <functional>
#include <map>
#include <string>

namespace lab_comps {

class FormulaColumn : public BaseColumn, public ICalculable {
private:
    // Заменяем стратегию на std::function!
    std::function<double(const std::map<std::string, double>&)> m_calculator;
    bool m_isCalculated{ false };

public:
    // Конструктор теперь принимает функцию
    FormulaColumn(std::string name, std::string var, int precision, 
                  std::function<double(const std::map<std::string, double>&)> calcFunc);
    
    // --- ПРАВИЛО ПЯТИ ---
    FormulaColumn(const FormulaColumn& other);                  // Копирование (глубокое)
    FormulaColumn(FormulaColumn&& other) noexcept;              // Перемещение
    FormulaColumn& operator=(const FormulaColumn& other);       // Копирующее присваивание (глубокое)
    FormulaColumn& operator=(FormulaColumn&& other) noexcept;   // Перемещающее присваивание
    ~FormulaColumn() override;                                  // Деструктор
    // --------------------

    std::string GetType() const override;
    std::string Describe() const override;
    std::unique_ptr<BaseColumn> Clone() const override;

    // Метод для смены поведения
    void SetCalculator(std::function<double(const std::map<std::string, double>&)> calcFunc);

    void Calculate() override;
    bool IsCalculated() const override { return m_isCalculated; }
};

} // namespace lab_comps