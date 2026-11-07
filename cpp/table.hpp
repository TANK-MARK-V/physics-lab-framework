#pragma once

#include <string>
#include <vector>
#include <memory>

namespace lab_comps {

class BaseColumn;
class Formula;

class Table {
private:
    std::string m_name;
    int m_experiments;
    std::vector<std::unique_ptr<BaseColumn>> m_columns;

public:
    Table();
    Table(const std::string& name, int experiments);
    ~Table();

    [[nodiscard]] const std::string& GetName() const;
    [[nodiscard]] int GetExperiments() const;
    [[nodiscard]] const std::vector<std::unique_ptr<BaseColumn>>& GetColumns() const;

    // Создание колонок разных типов
    void CreateInputColumn(const std::string& name, const std::string& var, int precision);
    void CreateFormulaColumn(const std::string& name, const std::string& var, 
                             int precision, std::shared_ptr<Formula> formula);
    void CreateConstantColumn(const std::string& name, const std::string& var,
                              int precision, double value);

    // Установить данные
    void SetColumnData(const std::string& var, const std::vector<double>& data);

    // Расчёт
    void Calculate();
};

} // namespace lab_comps