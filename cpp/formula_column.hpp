#pragma once

#include "base_column.hpp"
#include <memory>

namespace lab_comps {

class Formula;

class FormulaColumn : public BaseColumn {
private:
    std::shared_ptr<Formula> m_formula;

public:
    FormulaColumn(std::string name, std::string var, 
                  int precision, std::shared_ptr<Formula> formula);
    FormulaColumn(const FormulaColumn& other);

    FormulaColumn(FormulaColumn&& other) noexcept;              // перемещение
    FormulaColumn& operator=(const FormulaColumn& other);       // копирующее присваивание
    FormulaColumn& operator=(FormulaColumn&& other) noexcept;   // перемещающее присваивание

    ~FormulaColumn() override;  // virtual

    std::string GetType() const override;
    std::string Describe() const override;  // без вызова базы
    std::unique_ptr<BaseColumn> Clone() const override;
    void Calculate() override;              // своя реализация

    void SetFormula(std::shared_ptr<Formula> formula);

    [[nodiscard]] std::shared_ptr<Formula> GetFormula() const;

};

} // namespace lab_comps