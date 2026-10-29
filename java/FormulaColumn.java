public class FormulaColumn extends BaseColumn {
    private Formula formula;

    public FormulaColumn(String name, String var, int precision, Formula formula) {
        super(name, var, precision);
        this.formula = formula;
        System.out.println("[FormulaColumn] Создана");
    }

    @Override
    public String getType() {
        return "Formula";
    }

    @Override
    public String describe() {
        return "Формула: " + name + " = " + formula.getExpression();
    }

    // Конструктор копирования (глубокая копия)
    public FormulaColumn(FormulaColumn other) {
        super(other.name, other.var, other.precision);
        // Глубокая копия: создаём новую формулу
        this.formula = new Formula(other.formula.getName(), other.formula.getExpression());
        System.out.println("[FormulaColumn] Глубокая копия");
    }

    @Override
    public BaseColumn clone() {
        return new FormulaColumn(this); // Используем конструктор копирования
    }

    public Formula getFormula() { return formula; }
}