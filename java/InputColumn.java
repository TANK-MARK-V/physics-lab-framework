public class InputColumn extends BaseColumn implements Calculable {
    private boolean isCalculated = false;

    public InputColumn(String name, String var, int precision) {
        super(name, var, precision); // Вызов конструктора базы
        System.out.println("[InputColumn] Создана");
    }

    @Override
    public String getType() {
        return "Input";
    }

    @Override
    public String describe() {
        // Вызов метода базового класса
        return super.describe() + " [ввод]";
    }

    @Override
    public BaseColumn clone() {
        return new InputColumn(this.name, this.var, this.precision);
    }

    // Реализация Calculable
    @Override
    public void calculate() {
        if (data == null || data.length == 0) {
            System.out.println("[InputColumn] " + name + ": данные не введены");
            isCalculated = false;
        } else {
            System.out.println("[InputColumn] " + name + ": данные готовы");
            isCalculated = true;
        }
    }

    @Override
    public boolean isCalculated() {
        return isCalculated;
    }
}