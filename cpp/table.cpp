#include "table.hpp"
#include "column.hpp"
#include "formula.hpp"
#include "table_calculator.hpp"

#include <iostream>
#include <memory>

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

const std::vector<std::unique_ptr<Column>>& Table::GetColumns() const {
    return m_columns;
}

void Table::CreateColumn(const std::string& name, const std::string& var, int precision) {
    m_columns.push_back(std::make_unique<Column>(name, var, precision));
    std::cout << "[Table] Добавлена колонка: " << name << "\n";
}

void Table::CreateColumn(const std::string& name, const std::string& var, 
                         int precision, std::shared_ptr<Formula> formula) {
    auto col = std::make_unique<Column>(name, var, precision);
    col->SetFormula(formula);
    m_columns.push_back(std::move(col));
    std::cout << "[Table] Добавлена колонка с формулой: " << name << "\n";
}

void Table::SetColumnData(const std::string& var, const std::vector<double>& data) {
    for (auto& col : m_columns) {
        if (col->GetVar() == var) {
            col->SetData(data);
            return;
        }
    }
}

void Table::Calculate() {
    TableCalculator calc(m_experiments);
    for (auto& col : m_columns) {
        calc.AddCol(col.get());
    }
    calc.TryCalculate();
}

} // namespace lab_comps