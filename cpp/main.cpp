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
#include <map>

using namespace lab_comps;

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

    std::cout << "=== ЛР-5: Полиморфизм, интерфейсы, исключения ===\n\n";

    // =====================================================================
    // 1. ИНТЕРФЕЙС ICalculable И МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ
    // =====================================================================
    std::cout << "--- 1. Интерфейс ICalculable и множественное наследование ---\n";
    
    std::vector<std::unique_ptr<BaseColumn>> columns;
    
    columns.push_back(std::make_unique<InputColumn>("a", "a", 2));
    columns.push_back(std::make_unique<InputColumn>("t", "t", 2));
    
    // Создаём колонку с формулой (стратегия FormulaEvaluation)
    columns.push_back(std::make_unique<FormulaColumn>(
        "v", "v", 2, std::make_unique<FormulaEvaluation>("a t")));
    
    // Создаём колонку с суммой (стратегия SumEvaluation)
    columns.push_back(std::make_unique<FormulaColumn>(
        "sum", "sum", 2, std::make_unique<SumEvaluation>()));
    
    // Константа
    columns.push_back(std::make_unique<ConstantColumn>("g", "g", 2, 9.8));

    // Проверяем, кто реализует ICalculable через dynamic_cast
    std::cout << "\nПроверка реализации ICalculable:\n";
    for (const auto& col : columns) {
        if (auto* calc = dynamic_cast<ICalculable*>(col.get())) {
            std::cout << "  " << col->GetName() << " -> реализует ICalculable\n";
        } else {
            std::cout << "  " << col->GetName() << " -> НЕ реализует ICalculable\n";
        }
    }

    // =====================================================================
    // 2. РАННЕЕ И ПОЗДНЕЕ СВЯЗЫВАНИЕ
    // =====================================================================
    std::cout << "\n--- 2. Раннее и позднее связывание ---\n";
    
    std::unique_ptr<BaseColumn> basePtr = std::make_unique<FormulaColumn>(
        "test", "test", 2, std::make_unique<SimpleEvaluation>());
    
    // GetName() — невиртуальный метод. Раннее связывание.
    std::cout << "Невиртуальный метод (раннее): " << basePtr->GetName() << "\n";
    
    // Describe() — виртуальный. Позднее связывание.
    std::cout << "Виртуальный метод (позднее): " << basePtr->Describe() << "\n";

    // =====================================================================
    // 3. DYNAMIC_CAST: ВЫЧИСЛЯЕМ ТОЛЬКО ICalculable
    // =====================================================================
    std::cout << "\n--- 3. dynamic_cast: вычисляем только ICalculable ---\n";
    
    for (const auto& col : columns) {
        if (auto* calc = dynamic_cast<ICalculable*>(col.get())) {
            std::cout << "Вычисляем " << col->GetName() << ":\n";
            calc->Calculate();
        } else {
            std::cout << col->GetName() << ": не требует вычисления (только данные)\n";
        }
    }

    // =====================================================================
    // 4. КОНФИГУРИРОВАНИЕ (ОБЪЕКТ ПОВЕДЕНИЯ)
    // =====================================================================
    std::cout << "\n--- 4. Конфигурирование (объект поведения) ---\n";
    
    auto dynamicCol = std::make_unique<FormulaColumn>(
        "dyn", "dyn", 2, std::make_unique<SimpleEvaluation>());
    
    std::cout << "Стратегия 1 (SimpleEvaluation):\n";
    dynamicCol->Calculate(); // 42.0
    
    std::cout << "\nМеняем стратегию на SumEvaluation:\n";
    dynamicCol->SetStrategy(std::make_unique<SumEvaluation>());
    dynamicCol->Calculate(); // 0 (так как vars пустая)

    // =====================================================================
    // 5. ИСКЛЮЧЕНИЯ
    // =====================================================================
    std::cout << "\n--- 5. Исключения (проверка точности) ---\n";
    
    // Успешное действие
    try {
        auto goodCol = std::make_unique<InputColumn>("good", "good", 2);
        std::cout << "Колонка 'good' создана успешно\n";
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
    
    // Нарушение правила
    try {
        auto badCol = std::make_unique<InputColumn>("bad", "bad", -5);
        std::cout << "Колонка создана (этого не должно быть!)\n";
    } 
    catch (const InvalidPrecisionError& e) { // Частное — первым
        std::cout << "Поймано частное исключение: " << e.what() << "\n";
    }
    catch (const std::exception& e) { // Общее — вторым
        std::cout << "Поймано общее исключение: " << e.what() << "\n";
    }

    // =====================================================================
    // 6. ГЛУБОКАЯ КОПИЯ (Clone)
    // =====================================================================
    std::cout << "\n--- 6. Глубокая копия (Clone) ---\n";
    
    auto original = std::make_unique<FormulaColumn>(
        "v", "v", 2, std::make_unique<FormulaEvaluation>("a t"));
    
    auto deepCopy = original->Clone();
    
    // Меняем стратегию у оригинала
    original->SetStrategy(std::make_unique<SumEvaluation>());
    
    std::cout << "original: " << original->Describe() << "\n";
    std::cout << "deep:     " << deepCopy->Describe() << "\n"; // Не изменится

    std::cout << "\n=== КОНЕЦ ===\n";
    return 0;
}