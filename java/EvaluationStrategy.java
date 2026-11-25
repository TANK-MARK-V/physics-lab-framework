import java.util.Map;

public interface EvaluationStrategy {
    double evaluate(Map<String, Double> vars);
    String getView();
    EvaluationStrategy clone();
}