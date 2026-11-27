#include "algorithms_demo.hpp"
#include "measurement.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <map>
#include <numeric>

namespace lab_comps {

void RunAlgorithmsDemo() {
    std::cout << "\n--- ДЕМОНСТРАЦИЯ АЛГОРИТМОВ ---\n";

    std::vector<Measurement> measurements = {
        {"Иванов", "Угол", 30.5, 0.5, false},
        {"Петров", "Угол", 31.0, 1.2, true},
        {"Сидорова", "Масса", 10.2, 0.1, false},
        {"Козлов", "Масса", 10.5, 2.5, true},
        {"Смирнов", "Время", 5.0, 0.05, false}
    };

    // ==============================================================
    // 1. std::min_element / std::max_element
    // ==============================================================
    auto minErr = std::ranges::min_element(measurements, {}, &Measurement::error);
    std::cout << "Min погрешность: " << minErr->student << " (" << minErr->error << ")\n";
    
    auto maxErr = std::ranges::max_element(measurements, {}, &Measurement::error);
    std::cout << "Max погрешность: " << maxErr->student << " (" << maxErr->error << ")\n";

    // ==============================================================
    // 2. std::find / std::find_if
    // ==============================================================
    // find ищет по значению (например, по имени)
    auto found = std::ranges::find(measurements, "Смирнов", &Measurement::student);
    if (found != measurements.end()) {
        std::cout << "Найден по имени: " << found->student << "\n";
    }

    // find_if ищет по условию
    auto found_if = std::ranges::find_if(measurements, [](const Measurement& m) { 
        return m.error > 1.0; 
    });
    if (found_if != measurements.end()) {
        std::cout << "Найден с ошибкой > 1.0: " << found_if->student << "\n";
    }

    // ==============================================================
    // 3. std::copy / std::copy_if
    // ==============================================================
    std::vector<Measurement> copyVec;
    std::ranges::copy(measurements, std::back_inserter(copyVec)); // Копируем всё
    std::cout << "Скопировано элементов: " << copyVec.size() << "\n";

    std::vector<Measurement> badCopies;
    std::ranges::copy_if(measurements, std::back_inserter(badCopies), 
        [](const Measurement& m) { return m.error > 0.5; }); // Копируем с ошибкой > 0.5
    std::cout << "Скопировано с ошибкой > 0.5: " << badCopies.size() << "\n";

    // ==============================================================
    // 4. std::sort
    // ==============================================================
    std::ranges::sort(measurements, [](const Measurement& a, const Measurement& b) {
        return a.value < b.value;
    });
    std::cout << "Отсортировано по значению. Первый: " << measurements.front().value << "\n";

    // ==============================================================
    // 5. std::remove / std::remove_if (вместе с erase)
    // ==============================================================
    // ВАЖНО: std::remove не удаляет элементы, он сдвигает их.
    // Нужно обязательно вызывать .erase()
    auto new_end = std::remove_if(measurements.begin(), measurements.end(), 
        [](const Measurement& m) { return m.processed; });
    measurements.erase(new_end, measurements.end());
    std::cout << "После remove_if + erase (удалены обработанные): " << measurements.size() << "\n";

    // (Дополнительно покажем std::remove для конкретного значения)
    auto new_end_2 = std::remove(measurements.begin(), measurements.end(), 
        Measurement{"Смирнов", "Время", 5.0, 0.05, false});
    measurements.erase(new_end_2, measurements.end());
    std::cout << "После remove (удален Смирнов): " << measurements.size() << "\n";

    // ==============================================================
    // 6. std::views::filter
    // ==============================================================
    auto filteredView = measurements 
                      | std::views::filter([](const Measurement& m) { return m.error > 0.1; });
    
    std::cout << "Filtered (ошибка > 0.1): ";
    for (const auto& m : filteredView) std::cout << m.student << " ";
    std::cout << "\n";

    // ==============================================================
    // 7. std::transform / std::views::transform
    // ==============================================================
    // std::transform (создает новый вектор)
    std::vector<double> errors;
    std::transform(measurements.begin(), measurements.end(), std::back_inserter(errors), 
        [](const Measurement& m) { return m.error * 2.0; });
    std::cout << "Transform (ошибка * 2): " << errors.front() << "\n";

    // views::transform (ленивое преобразование)
    auto transformedView = measurements 
                         | std::views::transform([](const Measurement& m) { return m.student; });
    std::cout << "Views::transform (имена): ";
    for (const auto& name : transformedView) std::cout << name << " ";
    std::cout << "\n";

    // ==============================================================
    // 8. std::any_of
    // ==============================================================
    bool hasBigError = std::any_of(measurements.begin(), measurements.end(), 
        [](const Measurement& m) { return m.error > 1.0; });
    std::cout << "Any_of (есть ошибка > 1.0?): " << (hasBigError ? "Да" : "Нет") << "\n";
    
    // Бонус: std::none_of и std::all_of
    bool allProcessed = std::all_of(measurements.begin(), measurements.end(), 
        [](const Measurement& m) { return m.processed; });
    std::cout << "All_of (все обработаны?): " << (allProcessed ? "Да" : "Нет") << "\n";
}

} // namespace lab_comps