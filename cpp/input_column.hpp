#pragma once

#include "base_column.hpp"

namespace lab_comps {

class InputColumn : public BaseColumn {
public:
    InputColumn(std::string name, std::string var, int precision);
    
    ~InputColumn() override;  // virtual
    
    std::string GetType() const override;
    std::string Describe() const override;  // с вызовом базы
    std::unique_ptr<BaseColumn> Clone() const override;
};

} // namespace lab_comps