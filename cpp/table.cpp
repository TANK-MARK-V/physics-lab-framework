#include "table.hpp"

#include <iostream>

namespace lab_comps {

Table::Table():
    m_name{ "Таблица" },
    m_experiments{ 1 } {

    std::cout << "[Table] Создана: " << m_name << "\n";
}

Table::Table(const std::string& name, int experiments):
    m_name{ name },
    m_experiments{ experiments } {

    std::cout << "[Table] Создана: " << m_name << "\n";
}

Table::~Table() {
    for (auto* col : m_columns) {
        delete col;
    }
    std::cout << "[Table] Уничтожена: " << m_name << "\n";
}

const std::string& Table::getName() const {
    return m_name;
}

int Table::getExperiments() const {
    return m_experiments;
}

const std::vector<Column*>& Table::getColumns() const {
    return m_columns;
}


bool Table::addColumn(Column* column) {
    if (column == nullptr) {
        std::cout << "[Table] Ошибка: столбец не может быть nullptr\n";
        return false;
    }
    m_columns.push_back(column);
    std::cout << "[Table] Добавлен столбец\n";
    return true;
}

bool Table::calculateColumns() {
    for (auto* col : m_columns) {
        if (col->getFormula() != nullptr)
            col->calculate();
    }
    return true;
}

}   // namespace lab_comps
