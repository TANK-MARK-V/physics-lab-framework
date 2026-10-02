#include "formula.hpp"
#include "table.hpp"

#include <iostream>
#include <map>
#include <sstream>    // std::istringstream
#include <string>     // std::string
#include <vector>     // std::vector
#include <cctype>     // std::isalpha

namespace lab_comps {

Formula::Formula(Table* table, const std::string& expression, const std::string& name):
    m_table{ table },
    m_name{ name },
    m_expression{ expression } {
    
    // 1. Проверить, что есть указатель на таблицу
    if (m_table == nullptr) {
        std::cout << "[Formula] Ошибка: нет указателя на таблицу\n";
        return;
    }
    // 2. Обработать исходное выражение
    parseExpression();

    // 3. Проверить, что все используемые переменные есть где-то в таблице
    if (!validate()) {
        std::cout << "[Formula] Ошибка: не все переменные найдены в таблице (правило №4)\n";
        return;
    }
    std::cout << "[Formula] Создана: " << m_name << "\n";
}

Formula::~Formula() {
    std::cout << "[Formula] Уничтожена: " << m_name << "\n";
}

void Formula::setTable(Table* table) {
    m_table = table;
    std::cout << "[Formula] Теперь привязана к таблице: " << m_table->getName() << "\n";
}

const std::string& Formula::getName() const {
    return m_name;
}

const std::string& Formula::getExpression() const {
    return m_expression;
}

const std::vector<std::string>& Formula::getVars() const {
    return m_vars;
}

void Formula::parseExpression() {
    // TODO: реальный парсер
    // Пока — заглушка
    std::istringstream iss(m_expression);
    std::string token;
    while (iss >> token) {
        m_postfix.push_back(token);
        if (std::isalpha(token[0])) {
            m_vars.push_back(token);
        }
    }
}

bool Formula::validate() {
    for (auto& var : m_vars) {
        bool found = false;
        for (auto* col : m_table->getColumns()) {
            if (col->getVar() == var) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

double Formula::evaluate(const std::map<std::string, double>& vars) const {
    // TODO: реальный парсер
    // Пока — заглушка
    return 42.0;  // ← ответ на всё
}

} // namespace lab_comps