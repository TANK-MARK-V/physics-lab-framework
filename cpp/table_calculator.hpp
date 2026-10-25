#pragma once

#include <string>
#include <vector>
#include <map>

namespace lab_comps {

class Column;

class TableCalculator {
private:
    int m_experiments;
    std::vector<Column*> m_readyCols;    // Агрегация
    std::vector<Column*> m_pendingCols;  // Агрегация
    std::map<std::string, bool> m_varsStates;  // Кэш

public:
    TableCalculator() = delete;
    TableCalculator(int experiments);
    ~TableCalculator();

    void AddCol(Column* col);
    bool TryCalculate();

private:
    bool CanCalculate(Column* col) const;
};

} // namespace lab_comps