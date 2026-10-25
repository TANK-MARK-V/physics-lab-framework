#pragma once

#include <string>
#include <vector>
#include <map>

namespace lab_comps {

class Formula {
private:
    std::string m_name;
    std::string m_expression;
    std::vector<std::string> m_postfix;
    std::vector<std::string> m_vars;

public:
    Formula() = delete;
    Formula(const std::string& name, const std::string& expression);
    ~Formula();

    [[nodiscard]] const std::string& GetName() const;
    [[nodiscard]] const std::string& GetExpression() const;
    [[nodiscard]] const std::vector<std::string>& GetVars() const;

    double Evaluate(const std::map<std::string, double>& vars) const;

private:
    void ParseExpression();
};

} // namespace lab_comps