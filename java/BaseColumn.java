public abstract class BaseColumn {
    // protected: нужно наследникам, но не внешнему коду
    protected String name;
    protected String var;
    protected int precision;
    protected double[] data;

    // Статические члены (одно поле на весь класс)
    private static int lastId = 0;

    // Статический метод
    public static int nextId() {
        return ++lastId;
    }

    // Уникальный ID для каждого объекта
    private final int id;

    public BaseColumn(String name, String var, int precision) {
        this.id = nextId(); // Генерируем ID через статический метод
        this.name = name;
        this.var = var;
        this.precision = checkPrecision(precision);
        System.out.println("[BaseColumn] Создана: " + name + " (ID: " + id + ")");
    }

    protected int checkPrecision(int precision) {
        if (precision < 0) {
            System.out.println("[!] Точность не может быть ниже нуля");
            return 0;
        }
        return precision;
    }

    // Геттеры
    public int getId() { return id; }
    public String getName() { return name; }
    public String getVar() { return var; }
    public int getPrecision() { return precision; }
    public double[] getData() { return data; }

    public void setData(double[] data) { this.data = data; }

    // Абстрактные методы — каждый наследник реализует по-своему
    public abstract String getType();
    public abstract BaseColumn clone();

    // Обычный виртуальный метод (в Java все методы виртуальны по умолчанию)
    public String describe() {
        return var + " (" + name + ")";
    }

    // final метод — запрещаем переопределять
    public final String getFullInfo() {
        return "ID=" + id + ", Type=" + getType() + ", Name=" + name;
    }
}