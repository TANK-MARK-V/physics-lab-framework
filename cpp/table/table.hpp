#pragma once

#include "../columns/base_column.hpp"
#include "../strategies/ievaluation_strategy.hpp"
#include <string>
#include <list>
#include <map>
#include <memory>
#include <vector>

namespace lab_comps {

class Table {
private:
    std::string m_name;
    int m_experiments;
    
    // 1. std::list для гибкой вставки колонок в любое место
    std::list<std::unique_ptr<BaseColumn>> m_columns;
    
    // 2. std::map для быстрого поиска колонки по имени переменной
    // Храним "var" -> указатель на колонку (итератор было бы сложнее)
    std::map<std::string, BaseColumn*> m_lookup;

public:
    Table();
    Table(const std::string& name, int experiments);
    ~Table();

    [[nodiscard]] const std::string& GetName() const;
    [[nodiscard]] int GetExperiments() const;
    [[nodiscard]] const std::list<std::unique_ptr<BaseColumn>>& GetColumns() const;

    // Создание колонок
    void CreateInputColumn(const std::string& name, const std::string& var, int precision);
    void CreateFormulaColumn(const std::string& name, const std::string& var,
                             int precision, std::unique_ptr<IEvaluationStrategy> strategy);
    void CreateConstantColumn(const std::string& name, const std::string& var,
                              int precision, double value);

    // Вставка в середину (демонстрация для std::list)
    void InsertColumnAt(std::size_t index, std::unique_ptr<BaseColumn> col);

    // Установить данные
    void SetColumnData(const std::string& var, const std::vector<double>& data);

    // Расчёт
    void Calculate();

    // Поиск (теперь через std::map)
    [[nodiscard]] BaseColumn* FindColumn(const std::string& var) const;
    [[nodiscard]] BaseColumn* FindColumn(int id) const;
};

} // namespace lab_comps