#include "constant_column.hpp"

#include <iostream>

namespace lab_comps {

ConstantColumn::ConstantColumn(std::string name, std::string var, 
                               int precision, double value)
    : BaseColumn{ std::move(name), std::move(var), precision }
    , m_value{ value }
{
    std::cout << "[ConstantColumn] Создана\n";
}

ConstantColumn::~ConstantColumn() {
    std::cout << "[ConstantColumn] Уничтожена: " << m_name << "\n";
}

std::string ConstantColumn::GetType() const {
    return "Constant";
}

std::string ConstantColumn::Describe() const {
    return "Константа: " + m_name + " = " + std::to_string(m_value);
}

std::unique_ptr<BaseColumn> ConstantColumn::Clone() const {
    return std::make_unique<ConstantColumn>(*this);
}

} // namespace lab_comps