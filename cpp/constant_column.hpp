#pragma once

#include "base_column.hpp"

namespace lab_comps {

class ConstantColumn final : public BaseColumn {  // final
private:
    double m_value;

public:
    ConstantColumn(std::string name, std::string var, 
                   int precision, double value);

    ~ConstantColumn() override;  // virtual

    std::string GetType() const override;
    std::string Describe() const override;
    std::unique_ptr<BaseColumn> Clone() const override;
};

} // namespace lab_comps