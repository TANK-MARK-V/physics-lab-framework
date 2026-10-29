#include "table.hpp"
#include "base_column.hpp"
#include "input_column.hpp"
#include "formula_column.hpp"
#include "constant_column.hpp"
#include "formula.hpp"
#include "table_calculator.hpp"

#include <iostream>

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

const std::vector<std::unique_ptr<BaseColumn>>& Table::GetColumns() const {
    return m_columns;
}

void Table::CreateInputColumn(const std::string& name, const std::string& var, int precision) {
    m_columns.push_back(std::make_unique<InputColumn>(name, var, precision));
}

void Table::CreateFormulaColumn(const std::string& name, const std::string& var, 
                                int precision, std::shared_ptr<Formula> formula) {
    m_columns.push_back(std::make_unique<FormulaColumn>(name, var, precision, formula));
}

void Table::CreateConstantColumn(const std::string& name, const std::string& var,
                                 int precision, double value) {
    m_columns.push_back(std::make_unique<ConstantColumn>(name, var, precision, value));
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
        calc.AddCol(col.get());  // ← BaseColumn*
    }
    calc.TryCalculate();
}

} // namespace lab_comps