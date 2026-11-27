#include "table.hpp"
#include "../columns/input_column.hpp"
#include "../columns/formula_column.hpp"
#include "../columns/constant_column.hpp"
#include "table_calculator.hpp"

#include <iostream>
#include <algorithm>

namespace lab_comps {

Table::Table()
    : m_name{ "Таблица" }
    , m_experiments{ 1 }
{
    std::cout << "[Table] Создана: " << m_name << "\n";
}

Table::Table(const std::string& name, int experiments)
    : m_name{ name }
    , m_experiments{ experiments }
{
    std::cout << "[Table] Создана: " << m_name << "\n";
}

Table::~Table() {
    std::cout << "[Table] Уничтожена: " << m_name << "\n";
}

const std::string& Table::GetName() const {
    return m_name;
}

int Table::GetExperiments() const {
    return m_experiments;
}

const std::list<std::unique_ptr<BaseColumn>>& Table::GetColumns() const {
    return m_columns;
}

void Table::CreateInputColumn(const std::string& name, const std::string& var, int precision) {
    auto col = std::make_unique<InputColumn>(name, var, precision);
    m_lookup[var] = col.get(); // Сохраняем в map
    m_columns.push_back(std::move(col)); // Кладем в list
}

void Table::CreateFormulaColumn(const std::string& name, const std::string& var, 
                                int precision, std::unique_ptr<IEvaluationStrategy> strategy) {
    auto col = std::make_unique<FormulaColumn>(name, var, precision, std::move(strategy));
    m_lookup[var] = col.get();
    m_columns.push_back(std::move(col));
}

void Table::CreateConstantColumn(const std::string& name, const std::string& var,
                                 int precision, double value) {
    auto col = std::make_unique<ConstantColumn>(name, var, precision, value);
    m_lookup[var] = col.get();
    m_columns.push_back(std::move(col));
}

void Table::InsertColumnAt(std::size_t index, std::unique_ptr<BaseColumn> col) {
    if (index > m_columns.size()) index = m_columns.size();
    auto it = m_columns.begin();
    std::advance(it, index);
    m_lookup[col->GetVar()] = col.get();
    m_columns.insert(it, std::move(col));
    std::cout << "[Table] Колонка вставлена на позицию " << index << "\n";
}

void Table::SetColumnData(const std::string& var, const std::vector<double>& data) {
    // Используем map для быстрого поиска O(log N)
    auto it = m_lookup.find(var);
    if (it != m_lookup.end()) {
        it->second->SetData(data);
    }
}

void Table::Calculate() {
    TableCalculator calc(m_experiments);
    // Передаем указатели из list в калькулятор
    for (const auto& col : m_columns) {
        calc.AddCol(col.get());
    }
    calc.TryCalculate();
}

BaseColumn* Table::FindColumn(const std::string& var) const {
    auto it = m_lookup.find(var);
    return (it != m_lookup.end()) ? it->second : nullptr;
}

BaseColumn* Table::FindColumn(int id) const {
    // Для поиска по ID используем std::ranges::find_if (демонстрация алгоритма)
    auto it = std::ranges::find_if(m_columns, [id](const auto& col) {
        return col->GetId() == id;
    });
    return (it != m_columns.end()) ? it->get() : nullptr;
}

} // namespace lab_comps