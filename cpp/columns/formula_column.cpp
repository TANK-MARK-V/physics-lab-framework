#include "formula_column.hpp"

#include <iostream>
#include <utility>

namespace lab_comps {

FormulaColumn::FormulaColumn(std::string name, std::string var, int precision, 
                             std::function<double(const std::map<std::string, double>&)> calcFunc)
    : BaseColumn{ std::move(name), std::move(var), precision }
    , m_calculator{ std::move(calcFunc) }
{
    std::cout << "[FormulaColumn] Создана\n";
}

FormulaColumn::FormulaColumn(const FormulaColumn& other)
    : BaseColumn{ other }
    , m_calculator{ other.m_calculator }
{
    std::cout << "[FormulaColumn] Копия: " << m_name << "\n";
}

FormulaColumn::FormulaColumn(FormulaColumn&& other) noexcept
    : BaseColumn{ std::move(other) }
    , m_calculator{ std::move(other.m_calculator) }
{
    std::cout << "[FormulaColumn] Перемещение: " << m_name << "\n";
}

FormulaColumn& FormulaColumn::operator=(const FormulaColumn& other) {
    if (this == &other) return *this;
    BaseColumn::operator=(other);
    m_calculator = other.m_calculator;
    return *this;
}

FormulaColumn& FormulaColumn::operator=(FormulaColumn&& other) noexcept {
    if (this == &other) return *this;
    BaseColumn::operator=(std::move(other));
    m_calculator = std::move(other.m_calculator);
    return *this;
}

FormulaColumn::~FormulaColumn() {
    std::cout << "[FormulaColumn] Уничтожена: " << m_name << "\n";
}

std::string FormulaColumn::GetType() const { return "Formula"; }

std::string FormulaColumn::Describe() const {
    return "Формула: " + m_name + " (лямбда)";
}

std::unique_ptr<BaseColumn> FormulaColumn::Clone() const {
    auto copy = std::make_unique<FormulaColumn>(m_name, m_var, m_precision, m_calculator);
    copy->SetData(GetData());
    return copy;
}

void FormulaColumn::SetCalculator(std::function<double(const std::map<std::string, double>&)> calcFunc) {
    m_calculator = std::move(calcFunc);
    std::cout << "[FormulaColumn] Поведение изменено для " << m_name << "\n";
}

void FormulaColumn::Calculate() {
    if (!m_calculator) {
        std::cout << "[FormulaColumn] Ошибка: нет поведения для " << m_name << "\n";
        return;
    }
    
    std::map<std::string, double> vars; 
    double result = m_calculator(vars);
    m_isCalculated = true;
    
    std::cout << "[FormulaColumn] " << m_name << " = " << result << "\n";
}

} // namespace lab_comps