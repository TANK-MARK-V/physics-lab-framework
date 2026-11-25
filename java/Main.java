import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== ЛР-5: Java Полиморфизм, интерфейсы, исключения ===\n");

        // ========== 1. ИНТЕРФЕЙС И МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ ==========
        System.out.println("--- 1. Интерфейс Calculable и множественное наследование ---");
        List<BaseColumn> columns = new ArrayList<>();
        columns.add(new InputColumn("a", "a", 2));
        columns.add(new InputColumn("t", "t", 2));
        columns.add(new FormulaColumn("v", "v", 2, new FormulaEvaluation("a t")));
        columns.add(new FormulaColumn("sum", "sum", 2, new SumEvaluation()));
        columns.add(new ConstantColumn("g", "g", 2, 9.8));

        System.out.println("\nПроверка реализации Calculable:");
        for (BaseColumn col : columns) {
            if (col instanceof Calculable) {
                System.out.println("  " + col.getName() + " -> реализует Calculable");
            } else {
                System.out.println("  " + col.getName() + " -> НЕ реализует Calculable");
            }
        }

        // ========== 2. РАННЕЕ И ПОЗДНЕЕ СВЯЗЫВАНИЕ ==========
        System.out.println("\n--- 2. Раннее и позднее связывание ---");
        BaseColumn basePtr = new FormulaColumn("test", "test", 2, new SimpleEvaluation());
        // В Java все методы виртуальны, поэтому раннего связывания для обычных методов нет.
        // Раннее связывание можно показать только для final или static методов.
        System.out.println("В Java все методы виртуальны. Раннее связывание — только для final/static.");
        System.out.println("describe(): " + basePtr.describe()); // Позднее связывание

        // ========== 3. ПРОВЕРКА ТИПА (instanceof) ==========
        System.out.println("\n--- 3. instanceof: вычисляем только Calculable ---");
        for (BaseColumn col : columns) {
            if (col instanceof Calculable calculable) {
                System.out.println("Вычисляем " + col.getName() + ":");
                calculable.calculate();
            } else {
                System.out.println(col.getName() + ": не требует вычисления");
            }
        }

        // ========== 4. КОНФИГУРИРОВАНИЕ ==========
        System.out.println("\n--- 4. Конфигурирование (объект поведения) ---");
        FormulaColumn dynamicCol = new FormulaColumn("dyn", "dyn", 2, new SimpleEvaluation());
        System.out.println("Стратегия 1:");
        dynamicCol.calculate();

        System.out.println("\nМеняем стратегию на SumEvaluation:");
        dynamicCol.setStrategy(new SumEvaluation());
        dynamicCol.calculate();

        // ========== 5. ИСКЛЮЧЕНИЯ ==========
        System.out.println("\n--- 5. Исключения ---");
        try {
            InputColumn goodCol = new InputColumn("good", "good", 2);
            System.out.println("Колонка 'good' создана успешно");
        } catch (Exception e) {
            System.out.println("Ошибка: " + e.getMessage());
        }

        try {
            InputColumn badCol = new InputColumn("bad", "bad", -5);
            System.out.println("Колонка создана (этого не должно быть!)");
        } catch (InvalidPrecisionException e) {
            System.out.println("Поймано частное исключение: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("Поймано общее исключение: " + e.getMessage());
        } finally {
            System.out.println("Блок finally выполнен");
        }

        // ========== 6. СТАНДАРТНЫЙ ИНТЕРФЕЙС (Comparable) ==========
        System.out.println("\n--- 6. Сортировка (Comparable) ---");
        Collections.sort(columns); // Сортировка по имени
        for (BaseColumn col : columns) {
            System.out.println("  " + col.getName());
        }
        
        System.out.println("\n=== КОНЕЦ ===");
    }
}