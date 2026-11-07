#include "formula_column.hpp"

#include <iostream>
#include <map>
#include <utility>

namespace lab_comps {

FormulaColumn::FormulaColumn(std::string name, std::string var, int precision, 
                             std::shared_ptr<IEvaluationStrategy> strategy)
    : BaseColumn{ std::move(name), std::move(var), precision }
    , m_strategy{ std::move(strategy) }
{
    std::cout << "[FormulaColumn] Создана\n";
}

// 1. Конструктор копирования (ПОВЕРХНОСТНАЯ КОПИЯ)
FormulaColumn::FormulaColumn(const FormulaColumn& other)
    : BaseColumn{ other } // копируем базу
    , m_strategy{ other.m_strategy } // копируем shared_ptr (делим стратегию)
{
    std::cout << "[FormulaColumn] Поверхностная копия: " << m_name << "\n";
}

// 2. Конструктор перемещения
FormulaColumn::FormulaColumn(FormulaColumn&& other) noexcept
    : BaseColumn{ std::move(other) }
    , m_strategy{ std::move(other.m_strategy) }
{
    std::cout << "[FormulaColumn] Перемещение: " << m_name << "\n";
}

// 3. Оператор копирующего присваивания (ПОВЕРХНОСТНАЯ КОПИЯ)
FormulaColumn& FormulaColumn::operator=(const FormulaColumn& other) {
    if (this == &other) return *this; // защита от самоприсваивания
    
    BaseColumn::operator=(other); // копируем базу
    m_strategy = other.m_strategy; // копируем shared_ptr
    
    std::cout << "[FormulaColumn] Присваивание (копия): " << m_name << "\n";
    return *this;
}

// 4. Оператор перемещающего присваивания
FormulaColumn& FormulaColumn::operator=(FormulaColumn&& other) noexcept {
    if (this == &other) return *this;
    
    BaseColumn::operator=(std::move(other));
    m_strategy = std::move(other.m_strategy);
    
    std::cout << "[FormulaColumn] Присваивание (перемещение): " << m_name << "\n";
    return *this;
}

// 5. Деструктор
FormulaColumn::~FormulaColumn() {
    std::cout << "[FormulaColumn] Уничтожена: " << m_name << "\n";
}

std::string FormulaColumn::GetType() const {
    return "Formula";
}

std::string FormulaColumn::Describe() const {
    if (m_strategy) {
        return "Формула: " + m_name + " = " + m_strategy->GetView();
    }
    return "Формула: " + m_name + " (нет стратегии)";
}

// ГЛУБОКАЯ КОПИЯ через Clone()
std::unique_ptr<BaseColumn> FormulaColumn::Clone() const {
    auto newStrategy = m_strategy ? m_strategy->Clone() : nullptr;
    
    auto copy = std::make_unique<FormulaColumn>(
        m_name, m_var, m_precision, std::shared_ptr<IEvaluationStrategy>(std::move(newStrategy))
    );
    copy->SetData(GetData());
    return copy;
}

void FormulaColumn::SetStrategy(std::shared_ptr<IEvaluationStrategy> strategy) {
    m_strategy = std::move(strategy);
    std::cout << "[FormulaColumn] Стратегия изменена для " << m_name << "\n";
}

void FormulaColumn::Calculate() {
    if (!m_strategy) {
        std::cout << "[FormulaColumn] Ошибка: нет стратегии для " << m_name << "\n";
        return;
    }
    
    std::map<std::string, double> vars; 
    double result = m_strategy->Evaluate(vars);
    m_isCalculated = true;
    
    std::cout << "[FormulaColumn] " << m_name 
              << " (" << m_strategy->GetView() << ") = " << result << "\n";
}

} // namespace lab_comps