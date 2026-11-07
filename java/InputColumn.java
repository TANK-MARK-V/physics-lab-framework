public class InputColumn extends BaseColumn {
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
}