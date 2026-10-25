import java.lang.ref.WeakReference;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== ЛР-3: Java ===\n");

        // ========== 1. КОМПОЗИЦИЯ ==========
        System.out.println("--- 1. Композиция: Table создаёт Column ---");
        Table table = new Table("Демо", 3);

        // Table САМ создаёт колонки без формул
        table.createColumn("a", "a", 2);
        table.createColumn("t", "t", 2);

        // Данные
        table.setColumnData("a", new double[]{5, 5, 5});
        table.setColumnData("t", new double[]{1, 2, 3});

        System.out.println(table);

        // ========== 2. АГРЕГАЦИЯ ==========
        System.out.println("\n--- 2. Агрегация: Formula создана СНАРУЖИ ---");
        Formula formula = new Formula("Скорость", "a t");
        System.out.println("Формула: " + formula);

        // Table создаёт колонку, но формула передаётся СНАРУЖИ
        table.createColumn("v", "v", 2, formula);

        // ========== 3. РАСЧЁТ ==========
        System.out.println("\n--- 3. Расчёт ---");
        table.calculate();

        // ========== 4. ПРАВИЛО ==========
        System.out.println("\n--- 4. Правило: точность < 0 ---");
        table.createColumn("bad", "bad", -1);
        for (Column col : table.getColumns()) {
            if (col.getVar().equals("bad")) {
                System.out.println("Точность: " + col.getPrecision());
            }
        }

        // ========== 5. ССЫЛКИ И КОПИИ ==========
        System.out.println("\n--- 5. Ссылки и копии ---");
        Column first = new Column("first", "f", 2);
        first.setData(new double[]{1, 2, 3});

        Column second = first;
        second.setData(new double[]{10, 20, 30});

        System.out.println("first.data[0]  = " + first.getData()[0]);
        System.out.println("second.data[0] = " + second.getData()[0]);
        System.out.println("Один объект? " + (first == second));

        // ========== 6. СБОРЩИК МУСОРА ==========
        System.out.println("\n--- 6. Сборщик мусора ---");
        Column temp = new Column("temp", "tmp", 2);
        WeakReference<Column> watcher = new WeakReference<>(temp);
        System.out.println("Объект жив: " + (watcher.get() != null));

        temp = null;
        System.gc();
        System.out.println("Объект жив: " + (watcher.get() != null));

        System.out.println("\n=== КОНЕЦ ===");
    }
}