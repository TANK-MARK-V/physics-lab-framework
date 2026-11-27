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
#include "algorithms_demo.hpp"
#include "calculation_result.hpp"

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

    std::cout << "=== ЛР-7: Статический полиморфизм ===\n";

    // =====================================================================
    // ДЕМОНСТРАЦИЯ АЛГОРИТМОВ
    // =====================================================================
    RunAlgorithmsDemo();

    // ==============================================================
    // ДЕМОНСТРАЦИЯ std::variant и std::visit
    // ==============================================================
    std::cout << "\n--- std::variant ---\n";

    CalculationResult res1 = NumberResult{ 42.5 };
    CalculationResult res2 = ErrorResult{ PhysicalQuantity(10.5, 0.2) };
    CalculationResult res3 = TextResult{ "Неизвестная переменная" };

    PrintResult(res1);
    PrintResult(res2);
    PrintResult(res3);

    std::cout << "\n=== КОНЕЦ ===\n";
    return 0;
}