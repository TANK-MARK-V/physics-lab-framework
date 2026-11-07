#pragma once

#include <string>
#include <vector>
#include <map>

namespace lab_comps {

class BaseColumn;

class TableCalculator {
private:
    int m_experiments;
    std::vector<BaseColumn*> m_readyCols;
    std::vector<BaseColumn*> m_pendingCols;
    std::map<std::string, bool> m_varsStates;

public:
    TableCalculator() = delete;
    TableCalculator(int experiments);
    ~TableCalculator();

    void AddCol(BaseColumn* col);
    bool TryCalculate();

private:
    bool CanCalculate(BaseColumn* col) const;
};

} // namespace lab_comps