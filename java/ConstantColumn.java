public final class ConstantColumn extends BaseColumn implements Calculable {
    private double value;
    private boolean isCalculated = false;

    public ConstantColumn(String name, String var, int precision, double value) {
        super(name, var, precision);
        this.value = value;
        System.out.println("[ConstantColumn] Создана");
    }

    @Override
    public String getType() {
        return "Constant";
    }

    @Override
    public String describe() {
        // Без вызова базы
        return "Константа: " + name + " = " + value;
    }

    @Override
    public BaseColumn clone() {
        return new ConstantColumn(this.name, this.var, this.precision, this.value);
    }

    // Реализация Calculable
    @Override
    public void calculate() {
        isCalculated = true;
        System.out.println("[ConstantColumn] " + name + " = " + value);
    }

    @Override
    public boolean isCalculated() {
        return isCalculated;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ConstantColumn that = (ConstantColumn) o;
        return Double.compare(that.value, value) == 0 &&
                name.equals(that.name) &&
                var.equals(that.var);
    }

    @Override
    public int hashCode() {
        // Генерируем хеш на основе тех же полей
        return java.util.Objects.hash(name, var, value);
    }
}