#pragma once

#include <string>
#include <vector>
#include <map>

namespace lab_comps {

class Table;      // Вперёд-объявление

class Formula {
private:
    Table* m_table;
    std::string m_name;
    std::string m_expression;
    std::vector<std::string> m_postfix;
    std::vector<std::string> m_vars;

public:
    Formula() = delete;
    Formula(Table* table, const std::string& expression, const std::string& name);
    ~Formula();

    void setTable(Table* table);

    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::string& getExpression() const;
    [[nodiscard]] const std::vector<std::string>& getVars() const;

    void parseExpression();
    [[nodiscard]] bool validate();
    double evaluate(const std::map<std::string, double>& vars) const;
};

} // namespace lab_comps