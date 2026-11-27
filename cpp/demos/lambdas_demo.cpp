#include "lambdas_demo.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

namespace lab_comps {

// Вспомогательный класс для демонстрации захвата [this]
class LambdaDemoClass {
private:
    int m_limit = 10;
public:
    void Run() {
        // Захват [this] позволяет лямбде обращаться к полям класса
        auto printLimit = [this]() {
            std::cout << "Текущий лимит из класса (через this): " << m_limit << "\n";
        };
        printLimit();
        m_limit = 20;
        printLimit(); // Выведет 20, так как захвачен указатель this
    }
};

void RunLambdasDemo() {
    std::cout << "\n--- ДЕМОНСТРАЦИЯ ЛЯМБД И ЗАХВАТА ---\n";

    // ==============================================================
    // 1. Захват по значению и по ссылке
    // ==============================================================
    int threshold = 5;

    // Захват по значению (копия на момент создания)
    auto byValue = [threshold]() {
        std::cout << "Лямбда по значению видит: " << threshold << "\n";
    };

    // Захват по ссылке
    auto byReference = [&threshold]() {
        std::cout << "Лямбда по ссылке видит: " << threshold << "\n";
    };

    byValue();     // Выведет 5
    byReference(); // Выведет 5

    threshold = 15; // Меняем переменную

    std::cout << "--- После изменения threshold = 15 ---\n";
    byValue();     // Выведет 5 (копия)
    byReference(); // Выведет 15 (ссылка)

    // ==============================================================
    // 2. Захват [this]
    // ==============================================================
    LambdaDemoClass demoObj;
    demoObj.Run();

    // ==============================================================
    // 3. Обобщённая лямбда (auto)
    // ==============================================================
    std::cout << "\n--- Обобщённая лямбда ---\n";
    
    // Эта лямбда может принимать любой контейнер (вектор, список, массив)
    auto printContainer = [](const auto& container) {
        std::cout << "Элементы: ";
        for (const auto& element : container) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    };

    std::vector<int> vec = {1, 2, 3};
    std::list<std::string> lst = {"alpha", "beta", "gamma"};
    int arr[] = {10, 20, 30};

    printContainer(vec);
    printContainer(lst);
    printContainer(arr);
}

} // namespace lab_comps