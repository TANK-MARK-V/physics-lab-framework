#include "table.hpp"
#include "column.hpp"
#include "formula.hpp"

#include <iostream>
#include <clocale>
#include <cstdlib>

using namespace lab_comps;

// Функция по ссылке
void printTableRef(Table& table) {
    std::cout << "\n[printTableRef] Таблица: " << table.getName() << "\n";
    for (auto* col : table.getColumns()) {
        std::cout << "  Столбец: " << col->getVar() << "\n";
    }
}

// Функция по указателю
void printTablePtr(Table* table) {
    if (table == nullptr) return;
    std::cout << "\n[printTablePtr] Таблица: " << table->getName() << "\n";
    for (auto* col : table->getColumns()) {
        std::cout << "  Столбец: " << col->getVar() << "\n";
    }
}

int main() {
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #else
        setlocale(LC_ALL, "ru_RU.UTF-8");
    #endif
    std::cout << "=== Поехали ===\n";

    std::cout << "\n=== 0. ПОДГОТОВКА ДЛЯ АГРЕГАЦИИ: создаём Formula снаружи ===\n";
    Table* formulaTable = new Table("ДляФормулы", 0);
    std::cout << "\n=== 0.1. ПОДГОТОВКА ДЛЯ АГРЕГАЦИИ: создаём неправильную Formula (с несуществующими переменными) ===\n";
    Formula* formula = new Formula(formulaTable, "l + R", "Формула для агрегации (v)");
    delete formula;
    std::cout << "\n=== 0.2. ПОДГОТОВКА ДЛЯ АГРЕГАЦИИ: создаём правильную Formula (без переменных) ===\n";
    formula = new Formula(formulaTable, "1 + 1", "Формула для агрегации (v)");


    std::cout << "\n=== 1. КОМПОЗИЦИЯ: Table создаёт Column ===\n";
    {
        Table table("Демо", 3);  // Статическая инициализация

        std::cout << "\n=== 1.2. КОМПОЗИЦИЯ: создаём правильную колонку (точность >= 0)===\n";
        Column* colA = new Column(&table, "a", "a", 2);
        std::cout << "\n=== 1.2. КОМПОЗИЦИЯ: создаём неправильную колонку (точность < 0) ===\n";
        Column* colT = new Column(&table, "t", "t", -1);
        
        colA->setData({5, 5, 5});
        colT->setData({1, 2, 3});
        
        table.addColumn(colA);
        table.addColumn(colT);
        
        std::cout << "\n=== 2. АГРЕГАЦИЯ: связываем Formula и table ===\n";
        formula->setTable(&table);
        Column* colV = new Column(&table, "v", "v", 2);
        colV->setFormula(formula);
        table.addColumn(colV);
        
        std::cout << "\n=== 3. РАСЧЁТ ===\n";
        table.calculateColumns();
        
        std::cout << "\n=== 4. По ссылке ===\n";
        printTableRef(table);
        
        std::cout << "\n=== 5. По указателю ===\n";
        printTablePtr(&table);
        
        std::cout << "\n=== 6. Выход из области выдимости (уничтожение Демо) ===\n";
    }  // table уничтожается, колонки тоже, а формула - нет
    std::cout << "\n=== 7. Удаляем ненужное ===\n";
    delete formula;  // Удаляем формулу вручную
    delete formulaTable;  // Удаляем таблицу для формулы

    std::cout << "\n=== 8. ДИНАМИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ===\n";
    Table* dynTable = new Table("Динамическая", 2);
    delete dynTable;

    std::cout << "\n=== 9. МАССИВ ОБЪЕКТОВ ===\n";
    Table* tables = new Table[2];
    delete[] tables;

    std::cout << "\n=== 10. МАССИВ УКАЗАТЕЛЕЙ ===\n";
    Table** ptrs = new Table*[2];
    for (int i = 0; i < 2; i++) {
        ptrs[i] = new Table("Таблица " + std::to_string(i), 1);
    }
    for (int i = 0; i < 2; i++) {
        delete ptrs[i];
    }
    delete[] ptrs;

    std::cout << "\n=== КОНЕЦ ===\n";
    return 0;
}