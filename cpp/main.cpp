#include "table.hpp"
#include "base_column.hpp"
#include "input_column.hpp"
#include "formula_column.hpp"
#include "constant_column.hpp"
#include "strategies.hpp"
#include "exceptions.hpp"
#include "physical_quantity.hpp"

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

    // =====================================================================
    // ПЕРЕГРУЗКА ОПЕРАТОРОВ (PhysicalQuantity)
    // =====================================================================
    std::cout << "\n--- Перегрузка операторов (PhysicalQuantity) ---\n";
    
    PhysicalQuantity q1(10.5, 0.1);
    PhysicalQuantity q2(5.2, 0.2);
    
    PhysicalQuantity q3 = q1 + q2; // Работает operator+
    std::cout << "q1 + q2 = " << q3 << "\n"; // Работает operator<<
    
    q3 += q1; // Работает operator+=
    std::cout << "q3 += q1 = " << q3 << "\n";
    
    std::cout << std::boolalpha; // Чтобы bool выводился как true/false
    std::cout << "q1 == q2: " << (q1 == q2) << "\n"; // Работает operator== (из <=>)
    std::cout << "q1 > q2:  " << (q1 > q2) << "\n";  // Работает operator> (из <=>)

    // =====================================================================
    // ПЕРЕГРУЗКА ФУНКЦИЙ И ДРУЖЕСТВЕННЫЙ ВЫВОД
    // =====================================================================
    std::cout << "\n--- 8. Перегрузка функций и вывод в поток ---\n";

    // Создаем тестовую таблицу (предполагается, что Table уже умеет создавать колонки)
    Table myTable("Тестовая", 3);
    myTable.CreateInputColumn("Угол", "alpha", 2);
    myTable.CreateConstantColumn("Гравитация", "g", 2, 9.81);

    // Проверка перегрузки FindColumn по имени
    BaseColumn* colByName = myTable.FindColumn("alpha");
    if (colByName) {
        // Проверка дружественного operator<<
        std::cout << "Найдено по имени: " << *colByName << "\n";
    }

    // Проверка перегрузки FindColumn по ID
    // (ID колонки "g" будет на 1 больше, чем ID колонки "alpha")
    int targetId = colByName->GetId() + 1;
    BaseColumn* colById = myTable.FindColumn(targetId);
    if (colById) {
        std::cout << "Найдено по ID(" << targetId << "): " << *colById << "\n";
    }

    std::cout << "\n=== КОНЕЦ ===\n";
    return 0;
}