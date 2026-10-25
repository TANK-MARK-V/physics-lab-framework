#include "column.hpp"
#include "formula.hpp"

#include <iostream>

namespace lab_comps {

Column::Column(const std::string& name, const std::string& var, int precision)
    : m_name{ name }
    , m_var{ var }
    , m_precision{ precision }
{
    if (precision < 0) {
        // Пока просто обнуляем точность
        m_precision = 0;
        std::cout << "[Column] Нельзя создать колонку с отрицательной точностью (правило №5)\n";
    }
    std::cout << "[Column] Создана: " << m_name << "\n";
}

Column::~Column() {
    std::cout << "[Column] Уничтожена: " << m_name << "\n";
}

const std::string& Column::GetName() const {
    return m_name;
}

const std::string& Column::GetVar() const {
    return m_var;
}

int Column::GetPrecision() const {
    return m_precision;
}

const std::vector<double>& Column::GetData() const {
    return m_data;
}

std::shared_ptr<Formula> Column::GetFormula() const {
    return m_formula.lock();  // ← weak → shared
}

void Column::SetData(const std::vector<double>& data) {
    m_data = data;
}

void Column::SetPrecision(int precision) {
    if (precision < 0) {
        // Пока просто обнуляем точность
        m_precision = 0;
        std::cout << "[Column] Нельзя установить отрицательную точность (правило №5)\n";
        return;
    }
    m_precision = precision;
}

void Column::SetFormula(std::shared_ptr<Formula> formula) {
    m_formula = formula;  // ← shared → weak
}

bool Column::IsReady(int expectedLength) const {
    return static_cast<int>(m_data.size()) == expectedLength;
}

} // namespace lab_comps