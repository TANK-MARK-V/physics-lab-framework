import java.util.Map;

public class SimpleEvaluation implements EvaluationStrategy {
    @Override
    public double evaluate(Map<String, Double> vars) {
        return 42.0;
    }

    @Override
    public String getView() {
        return "Заглушка (42.0)";
    }

    @Override
    public EvaluationStrategy clone() {
        return new SimpleEvaluation();
    }
}