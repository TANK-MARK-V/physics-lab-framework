public class FormulaColumn extends BaseColumn implements Calculable {
    private EvaluationStrategy strategy;
    private boolean isCalculated = false;

    public FormulaColumn(String name, String var, int precision, EvaluationStrategy strategy) {
        super(name, var, precision);
        this.strategy = strategy;
        System.out.println("[FormulaColumn] Создана");
    }

    // Конструктор копирования (глубокая копия через clone)
    public FormulaColumn(FormulaColumn other) {
        super(other.name, other.var, other.precision);
        this.strategy = other.strategy != null ? other.strategy.clone() : null;
        System.out.println("[FormulaColumn] Копия: " + name);
    }

    @Override
    public String getType() {
        return "Formula";
    }

    @Override
    public String describe() {
        if (strategy != null) {
            return "Формула: " + name + " = " + strategy.getView();
        }
        return "Формула: " + name + " (нет стратегии)";
    }

    @Override
    public BaseColumn clone() {
        return new FormulaColumn(this);
    }

    // Динамическое конфигурирование
    public void setStrategy(EvaluationStrategy strategy) {
        this.strategy = strategy;
        System.out.println("[FormulaColumn] Стратегия изменена для " + name);
    }

    public EvaluationStrategy getStrategy() {
        return strategy;
    }

    // Реализация Calculable
    @Override
    public void calculate() {
        if (strategy == null) {
            System.out.println("[FormulaColumn] Ошибка: нет стратегии для " + name);
            return;
        }
        java.util.Map<String, Double> vars = new java.util.HashMap<>();
        double result = strategy.evaluate(vars);
        isCalculated = true;
        System.out.println("[FormulaColumn] " + name + " (" + strategy.getView() + ") = " + result);
    }

    @Override
    public boolean isCalculated() {
        return isCalculated;
    }
}