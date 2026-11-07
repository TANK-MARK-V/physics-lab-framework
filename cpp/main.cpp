#include "base_column.hpp"
#include "input_column.hpp"
#include "formula_column.hpp"
#include "constant_column.hpp"
#include "strategies.hpp"
#include "exceptions.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <clocale>
#include <cstdlib>

using namespace lab_comps;

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

    std::cout << "=== ЛР-5: Полиморфизм, интерфейсы, исключения ===\n\n";

    // ========== 1. ИНТЕРФЕЙС ICalculable ==========
    std::cout << "--- 1. Интерфейс ICalculable ---\n";
    
    std::vector<std::unique_ptr<BaseColumn>> columns;
    columns.push_back(std::make_unique<InputColumn>("a", "a", 2));
    columns.push_back(std::make_unique<InputColumn>("t", "t", 2));
    
    // Формула
    columns.push_back(std::make_unique<FormulaColumn>(
        "v", "v", 2, std::make_unique<FormulaEvaluation>("a t")));
    
    // Сумма
    columns.push_back(std::make_unique<FormulaColumn>(
        "sum", "sum", 2, std::make_unique<SumEvaluation>()));
    
    // Константа
    columns.push_back(std::make_unique<ConstantColumn>("g", "g", 2, 9.8));

    // ========== 2. МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ ==========
    std::cout << "\n--- 2. Множественное наследование (BaseColumn + ICalculable) ---\n";
    for (const auto& col : columns) {
        if (auto* calc = dynamic_cast<ICalculable*>(col.get())) {
            std::cout << "Колонка " << col->GetName() << " реализует ICalculable\n";
        } else {
            std::cout << "Колонка " << col->GetName() << " НЕ реализует ICalculable\n";
        }
    }

    // ========== 3. РАННЕЕ И ПОЗДНЕЕ СВЯЗЫВАНИЕ ==========
    std::cout << "\n--- 3. Раннее и позднее связывание ---\n";
    std::unique_ptr<BaseColumn> basePtr = std::make_unique<FormulaColumn>(
        "test", "test", 2, std::make_unique<SimpleEvaluation>());
    
    std::cout << "Невиртуальный метод (раннее): " << basePtr->GetName() << "\n";
    std::cout << "Виртуальный метод (позднее): " << basePtr->Describe() << "\n";

    // ========== 4. ПРОВЕРКА ТИПА (dynamic_cast) ==========
    std::cout << "\n--- 4. dynamic_cast: вычисляем только ICalculable ---\n";
    for (const auto& col : columns) {
        if (auto* calc = dynamic_cast<ICalculable*>(col.get())) {
            std::cout << "Вычисляем " << col->GetName() << ":\n";
            calc->Calculate();
        } else {
            std::cout << col->GetName() << ": не требует вычисления\n";
        }
    }

    // ========== 5. ДИНАМИЧЕСКОЕ КОНФИГУРИРОВАНИЕ ==========
    std::cout << "\n--- 5. Динамическое конфигурирование ---\n";
    auto dynamicCol = std::make_unique<FormulaColumn>(
        "dyn", "dyn", 2, std::make_unique<SimpleEvaluation>());
    
    std::cout << "Стратегия 1:\n";
    dynamicCol->Calculate();
    
    std::cout << "Меняем на SumEvaluation:\n";
    dynamicCol->SetStrategy(std::make_unique<SumEvaluation>());
    dynamicCol->Calculate();

    // ========== 6. ИСКЛЮЧЕНИЯ ==========
    std::cout << "\n--- 6. Исключения ---\n";
    try {
        auto badCol = std::make_unique<InputColumn>("bad", "bad", -5);
    } 
    catch (const InvalidPrecisionError& e) {
        std::cout << "Поймано частное исключение: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "Поймано общее: " << e.what() << "\n";
    }

    std::cout << "\n=== КОНЕЦ ===\n";
    return 0;
}