#pragma once

#include "base_column.hpp"
#include "icalculable.hpp"

namespace lab_comps {

class ConstantColumn final : public BaseColumn, public ICalculable {
private:
    double m_value;
    bool m_isCalculated{ false };

public:
    ConstantColumn(std::string name, std::string var, 
                   int precision, double value);

    ~ConstantColumn() override;  // virtual

    std::string GetType() const override;
    std::string Describe() const override;
    std::unique_ptr<BaseColumn> Clone() const override;

    // Реализация ICalculable
    void Calculate() override;
    bool IsCalculated() const override { return m_isCalculated; }
};

} // namespace lab_comps