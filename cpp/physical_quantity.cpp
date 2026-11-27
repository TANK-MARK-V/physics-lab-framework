#include "physical_quantity.hpp"

namespace lab_comps {

PhysicalQuantity::PhysicalQuantity(double value, double error)
    : m_value{ value }, m_error{ std::abs(error) } // Погрешность всегда положительная
{
    std::cout << "[PhysicalQuantity] Создана: " << m_value << " ± " << m_error << "\n";
}

PhysicalQuantity::~PhysicalQuantity() {
    // Оставим пустым, чтобы не засорять консоль
}

} // namespace lab_comps