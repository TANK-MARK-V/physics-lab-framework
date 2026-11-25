#pragma once
#include "ievaluation_strategy.hpp"

namespace lab_comps {

// Стратегия 1: Простая заглушка (как было раньше)
class SimpleEvaluation : public IEvaluationStrategy {
public:
    double Evaluate(const std::map<std::string, double>& vars) const override { return 42.0; }
    
    std::string GetView() const override { return "Заглушка (42.0)"; }
    
    std::unique_ptr<IEvaluationStrategy> Clone() const override {
        return std::make_unique<SimpleEvaluation>(*this);
    }
};

// Стратегия 2: Сумма всех переменных
class SumEvaluation : public IEvaluationStrategy {
public:
    double Evaluate(const std::map<std::string, double>& vars) const override {
        double sum = 0.0;
        for (const auto& kv : vars) {
            sum += kv.second;
        }
        return sum;
    }
    
    std::string GetView() const override { return "Сумма переменных"; }
    
    std::unique_ptr<IEvaluationStrategy> Clone() const override {
        return std::make_unique<SumEvaluation>(*this);
    }
};

// Стратегия 3: Формула (заменяет старую Formula)
class FormulaEvaluation : public IEvaluationStrategy {
private:
    std::string m_expression;

public:
    explicit FormulaEvaluation(std::string expression) : m_expression(std::move(expression)) {}
    
    double Evaluate(const std::map<std::string, double>& vars) const override { return 42.0; }
    
    std::string GetView() const override { return "Формула: " + m_expression; }
    
    std::unique_ptr<IEvaluationStrategy> Clone() const override {
        return std::make_unique<FormulaEvaluation>(m_expression);
    }
};

} // namespace lab_comps