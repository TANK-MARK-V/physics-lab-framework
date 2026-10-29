#include "base_column.hpp"
#include "input_column.hpp"
#include "formula_column.hpp"
#include "constant_column.hpp"
#include "formula.hpp"

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

    std::cout << "=== ЛР-4: Наследование ===\n\n";

    // ========== 1. СОЗДАНИЕ ОБЪЕКТОВ ==========
    std::cout << "--- 1. Создание объектов ---\n";
    auto formula = std::make_shared<Formula>("Скорость", "a t");

    std::vector<std::unique_ptr<BaseColumn>> columns;
    columns.push_back(std::make_unique<InputColumn>("a", "a", 2));
    columns.push_back(std::make_unique<InputColumn>("t", "t", 2));
    columns.push_back(std::make_unique<FormulaColumn>("v", "v", 2, formula));
    columns.push_back(std::make_unique<ConstantColumn>("g", "g", 2, 9.8));

    // ========== 2. ВИРТУАЛЬНЫЙ ДЕСТРУКТОР ==========
    std::cout << "\n--- 2. Уничтожение через указатель на базу ---\n";
    {
        std::unique_ptr<BaseColumn> col = std::make_unique<FormulaColumn>(
            "test", "test", 2, formula);
        // при reset() вызовется ~FormulaColumn(), потом ~BaseColumn()
    }

    // ========== 3. КОПИРОВАНИЕ ==========
    std::cout << "\n--- 3. Копирование ---\n";

    // 1. Создаем оригинал с формулой "a t"
    auto original = std::make_unique<FormulaColumn>("v", "v", 2, formula);
    original->SetData({1.0, 2.0, 3.0});

    // 2. Поверхностное копирование (делит shared_ptr)
    FormulaColumn shallowCopy = *original;

    // 3. Глубокое копирование (создает свою формулу через Clone)
    auto deepCopy = original->Clone();

    // 4. МЕНЯЕМ ДАННЫЕ ВНУТРИ ФОРМУЛЫ У ОРИГИНАЛА (через SetExpression)
    // Теперь формула у оригинала = "x y", но объект тот же самый
    original->GetFormula()->SetExpression("x y");

    // 5. ПРОВЕРЯЕМ
    std::cout << "\n--- 3.1. Поверхностное (делит формулу) ---\n";
    std::cout << "original: " << original->Describe() << "\n";
    std::cout << "shallow:  " << shallowCopy.Describe() << "\n";
    // ОБА покажут "x y" потому что shallowCopy смотрит на ТУ ЖЕ формулу, 
    // которую только что изменили через original

    std::cout << "\n--- 3.2. Глубокое (своя формула) ---\n";
    std::cout << "original: " << original->Describe() << "\n";
    std::cout << "deep:     " << deepCopy->Describe() << "\n";
    // deep покажет "a t" потому что Clone() создал НОВУЮ формулу, 
    // и когда мы меняли "x y" у оригинала, deep об этом не знал

    // ========== 4. СТАТИЧЕСКИЙ СЧЁТЧИК ==========
    std::cout << "\n--- 4. Статический счётчик ---\n";
    for (auto& col : columns) {
        std::cout << "ID: " << col->GetId() 
                  << ", Type: " << col->GetType()
                  << ", Name: " << col->GetName() << "\n";
    }

    // ========== 5. ПОЛИМОРФИЗМ ==========
    std::cout << "\n--- 5. Полиморфизм ---\n";
    for (auto& col : columns) {
        col->Calculate();
        std::cout << col->Describe() << "\n";
    }

    // ========== 6. СТРОКИ ==========
    std::cout << "\n--- 6. Строки ---\n";
    std::string fullName = "v" + std::string(" (скорость)");
    std::cout << "Конкатенация: " << fullName << "\n";
    if (fullName.find("скорость") != std::string::npos) {
        std::cout << "Поиск: найдено\n";
    }
    std::cout << "Подстрока: " << fullName.substr(0, 3) << "\n";
    
    if (fullName == "v (скорость)") {
        std::cout << "Сравнение: равны\n";
    }

     // ========== 7. THIS: ПЕРЕДАЧА ТЕКУЩЕГО ОБЪЕКТА ==========
    std::cout << "\n--- 7. this: передача текущего объекта ---\n";
    
    std::vector<BaseColumn*> registry;
    for (auto& col : columns) {
        col->AddToRegistry(registry);  // ← передача *this
    }
    
    std::cout << "Зарегистрировано колонок: " << registry.size() << "\n";
    for (auto* col : registry) {
        std::cout << "  → " << col->GetName() 
                  << " (тип: " << col->GetType() << ")\n";
    }

    std::cout << "\n=== КОНЕЦ ===\n";
    return 0;
}