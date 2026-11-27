package demos;

import java.util.*;

public class AlgorithmsDemo {

    public static void run() {
        System.out.println("\n--- ДЕМОНСТРАЦИЯ АЛГОРИТМОВ (Java Stream API) ---");

        // Исходные данные
        List<Measurement> measurements = new ArrayList<>(List.of(
            new Measurement("Иванов", "Угол", 30.5, 0.5, false),
            new Measurement("Петров", "Угол", 31.0, 1.2, true),
            new Measurement("Сидорова", "Масса", 10.2, 0.1, false),
            new Measurement("Козлов", "Масса", 10.5, 2.5, true),
            new Measurement("Смирнов", "Время", 5.0, 0.05, false)
        ));

        // 1. min / max (аналог min_element / max_element)
        Measurement minErr = Collections.min(measurements, Comparator.comparingDouble(m -> m.error));
        System.out.println("Min погрешность: " + minErr.student + " (" + minErr.error + ")");

        Measurement maxErr = Collections.max(measurements, Comparator.comparingDouble(m -> m.error));
        System.out.println("Max погрешность: " + maxErr.student + " (" + maxErr.error + ")");

        // 2. find / find_if (аналог findFirst)
        Optional<Measurement> foundByName = measurements.stream()
                .filter(m -> m.student.equals("Смирнов"))
                .findFirst();
        foundByName.ifPresent(m -> System.out.println("Найден по имени: " + m.student));

        Optional<Measurement> foundByError = measurements.stream()
                .filter(m -> m.error > 1.0)
                .findFirst();
        foundByError.ifPresent(m -> System.out.println("Найден с ошибкой > 1.0: " + m.student));

        // 3. copy / copy_if (аналог toList)
        List<Measurement> copyVec = new ArrayList<>(measurements);
        System.out.println("Скопировано элементов: " + copyVec.size());

        List<Measurement> badCopies = measurements.stream()
                .filter(m -> m.error > 0.5)
                .toList();
        System.out.println("Скопировано с ошибкой > 0.5: " + badCopies.size());

        // 4. sort (аналог sort)
        measurements.sort(Comparator.comparingDouble(m -> m.value));
        System.out.println("Отсортировано по значению. Первый: " + measurements.get(0).value);

        // 5. remove / remove_if (аналог removeIf)
        measurements.removeIf(m -> m.processed);
        System.out.println("После removeIf (удалены обработанные): " + measurements.size());

        // 6. filter (аналог views::filter)
        System.out.print("Filtered (ошибка > 0.1): ");
        measurements.stream()
                .filter(m -> m.error > 0.1)
                .forEach(m -> System.out.print(m.student + " "));
        System.out.println();

        // 7. map (аналог transform / views::transform)
        List<Double> errors = measurements.stream()
                .map(m -> m.error * 2.0)
                .toList();
        System.out.println("Transform (ошибка * 2): " + errors.get(0));

        System.out.print("Names: ");
        measurements.stream()
                .map(m -> m.student)
                .forEach(name -> System.out.print(name + " "));
        System.out.println();

        // 8. anyMatch (аналог any_of)
        boolean hasBigError = measurements.stream()
                .anyMatch(m -> m.error > 1.0);
        System.out.println("AnyMatch (есть ошибка > 1.0?): " + (hasBigError ? "Да" : "Нет"));
    }
}