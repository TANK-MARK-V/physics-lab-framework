#include "base_column.hpp"

#include <iostream>
#include <utility>

namespace lab_comps {

BaseColumn::BaseColumn(std::string name, std::string var, int precision)
    : m_name{ std::move(name) }
    , m_var{ std::move(var) }
    , m_precision{ precision }
    , m_id{ NextId() }
{
    ValidatePrecision();
    std::cout << "[BaseColumn] Создана: " << m_name 
              << " (ID: " << m_id << ")\n";
}

BaseColumn::BaseColumn(const BaseColumn& other)
    : m_name{ other.m_name }
    , m_var{ other.m_var }
    , m_precision{ other.m_precision }
    , m_data{ other.m_data }
    , m_id{ NextId() }
{
    std::cout << "[BaseColumn] Копия: " << m_name 
              << " (ID: " << m_id << ")\n";
}

BaseColumn::BaseColumn(BaseColumn&& other) noexcept
    : m_name{ std::move(other.m_name) }
    , m_var{ std::move(other.m_var) }
    , m_precision{ other.m_precision }
    , m_data{ std::move(other.m_data) }
    , m_id{ other.m_id }
{
    std::cout << "[BaseColumn] Перемещение: " << m_name << "\n";
}

BaseColumn& BaseColumn::operator=(const BaseColumn& other) {
    if (this == &other) return *this;  // this: самоприсваивание
    m_name = other.m_name;
    m_var = other.m_var;
    m_precision = other.m_precision;
    m_data = other.m_data;
    return *this;
}

BaseColumn& BaseColumn::operator=(BaseColumn&& other) noexcept {
    if (this == &other) return *this;
    m_name = std::move(other.m_name);
    m_var = std::move(other.m_var);
    m_precision = other.m_precision;
    m_data = std::move(other.m_data);
    return *this;
}

BaseColumn::~BaseColumn() {
    std::cout << "[BaseColumn] Уничтожена: " << m_name << "\n";
}

int BaseColumn::m_lastId = 0;

void BaseColumn::Calculate() {
    std::cout << "[BaseColumn] Calculate по умолчанию\n";
}

std::string BaseColumn::Describe() const {
    // std::string: конкатенация
    std::string result = m_var + " (" + m_name + ")";
    
    // std::string: find
    if (m_name.find("temp") != std::string::npos) {
        result += " [временная]";
    }
    
    return result;
}

void BaseColumn::SetPrecision(int precision) {
    m_precision = precision;
    ValidatePrecision();
}

void BaseColumn::AddToRegistry(std::vector<BaseColumn*>& registry) {
    registry.push_back(this);  // передача *this
}

} // namespace lab_comps