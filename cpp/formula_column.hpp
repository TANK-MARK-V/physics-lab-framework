#pragma once

#include "base_column.hpp"
#include "icalculable.hpp"
#include "ievaluation_strategy.hpp"
#include <memory>

namespace lab_comps {

class FormulaColumn : public BaseColumn, public ICalculable {
private:
    std::shared_ptr<IEvaluationStrategy> m_strategy;
    bool m_isCalculated{ false };

public:
    FormulaColumn(std::string name, std::string var, int precision, 
                  std::shared_ptr<IEvaluationStrategy> strategy);
    
    // --- ПРАВИЛО ПЯТИ ---
    FormulaColumn(const FormulaColumn& other);                  // Копирование (поверхностное)
    FormulaColumn(FormulaColumn&& other) noexcept;              // Перемещение
    FormulaColumn& operator=(const FormulaColumn& other);       // Копирующее присваивание (поверхностное)
    FormulaColumn& operator=(FormulaColumn&& other) noexcept;   // Перемещающее присваивание
    ~FormulaColumn() override;                                  // Деструктор
    // --------------------

    std::string GetType() const override;
    std::string Describe() const override;
    std::unique_ptr<BaseColumn> Clone() const override; // Глубокая копия

    void SetStrategy(std::shared_ptr<IEvaluationStrategy> strategy);

    void Calculate() override;
    bool IsCalculated() const override { return m_isCalculated; }
};

} // namespace lab_comps