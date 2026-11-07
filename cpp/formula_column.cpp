#include "formula_column.hpp"
#include "formula.hpp"

#include <iostream>
#include <utility>


namespace lab_comps {

FormulaColumn::FormulaColumn(std::string name, std::string var, 
                             int precision, std::shared_ptr<Formula> formula)
    : BaseColumn{ std::move(name), std::move(var), precision }
    , m_formula{ std::move(formula) }
{
    std::cout << "[FormulaColumn] Создана\n";
}

FormulaColumn::FormulaColumn(const FormulaColumn& other)
    : BaseColumn{ other }           // копируем базу
    , m_formula{ other.m_formula }  // копируем формулу
{
    std::cout << "[FormulaColumn] Копия: " << m_name 
              << " (ID: " << GetId() << ")\n";
}

FormulaColumn::FormulaColumn(FormulaColumn&& other) noexcept
    : BaseColumn{ std::move(other) }       // перемещаем базу
    , m_formula{ std::move(other.m_formula) } // перемещаем умный указатель
{
    std::cout << "[FormulaColumn] Перемещение: " << m_name << "\n";
}

FormulaColumn& FormulaColumn::operator=(const FormulaColumn& other) {
    if (this == &other) return *this; // защита от самоприсваивания
    
    BaseColumn::operator=(other); // вызываем присваивание базы!
    m_formula = other.m_formula;  // копируем shared_ptr
    
    std::cout << "[FormulaColumn] Присваивание (копия): " << m_name << "\n";
    return *this;
}

FormulaColumn& FormulaColumn::operator=(FormulaColumn&& other) noexcept {
    if (this == &other) return *this; // защита от самоприсваивания
    
    BaseColumn::operator=(std::move(other)); // перемещаем базу!
    m_formula = std::move(other.m_formula);  // перемещаем shared_ptr
    
    std::cout << "[FormulaColumn] Присваивание (перемещение): " << m_name << "\n";
    return *this;
}

FormulaColumn::~FormulaColumn() {
    std::cout << "[FormulaColumn] Уничтожена: " << m_name << "\n";
}

std::string FormulaColumn::GetType() const {
    return "Formula";
}

std::string FormulaColumn::Describe() const {
    // без вызова базы
    return "Формула: " + m_name + " = " + m_formula->GetExpression();
}

std::unique_ptr<BaseColumn> FormulaColumn::Clone() const {
    // СОЗДАЕМ НОВУЮ ФОРМУЛУ (глубокая копия)
    // Копируем данные из старой формулы в новую
    auto newFormula = std::make_shared<Formula>(
        m_formula->GetName(), 
        m_formula->GetExpression()
    );
    
    // Возвращаем новую колонку с НОВОЙ формулой
    return std::make_unique<FormulaColumn>(
        m_name, m_var, m_precision, newFormula
    );
}

void FormulaColumn::Calculate() {
    std::cout << "[FormulaColumn] Calculate для: " << m_name << "\n";
}

void FormulaColumn::SetFormula(std::shared_ptr<Formula> formula) {
    m_formula = formula;
}

std::shared_ptr<Formula> FormulaColumn::GetFormula() const {
    return m_formula;
}

} // namespace lab_comps