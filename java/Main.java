import columns.*;
import table.*;
import demos.*;

import java.util.*;


public class Main {
    public static void main(String[] args) {
        System.out.println("=== ЛР-7: Контейнеры, алгоритмы и лямбда-функции (Java) ===\n");

        // =====================================================================
        // 1. КОНТЕЙНЕРЫ
        // =====================================================================
        System.out.println("--- 1. Контейнеры ---");

        // 1.1. Массив T[] (аналог std::array)
        Double[] studentCoeffs = {0.0, 12.7, 4.3, 3.18, 2.78};
        System.out.println("Коэффициент Стьюдента для n=3: " + studentCoeffs[2]);

        // 1.2. ArrayList в TableCalculator (аналог std::vector)
        // Демонстрируем, что ArrayList используется для хранения колонок
        try (TableCalculator calc = new TableCalculator(3)) {
            InputColumn c1 = new InputColumn("Угол", "a", 2);
            ConstantColumn c2 = new ConstantColumn("g", "g", 2, 9.81);
            calc.addCol(c1);
            calc.addCol(c2);
            System.out.println("ArrayList в TableCalculator: Готовых = " + calc.getReadyCount() + 
                               ", Ожидающих = " + calc.getPendingCount());
        } // Здесь calc автоматически закроется, и предупреждение исчезнет

        // 1.3. List.subList (аналог std::span)
        // Передаем в average только часть массива (первые 4 элемента)
        List<Double> sub = Arrays.asList(studentCoeffs).subList(1, 4);
        System.out.println("SubList (коэффициенты для n=2,3,4): " + sub);
        System.out.println("Среднее (subList): " + Calculations.average(sub.toArray(new Double[0])));

        // 1.4. LinkedList и TreeMap в классе Table
        Table myTable = new Table("Физика", 3);
        myTable.createInputColumn("Угол", "alpha", 2);
        myTable.createConstantColumn("Гравитация", "g", 2, 9.81);
        myTable.insertColumnAt(1, new ConstantColumn("Пи", "pi", 2, 3.14));

        BaseColumn col = myTable.findColumn("pi");
        if (col != null) {
            System.out.println("Найдено через TreeMap: " + col);
        }

        // =====================================================================
        // 2. АЛГОРИТМЫ (Stream API)
        // =====================================================================
        AlgorithmsDemo.run();

        // =====================================================================
        // 3. std::variant (sealed interface + record)
        // =====================================================================
        System.out.println("\n--- 3. sealed interface (аналог variant) ---");
        CalculationResult res1 = new NumberResult(42.5);
        CalculationResult res2 = new ErrorResult(new PhysicalQuantity(10.5, 0.2));
        CalculationResult res3 = new TextResult("Неизвестная переменная");

        ResultPrinter.print(res1);
        ResultPrinter.print(res2);
        ResultPrinter.print(res3);

        // =====================================================================
        // 4. ЛЯМБДЫ И ЗАХВАТ
        // =====================================================================
        LambdaDemo.run();

        // =====================================================================
        // 5. FUNCTION В ПОЛЕ (Замена стратегии)
        // =====================================================================
        System.out.println("\n--- 5. Function в поле (Замена стратегии) ---");
        
        FormulaColumn fCol = new FormulaColumn("Тест", "test", 2, 
            vars -> 42.0
        );
        fCol.calculate();

        fCol.setCalculator(vars -> {
            double sum = 0.0;
            for (double v : vars.values()) sum += v;
            return sum;
        });
        fCol.calculate(); 

        System.out.println("\n=== КОНЕЦ ===");
    }
}