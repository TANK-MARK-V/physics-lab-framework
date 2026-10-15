#include "formula.hpp"

#include <iostream>
#include <sstream>
#include <cctype>

namespace lab_comps {

Formula::Formula(const std::string& name, const std::string& expression)
    : m_name{ name }
    , m_expression{ expression }
{
    ParseExpression();
    std::cout << "[Formula] Создана: " << m_name << "\n";
}

Formula::~Formula() {
    std::cout << "[Formula] Уничтожена: " << m_name << "\n";
}

const std::string& Formula::GetName() const {
    return m_name;
}

const std::string& Formula::GetExpression() const {
    return m_expression;
}

const std::vector<std::string>& Formula::GetVars() const {
    return m_vars;
}

void Formula::ParseExpression() {
    std::istringstream iss(m_expression);
    std::string token;
    while (iss >> token) {
        m_postfix.push_back(token);
        if (std::isalpha(token[0])) {
            m_vars.push_back(token);
        }
    }
}

double Formula::Evaluate(const std::map<std::string, double>& vars) const {
    // TODO: реальный парсер
    return 42.0;
}

} // namespace lab_comps