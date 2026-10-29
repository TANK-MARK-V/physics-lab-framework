#include "input_column.hpp"

#include <iostream>

namespace lab_comps {

InputColumn::InputColumn(std::string name, std::string var, int precision)
    : BaseColumn{ std::move(name), std::move(var), precision }
{
    std::cout << "[InputColumn] Создана\n";
}

InputColumn::~InputColumn() {
    std::cout << "[InputColumn] Уничтожена: " << m_name << "\n";
}

std::string InputColumn::GetType() const {
    return "Input";
}

std::string InputColumn::Describe() const {
    // с вызовом базового метода
    return BaseColumn::Describe() + " [ввод]";
}

std::unique_ptr<BaseColumn> InputColumn::Clone() const {
    return std::make_unique<InputColumn>(*this);
}

} // namespace lab_comps