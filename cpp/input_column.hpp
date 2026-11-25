#pragma once

#include "base_column.hpp"
#include "icalculable.hpp"

namespace lab_comps {

class InputColumn : public BaseColumn, public ICalculable {
private:
    bool m_isCalculated{ false };

public:
    InputColumn(std::string name, std::string var, int precision);
    
    ~InputColumn() override;  // virtual
    
    std::string GetType() const override;
    std::string Describe() const override;  // с вызовом базы
    std::unique_ptr<BaseColumn> Clone() const override;

    // Реализация ICalculable
    void Calculate() override;
    bool IsCalculated() const override { return m_isCalculated; }
};

} // namespace lab_comps