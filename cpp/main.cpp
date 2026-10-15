#include "table.hpp"
#include "column.hpp"
#include "formula.hpp"

#include <iostream>
#include <memory>
#include <clocale>
#include <cstdlib>

using namespace lab_comps;

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

    std::cout << "=== ЛР-3: C++ (умные указатели) ===\n";

    // ========== 1. UNIQUE_PTR: один владелец ==========
    std::cout << "\n--- 1. unique_ptr ---\n";
    {
        auto table = std::make_unique<Table>("Демо", 3);
        std::cout << "Таблица создана\n";
    }  // ← table уничтожена автоматически, delete не нужен

    // ========== 2. АГРЕГАЦИЯ + SHARED_PTR ==========
    std::cout << "\n--- 2. shared_ptr: несколько владельцев ---\n";
    auto formula = std::make_shared<Formula>("Скорость", "a t");
    std::cout << "use_count: " << formula.use_count() << "\n";  // 1

    {
        auto table = std::make_unique<Table>("Демо", 3);
        
        // Table сам создаёт колонки (композиция)
        table->CreateColumn("a", "a", 2);
        table->CreateColumn("t", "t", 2);
        
        // Данные
        table->SetColumnData("a", {5, 5, 5});
        table->SetColumnData("t", {1, 2, 3});
        
        // Агрегация: формула снаружи
        table->CreateColumn("v", "v", 2, formula);
        std::cout << "use_count после CreateColumn: " << formula.use_count() << "\n";  // 2
        
        // Расчёт
        table->Calculate();
    }  // ← table уничтожена, колонки тоже, но formula жива

    std::cout << "use_count после уничтожения table: " << formula.use_count() << "\n";  // 1

    // ========== 3. WEAK_PTR: наблюдатель ==========
    std::cout << "\n--- 3. weak_ptr: наблюдатель ---\n";
    std::weak_ptr<Formula> weakFormula = formula;
    std::cout << "use_count с weak: " << formula.use_count() << "\n";  // 1 (weak не считается)

    if (auto locked = weakFormula.lock()) {
        std::cout << "Формула жива: " << locked->GetName() << "\n";
    } else {
        std::cout << "Формула уничтожена\n";
    }

    formula.reset();  // ← последний владелец ушёл
    std::cout << "use_count после reset: " << formula.use_count() << "\n";  // 0

    if (auto locked = weakFormula.lock()) {
        std::cout << "Формула жива: " << locked->GetName() << "\n";
    } else {
        std::cout << "Формула уничтожена\n";  // ← сюда
    }

    // ========== 4. МАССИВ ОБЪЕКТОВ ==========
    std::cout << "\n--- 4. unique_ptr<T[]> (массив объектов) ---\n";
    {
        auto tables = std::make_unique<Table[]>(2);  // ← нужно Table()
        std::cout << "Массив из 2 таблиц создан\n";
    }  // ← автоматически удалён

    // ========== 5. МАССИВ УКАЗАТЕЛЕЙ ==========
    std::cout << "\n--- 5. vector<unique_ptr<Table>> (массив указателей) ---\n";
    {
        std::vector<std::unique_ptr<Table>> tables;
        tables.push_back(std::make_unique<Table>("Таблица 0", 1));
        tables.push_back(std::make_unique<Table>("Таблица 1", 1));
        std::cout << "Массив указателей создан\n";
    }  // ← автоматически удалён

    std::cout << "\n=== КОНЕЦ ===\n";
    return 0;
}