#pragma once

#include <string>
#include <vector>

#include "formula.hpp"

namespace lab_comps {

class Table;      // Вперёд-объявление

class Column {
private:
    Table* m_table;
    std::string m_name;
    std::string m_var;
    int m_precision;
    std::vector<double> m_data;
    Formula* m_formula;

public:
    Column() = delete;
    Column(Table* table, const std::string& name,
            const std::string& var, int precision);
    ~Column();

    void setData(const std::vector<double>& data);

    [[nodiscard]] const std::string& getVar() const;
    [[nodiscard]] const std::vector<double>& getData() const;
    [[nodiscard]] const Formula* getFormula() const;


    
    bool setFormula(Formula*);
    bool isReady() const;
    bool calculate();
};

}   // namespace lab_comps
