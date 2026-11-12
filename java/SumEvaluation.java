import java.util.Map;

public class SumEvaluation implements EvaluationStrategy {
    @Override
    public double evaluate(Map<String, Double> vars) {
        double sum = 0.0;
        for (double value : vars.values()) {
            sum += value;
        }
        return sum;
    }

    @Override
    public String getView() {
        return "Сумма переменных";
    }

    @Override
    public EvaluationStrategy clone() {
        return new SumEvaluation();
    }
}