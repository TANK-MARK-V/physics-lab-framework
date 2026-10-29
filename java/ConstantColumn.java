public final class ConstantColumn extends BaseColumn { // final — запрет наследования
    private double value;

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

    @Override
    public boolean equals(Object o) {
    // 1. Проверка на тот же самый объект (this)
    if (this == o) return true;
    
    // 2. Проверка на null и тип
    if (o == null || getClass() != o.getClass()) return false;
    
    // 3. Приведение типа и сравнение по содержимому
    ConstantColumn that = (ConstantColumn) o;
    
    // Сравниваем имя, переменную и значение
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