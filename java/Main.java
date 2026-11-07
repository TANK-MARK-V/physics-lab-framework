import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== ЛР-4: Java Наследование ===\n");

        // ========== 1. СОЗДАНИЕ ОБЪЕКТОВ ==========
        System.out.println("--- 1. Создание объектов (super) ---");
        Formula formula = new Formula("Скорость", "a t");
        
        List<BaseColumn> columns = new ArrayList<>();
        columns.add(new InputColumn("a", "a", 2));
        columns.add(new InputColumn("t", "t", 2));
        columns.add(new FormulaColumn("v", "v", 2, formula));
        columns.add(new ConstantColumn("g", "g", 2, 9.8));

        // ========== 2. ПОЛИМОРФИЗМ И ОПИСАНИЕ ==========
        System.out.println("\n--- 2. Полиморфизм и describe ---");
        for (BaseColumn col : columns) {
            System.out.println(col.describe());
            System.out.println(col.getFullInfo()); // final метод
        }

        // ========== 3. ПОВЕРХНОСТНАЯ И ГЛУБОКАЯ КОПИЯ ==========
        System.out.println("\n--- 3. Копирование ---");
        FormulaColumn original = new FormulaColumn("v", "v", 2, formula);
        original.setData(new double[]{1, 2, 3});

        // 3.1. Поверхностная копия (через присваивание ссылки)
        System.out.println("\n3.1. Поверхностная копия (ссылка)");
        FormulaColumn shallowCopy = original; // Это просто ссылка на тот же объект!
        
        // 3.2. Глубокая копия (через конструктор копирования)
        System.out.println("\n3.2. Глубокая копия (конструктор)");
        FormulaColumn deepCopy = new FormulaColumn(original);

        // Меняем формулу у оригинала
        original.getFormula().setExpression("x y"); // *Примечание: нужно добавить setExpression в Formula.java

        System.out.println("original: " + original.describe());
        System.out.println("shallow:  " + shallowCopy.describe()); // Изменится (тот же объект)
        System.out.println("deep:     " + deepCopy.describe());    // Не изменится (своя формула)

        // ========== 4. THIS ==========
        System.out.println("\n--- 4. this ---");
        // В конструкторе deepCopy мы использовали this.name и this.var
        System.out.println("Использование this в конструкторе копирования (см. код)");

        // ========== 5. СТАТИЧЕСКИЙ СЧЁТЧИК ==========
        System.out.println("\n--- 5. Статический счётчик ---");
        for (BaseColumn col : columns) {
            System.out.println("ID: " + col.getId() + " | " + col.getFullInfo());
        }

        // ========== 6. EQUALS И HASHCODE ==========
        System.out.println("\n--- 6. Сравнение по содержимому ---");
        ConstantColumn c1 = new ConstantColumn("g", "g", 2, 9.8);
        ConstantColumn c2 = new ConstantColumn("g", "g", 2, 9.8);
        System.out.println("c1.equals(c2): " + c1.equals(c2));
        System.out.println("c1.hashCode() == c2.hashCode(): " + (c1.hashCode() == c2.hashCode()));
    }
}