#include "table/table.hpp"
#include "table/table_calculator.hpp"
#include "columns/base_column.hpp"
#include "columns/input_column.hpp"
#include "columns/formula_column.hpp"
#include "columns/constant_column.hpp"
#include "exceptions.hpp"
#include "physical_quantity.hpp"
#include "calculations.hpp"
#include "demos/algorithms_demo.hpp"
#include "demos/lambdas_demo.hpp"
#include "calculation_result.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <span>
#include <clocale>
#include <cstdlib>
#include <map>
#include <functional>

using namespace lab_comps;

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

    std::cout << "=== ЛР-7: Контейнеры, алгоритмы и лямбда-функции ===\n";

    // =====================================================================
    // 1. ДЕМОНСТРАЦИЯ ВСЕХ КОНТЕЙНЕРОВ
    // =====================================================================
    std::cout << "\n--- 1. Контейнеры: array, vector, span ---\n";

    // 1.1. std::array (Коэффициенты Стьюдента)
    constexpr std::array<double, 5> STUDENT_COEFFS = {0.0, 12.7, 4.3, 3.18, 2.78};
    std::cout << "Коэффициент Стьюдента для n=3: " << STUDENT_COEFFS[2] << "\n";

    // 1.2. std::vector (в TableCalculator)
    std::cout << "Использование std::vector в TableCalculator:\n";
    
    // Создаем колонки (владельцем будет Table, но для демо калькулятора создадим локально)
    InputColumn c1("Угол", "a", 2);
    ConstantColumn c2("g", "g", 2, 9.81);
    
    TableCalculator calc(3);
    calc.AddCol(&c1); // Добавится в pending (нет данных)
    calc.AddCol(&c2); // Добавится в pending
    
    std::cout << "  Готовых: " << calc.GetReadyCount() 
              << ", Ожидающих: " << calc.GetPendingCount() << "\n";
    

    // 1.3. std::span (Окно на данные)
    // Передаем часть вектора
    std::vector<double> results = {10.5, 20.1, 15.3, 8.9};
    std::span<const double> firstThree(results.begin(), 3);
    // ИСПРАВЛЕНИЕ: Явно указываем тип double для шаблона
    std::cout << "Среднее первых трех результатов: " << Average<double>(firstThree) << "\n";
    
    // Передаем весь std::array целиком
    std::cout << "Среднее коэффициентов: " << Average<double>(std::span(STUDENT_COEFFS)) << "\n";

    // 1.4. Обобщённая лямбда (вывод разных контейнеров)
    auto printContainer = [](const auto& container) {
        std::cout << "  Элементы: ";
        for (const auto& el : container) std::cout << el << " ";
        std::cout << "\n";
    };
    std::cout << "Обобщённая лямбда:\n";
    printContainer(results);        // Вектор
    printContainer(STUDENT_COEFFS); // Массив

    // =====================================================================
    // 2. КОНТЕЙНЕРЫ В TABLE (list и map)
    // =====================================================================
    std::cout << "\n--- 2. Контейнеры в Table (list, map) ---\n";
    
    Table myTable("Физика", 3);
    myTable.CreateInputColumn("Угол", "alpha", 2);
    myTable.CreateConstantColumn("Гравитация", "g", 2, 9.81);
    
    // Вставка в середину (благодаря std::list)
    myTable.InsertColumnAt(1, std::make_unique<ConstantColumn>("Пи", "pi", 2, 3.14));

    // Поиск по имени (через std::map)
    BaseColumn* col = myTable.FindColumn("pi");
    if (col) {
        std::cout << "Найдено через map: " << *col << "\n";
    }

    // =====================================================================
    // 3. СТРУКТУРА Measurement И АЛГОРИТМЫ
    // =====================================================================
    RunAlgorithmsDemo();

    // =====================================================================
    // 4. std::variant И std::visit
    // =====================================================================
    std::cout << "\n--- 4. std::variant ---\n";
    CalculationResult res1 = NumberResult{ 42.5 };
    CalculationResult res2 = ErrorResult{ PhysicalQuantity(10.5, 0.2) };
    CalculationResult res3 = TextResult{ "Неизвестная переменная" };

    PrintResult(res1);
    PrintResult(res2);
    PrintResult(res3);

    // =====================================================================
    // 5. ЛЯМБДЫ И ЗАХВАТ (демо в отдельном файле)
    // =====================================================================
    RunLambdasDemo();

    // =====================================================================
    // 6. std::function В ПОЛЕ (Замена стратегии)
    // =====================================================================
    std::cout << "\n--- 6. std::function в поле ---\n";
    
    // Лямбда 1: Возвращает 42
    FormulaColumn fCol("Тест", "test", 2, [](const std::map<std::string, double>&) { 
        return 42.0; 
    });
    fCol.Calculate();
    
    // Меняем поведение на сумму
    fCol.SetCalculator([](const std::map<std::string, double>& vars) {
        double sum = 0.0;
        for (const auto& kv : vars) sum += kv.second;
        return sum;
    });
    fCol.Calculate();


    std::cout << "\n=== КОНЕЦ ===\n";
    return 0;
}