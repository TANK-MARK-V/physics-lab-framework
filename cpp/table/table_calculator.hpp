#pragma once

#include <string>
#include <vector>
#include <map>
#include <list>

namespace lab_comps {

class BaseColumn;

// std::vector используется для хранения указателей на колонки. 
// Быстрый доступ по индексу и добавление в конец.
class TableCalculator {
private:
    int m_experiments;
    std::vector<BaseColumn*> m_readyCols;   // Вектор для готовых
    std::vector<BaseColumn*> m_pendingCols; // Вектор для ожидающих
    std::map<std::string, bool> m_varsStates;

public:
    TableCalculator() = delete;
    TableCalculator(int experiments);
    ~TableCalculator();

        // Геттеры для демонстрации использования вектора
    [[nodiscard]] std::size_t GetReadyCount() const { return m_readyCols.size(); }
    [[nodiscard]] std::size_t GetPendingCount() const { return m_pendingCols.size(); }

    void AddCol(BaseColumn* col);
    bool TryCalculate();

private:
    bool CanCalculate(BaseColumn* col) const;
};

} // namespace lab_comps