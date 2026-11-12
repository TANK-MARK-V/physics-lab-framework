import java.util.Map;

public class FormulaEvaluation implements EvaluationStrategy {
    private String expression;

    public FormulaEvaluation(String expression) {
        this.expression = expression;
    }

    public void setExpression(String expression) {
        this.expression = expression;
    }

    @Override
    public double evaluate(Map<String, Double> vars) {
        // TODO: реальный парсер
        return 42.0;
    }

    @Override
    public String getView() {
        return "Формула: " + expression;
    }

    @Override
    public EvaluationStrategy clone() {
        return new FormulaEvaluation(expression);
    }
}