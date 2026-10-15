#include "table_calculator.hpp"
#include "column.hpp"
#include "formula.hpp"

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

void TableCalculator::AddCol(Column* col) {
    if (col->IsReady(m_experiments)) {
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
            Column* col = *it;
            if (CanCalculate(col)) {
                // Заглушка: заполняем данными
                std::vector<double> result(m_experiments, 52.0);
                col->SetData(result);
                
                m_readyCols.push_back(col);
                m_varsStates[col->GetVar()] = true;
                it = m_pendingCols.erase(it);
                progress = true;
                
                std::cout << "[TableCalculator] Вычислена колонка: " 
                          << col->GetName() << "\n";
            } else {
                ++it;
            }
        }
    }
    return m_pendingCols.empty();
}

bool TableCalculator::CanCalculate(Column* col) const {
    if (col->GetFormula() == nullptr) {
        return false;
    }
    for (const auto& var : col->GetFormula()->GetVars()) {
        auto it = m_varsStates.find(var);
        if (it == m_varsStates.end() || !it->second) {
            return false;
        }
    }
    return true;
}

} // namespace lab_comps