#pragma once
#include <map>
#include <string>
#include <memory>

namespace lab_comps {

class IEvaluationStrategy {
public:
    virtual ~IEvaluationStrategy() = default;
    
    // Вычислить значение на основе переменных
    virtual double Evaluate(const std::map<std::string, double>& vars) const = 0;
    
    // Получить строковое представление (для вывода)
    virtual std::string GetView() const = 0; 
    
    // Для глубокой копии
    virtual std::unique_ptr<IEvaluationStrategy> Clone() const = 0;
};

} // namespace lab_comps