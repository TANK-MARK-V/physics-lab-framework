#include "table.hpp"
#include "base_column.hpp"
#include "input_column.hpp"
#include "formula_column.hpp"
#include "constant_column.hpp"
#include "strategies.hpp"
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

    // =====================================================================
    // ШАБЛОННАЯ ФУНКЦИЯ С КОНЦЕПТОМ
    // =====================================================================
    std::cout << "\n--- Шаблонная функция Average ---\n";
    
    // Вызов с int
    std::vector<int> ints = {1, 2, 3, 4, 5};
    std::cout << "Среднее (int): " << Average(ints) << "\n";
    
    // Вызов с double
    std::vector<double> doubles = {1.5, 2.5, 3.5};
    std::cout << "Среднее (double): " << Average(doubles) << "\n";
    
    // Вызов с float
    std::vector<float> floats = {1.0f, 2.0f, 3.0f};
    std::cout << "Среднее (float): " << Average(floats) << "\n";

    // Демонстрация того, что концепт работает (этот код не скомпилируется, если раскомментировать):
    // std::vector<std::string> strings = {"a", "b"};
    // std::cout << Average(strings); // Ошибка компиляции: std::string не является Numeric

    // =====================================================================
    // ШАБЛОННЫЙ КЛАСС ColumnContainer И ШАБЛОННЫЙ МЕТОД
    // =====================================================================
    std::cout << "\n--- Шаблонный класс ColumnContainer ---\n";

    // Создаем контейнер для конкретных колонок ввода
    ColumnContainer<InputColumn> inputContainer;
    inputContainer.Add(std::make_unique<InputColumn>("alpha", "alpha", 2));
    inputContainer.Add(std::make_unique<InputColumn>("beta", "beta", 2));
    
    // Создаем общий контейнер для BaseColumn
    ColumnContainer<BaseColumn> allContainer;
    allContainer.Add(std::make_unique<ConstantColumn>("g", "g", 2, 9.81));

    // Демонстрация шаблонного метода MergeFrom
    // Переливаем колонки из inputContainer (U = InputColumn) в allContainer (T = BaseColumn)
    allContainer.MergeFrom(inputContainer);

    std::cout << "Размер общего контейнера: " << allContainer.Size() << "\n";
    for (std::size_t i = 0; i < allContainer.Size(); ++i) {
        std::cout << "  Элемент [" << i << "]: " << allContainer[i] << "\n";
    }

    // Демонстрация того, что концепт работает (если раскомментировать, будет ошибка компиляции):
    // ColumnContainer<int> invalidContainer; // Ошибка: int не является наследником BaseColumn

    std::cout << "\n=== КОНЕЦ ===\n";
    return 0;
}