#include "column.hpp"
#include "table.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>


namespace lab_comps {

Column::Column(Table* table, const std::string& name,
        const std::string& var, int precision):
    m_table{ table },
    m_name{ name },
    m_var{ var },
    m_precision{ precision },
    m_formula{ nullptr } {

    if (precision < 0) {
        // Пока просто обнуляем точность
        m_precision = 0;
        std::cout << "[Column] Нельзя создать колонку с отрицательной точностью (правило №5)\n";
    }
    std::cout << "[Column] Создана: " << m_name << " в таблице " << m_table->getName() << "\n";
}

Column::~Column() {
    std::cout << "[Column] Уничтожена: " << m_name << " в таблице " << m_table->getName() << "\n";
}

void Column::setData(const std::vector<double>& data) {
    m_data = data;
}

const std::string& Column::getVar() const {
    return m_var;
}

const std::vector<double>& Column::getData() const {
    return m_data;
}

const Formula* Column::getFormula() const {
    return m_formula;
}

bool Column::setFormula(Formula* formula) {
    // TODO: Добавить проверку на то, что формулу можно применить к этому столбцу
    m_formula = formula;
    return true;
}

bool Column::isReady() const {
    if (m_data.size() < m_table->getExperiments()) {
        return false;
    }
    return true;
}

bool Column::calculate() {
    // 1. Проверка: есть ли формула
    if (m_formula == nullptr) {
        std::cout << "[Column] Нет формулы\n";
        return false;
    }
    // 2. Получить список переменных, нужных формуле
    auto needVars = m_formula->getVars();
    // 3. Проверить, что все переменные есть и готовы
    int readyVars = 0;
    for (auto* col : m_table->getColumns()) {
        if (std::find(needVars.begin(), needVars.end(), col->getVar()) != needVars.end() 
            && col->isReady()) {
            readyVars++;
        }
    }
    if (readyVars != static_cast<int>(needVars.size())) {
        std::cout << "[Column] Не все зависимости заполнены (правило №1)\n";
        return false;
    }
    // 4. Вычислить для каждой строки
    int rows = m_table->getExperiments();
    m_data.clear();
    
    for (int row = 0; row < rows; row++) {
        // ← для каждой строки собираем СЛОВАРЬ
        std::map<std::string, double> vars;
        for (auto* col : m_table->getColumns()) {
            if (std::find(needVars.begin(), needVars.end(), col->getVar()) != needVars.end()) {
                vars[col->getVar()] = col->getData()[row];  // Берём значение
            }
        }
        // Вычисляем
        double result = m_formula->evaluate(vars);
        m_data.push_back(result);
    }
    
    std::cout << "[Column] Вычислен: " << m_name << "\n";
    return true;
}

}   // namespace lab_comps
