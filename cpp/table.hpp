#pragma once

#include <string>
#include <vector>
#include <memory>

namespace lab_comps {

class Column;
class Formula;

class Table {
private:
    std::string m_name;
    int m_experiments;
    std::vector<std::unique_ptr<Column>> m_columns;

public:
    Table();
    Table(const std::string& name, int experiments);
    ~Table();

    [[nodiscard]] const std::string& GetName() const;
    [[nodiscard]] int GetExperiments() const;
    [[nodiscard]] const std::vector<std::unique_ptr<Column>>& GetColumns() const;

    // Композиция: Table САМ создаёт колонку
    void CreateColumn(const std::string& name, const std::string& var, int precision);

    // Агрегация: формула создана СНАРУЖИ
    void CreateColumn(const std::string& name, const std::string& var, 
                      int precision, std::shared_ptr<Formula> formula);

    // Установить данные колонке по имени переменной
    void SetColumnData(const std::string& var, const std::vector<double>& data);

    // Расчёт всей таблицы
    void Calculate();
};

} // namespace lab_comps