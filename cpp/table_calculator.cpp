#include "table_calculator.hpp"
#include "base_column.hpp"

#include <iostream>

namespace lab_comps {

TableCalculator::TableCalculator(int experiments)
    : m_experiments{ experiments }
{
    std::cout << "[TableCalculator] Открыт\n";
}

TableCalculator::~TableCalculator() {
    std::cout << "[TableCalculator] Закрыт\n";
}

void TableCalculator::AddCol(BaseColumn* col) {
    if (col->GetData().size() == static_cast<size_t>(m_experiments)) {
        m_readyCols.push_back(col);
        m_varsStates[col->GetVar()] = true;
    } else {
        m_pendingCols.push_back(col);
        m_varsStates[col->GetVar()] = false;
    }
}

bool TableCalculator::TryCalculate() {
    bool progress = true;
    while (progress) {
        progress = false;
        for (auto it = m_pendingCols.begin(); it != m_pendingCols.end(); ) {
            BaseColumn* col = *it;
            if (CanCalculate(col)) {
                col->Calculate();
                m_readyCols.push_back(col);
                m_varsStates[col->GetVar()] = true;
                it = m_pendingCols.erase(it);
                progress = true;
                std::cout << "[TableCalculator] Вычислена: " 
                          << col->GetName() << "\n";
            } else {
                ++it;
            }
        }
    }
    return m_pendingCols.empty();
}

bool TableCalculator::CanCalculate(BaseColumn* col) const {
    // Пока заглушка: просто проверяем зависимости по формуле
    return true;
}

} // namespace lab_comps