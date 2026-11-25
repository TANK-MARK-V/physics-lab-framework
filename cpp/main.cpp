#include "table/table.hpp"
#include "table/table_calculator.hpp"
#include "columns/base_column.hpp"
#include "columns/input_column.hpp"
#include "columns/formula_column.hpp"
#include "columns/constant_column.hpp"
#include "strategies/strategies.hpp"
#include "exceptions.hpp"
#include "physical_quantity.hpp"
#include "calculations.hpp"
#include "column_container.hpp"

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

    std::cout << "=== ЛР-6: Статический полиморфизм ===\n";

    // =====================================================================
    // 1. ПЕРЕГРУЗКА ФУНКЦИЙ И МЕТОДОВ
    // =====================================================================
    std::cout << "\n--- 1. Перегрузка функций (поиск в таблице) ---\n";
    
    Table myTable("Тестовая таблица", 3);
    myTable.CreateInputColumn("Угол", "alpha", 2);
    myTable.CreateConstantColumn("Гравитация", "g", 2, 9.81);

    // Поиск по имени (var)
    BaseColumn* colByName = myTable.FindColumn("alpha");
    if (colByName) {
        std::cout << "Найдено по имени: " << *colByName << "\n";
    }

    // Поиск по ID
    int targetId = colByName->GetId() + 1;
    BaseColumn* colById = myTable.FindColumn(targetId);
    if (colById) {
        std::cout << "Найдено по ID(" << targetId << "): " << *colById << "\n";
    }

    // =====================================================================
    // 2. ПЕРЕГРУЗКА ОПЕРАТОРОВ
    // =====================================================================
    std::cout << "\n--- 2. Перегрузка операторов (PhysicalQuantity) ---\n";
    
    PhysicalQuantity q1(10.5, 0.1);
    PhysicalQuantity q2(5.2, 0.2);
    
    // Арифметические операторы (+ и +=)
    PhysicalQuantity q3 = q1 + q2; 
    std::cout << "q1 + q2 = " << q3 << "\n";
    
    q3 += q1; 
    std::cout << "q3 += q1 = " << q3 << "\n";
    
    // Операторы сравнения (==, > из <=>)
    std::cout << std::boolalpha; 
    std::cout << "q1 == q2: " << (q1 == q2) << "\n";
    std::cout << "q1 > q2:  " << (q1 > q2) << "\n";

    // =====================================================================
    // 3. ДРУЖЕСТВЕННЫЕ ФУНКЦИИ
    // =====================================================================
    std::cout << "\n--- 3. Дружественные функции (operator<<) ---\n";
    
    // Дружественная функция для значимого класса
    std::cout << "Вывод PhysicalQuantity: " << q1 << "\n";
    
    // Дружественная (свободная) функция для иерархии
    std::cout << "Вывод иерархии через базовый класс:\n";
    std::cout << "  " << *colByName << "\n"; // Выведет InputColumn
    std::cout << "  " << *colById << "\n";   // Выведет ConstantColumn

    // =====================================================================
    // 4. ШАБЛОННАЯ ФУНКЦИЯ С КОНЦЕПТОМ
    // =====================================================================
    std::cout << "\n--- 4. Шаблонная функция Average ---\n";
    
    // Вызов с int
    std::vector<int> ints = {1, 2, 3, 4, 5};
    std::cout << "Среднее (int): " << Average(ints) << "\n";
    
    // Вызов с double
    std::vector<double> doubles = {1.5, 2.5, 3.5};
    std::cout << "Среднее (double): " << Average(doubles) << "\n";

    // Вызов с float
    std::vector<float> floats = {1.0f, 2.0f, 3.0f};
    std::cout << "Среднее (float): " << Average(floats) << "\n";

    // Демонстрация ограничения концепта (не скомпилируется, если раскомментировать):
    // std::vector<std::string> strings = {"a", "b"};
    // std::cout << Average(strings); 

    // =====================================================================
    // 5. ШАБЛОННЫЙ КЛАСС И ШАБЛОННЫЙ МЕТОД
    // =====================================================================
    std::cout << "\n--- 5. Шаблонный класс ColumnContainer ---\n";

    // Шаблон используется с типом 1: InputColumn
    ColumnContainer<InputColumn> inputContainer;
    inputContainer.Add(std::make_unique<InputColumn>("angle_1", "a1", 2));
    inputContainer.Add(std::make_unique<InputColumn>("angle_2", "a2", 2));
    
    // Шаблон используется с типом 2: BaseColumn
    ColumnContainer<BaseColumn> allContainer;
    allContainer.Add(std::make_unique<ConstantColumn>("g", "g", 2, 9.81));

    // Демонстрация шаблонного метода MergeFrom
    std::cout << "Переливаем InputColumn в BaseColumn...\n";
    allContainer.MergeFrom(inputContainer);

    std::cout << "Размер общего контейнера: " << allContainer.Size() << "\n";
    for (std::size_t i = 0; i < allContainer.Size(); ++i) {
        std::cout << "  Элемент [" << i << "]: " << allContainer[i] << "\n";
    }

    // Демонстрация ограничения std::derived_from (не скомпилируется, если раскомментировать):
    // ColumnContainer<int> invalidContainer; 

    std::cout << "\n=== КОНЕЦ ===\n";
    return 0;
}