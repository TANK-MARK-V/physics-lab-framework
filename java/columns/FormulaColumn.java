package columns;
import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class FormulaColumn extends BaseColumn implements Calculable {
    // Заменили стратегию на Function
    private Function<Map<String, Double>, Double> calculator;
    private boolean isCalculated = false;

    public FormulaColumn(String name, String var, int precision, Function<Map<String, Double>, Double> calculator) {
        super(name, var, precision);
        this.calculator = calculator;
        System.out.println("[FormulaColumn] Создана");
    }

    @Override
    public String getType() {
        return "Formula";
    }

    @Override
    public String describe() {
        return "Формула: " + name + " (лямбда)";
    }

    @Override
    public BaseColumn clone() {
        return new FormulaColumn(this.name, this.var, this.precision, this.calculator);
    }

    // Смена поведения
    public void setCalculator(Function<Map<String, Double>, Double> calculator) {
        this.calculator = calculator;
        System.out.println("[FormulaColumn] Поведение изменено для " + name);
    }

    @Override
    public void calculate() {
        if (calculator == null) {
            System.out.println("[FormulaColumn] Ошибка: нет поведения для " + name);
            return;
        }
        Map<String, Double> vars = new HashMap<>();
        double result = calculator.apply(vars);
        isCalculated = true;
        System.out.println("[FormulaColumn] " + name + " = " + result);
    }

    @Override
    public boolean isCalculated() {
        return isCalculated;
    }
}