import columns.*;
import table.*;
import exceptions.*;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== ЛР-6: Статический полиморфизм (Java) ===\n");

        // =====================================================================
        // 1. ПЕРЕГРУЗКА МЕТОДОВ
        // =====================================================================
        System.out.println("--- 1. Перегрузка методов (поиск в таблице) ---");
        Table myTable = new Table("Тестовая таблица", 3);
        myTable.createInputColumn("Угол", "alpha", 2);
        myTable.createConstantColumn("Гравитация", "g", 2, 9.81);

        // Поиск по var (String)
        BaseColumn colByName = myTable.findColumn("alpha");
        if (colByName != null) {
            System.out.println("Найдено по имени: " + colByName);
        }

        // Поиск по id (int)
        int targetId = colByName.getId() + 1;
        BaseColumn colById = myTable.findColumn(targetId);
        if (colById != null) {
            System.out.println("Найдено по ID(" + targetId + "): " + colById);
        }

        // =====================================================================
        // 2. ЭМУЛЯЦИЯ ПЕРЕГРУЗКИ ОПЕРАТОРОВ И СРАВНЕНИЕ (equals, compareTo)
        // =====================================================================
        System.out.println("\n--- 2. Значимый класс PhysicalQuantity ---");
        PhysicalQuantity q1 = new PhysicalQuantity(10.5, 0.1);
        PhysicalQuantity q2 = new PhysicalQuantity(5.2, 0.2);

        // В Java вместо + и += используются методы
        PhysicalQuantity q3 = q1.plus(q2);
        System.out.println("q1.plus(q2) = " + q3);
        
        PhysicalQuantity q4 = q3.plus(q1);
        System.out.println("q3.plus(q1) = " + q4);
        
        PhysicalQuantity q5 = q1.times(3);
        System.out.println("q1.times(3) = " + q5);

        // Сравнение (equals и compareTo)
        System.out.println("q1.equals(q2): " + q1.equals(q2));
        System.out.println("q1.compareTo(q2) > 0: " + (q1.compareTo(q2) > 0));

        // =====================================================================
        // 3. АНАЛОГ ДРУЖЕСТВЕННЫХ ФУНКЦИЙ (package-private)
        // =====================================================================
        System.out.println("\n--- 3. Аналог friend (package-private) ---");
        // Класс ColumnPrinter находится в том же пакете (по умолчанию), 
        // поэтому он имеет доступ к полю name напрямую (без геттера).
        ColumnPrinter.printRawName(colByName);

        // =====================================================================
        // 4. ОБОБЩЁННЫЙ МЕТОД С ОГРАНИЧЕНИЕМ (<T extends Number>)
        // =====================================================================
        System.out.println("\n--- 4. Обобщённый метод Average ---");
        
        Integer[] ints = {1, 2, 3, 4, 5};
        System.out.println("Среднее (Integer): " + Calculations.average(ints));
        
        Double[] doubles = {1.5, 2.5, 3.5};
        System.out.println("Среднее (Double): " + Calculations.average(doubles));
        
        Float[] floats = {1.0f, 2.0f, 3.0f};
        System.out.println("Среднее (Float): " + Calculations.average(floats));

        // Демонстрация того, что концепт работает (не скомпилируется, если раскомментировать):
        // String[] strings = {"a", "b"};
        // System.out.println(Calculations.average(strings)); // Ошибка: String не является Number

        // =====================================================================
        // 5. ОБОБЩЁННЫЙ КЛАСС И ОБОБЩЁННЫЙ МЕТОД
        // =====================================================================
        System.out.println("\n--- 5. Обобщённый класс ColumnContainer ---");

        // Шаблон используется с типом 1: InputColumn
        ColumnContainer<InputColumn> inputContainer = new ColumnContainer<>();
        inputContainer.add(new InputColumn("angle_1", "a1", 2));
        inputContainer.add(new InputColumn("angle_2", "a2", 2));

        // Шаблон используется с типом 2: BaseColumn
        ColumnContainer<BaseColumn> allContainer = new ColumnContainer<>();
        allContainer.add(new ConstantColumn("g", "g", 2, 9.81));

        // Демонстрация обобщённого метода mergeFrom
        System.out.println("Переливаем InputColumn в BaseColumn...");
        allContainer.mergeFrom(inputContainer);

        System.out.println("Размер общего контейнера: " + allContainer.size());
        for (int i = 0; i < allContainer.size(); i++) {
            System.out.println("  Элемент [" + i + "]: " + allContainer.get(i));
        }

        // Демонстрация ограничения <T extends BaseColumn> (не скомпилируется, если раскомментировать):
        // ColumnContainer<Integer> invalidContainer = new ColumnContainer<>(); 

        System.out.println("\n=== КОНЕЦ ===");
    }
}