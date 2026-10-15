import java.util.*;

public class Formula {
    private String name;
    private String expression;
    private List<String> postfix = new ArrayList<>();
    private List<String> vars = new ArrayList<>();

    public Formula(String name, String expression) {
        this.name = name;
        this.expression = expression;
        parseExpression();
        System.out.println("[+] Formula создана: " + name);
    }

    public String getName() { return name; }
    public String getExpression() { return expression; }
    public List<String> getVars() { return vars; }

    private void parseExpression() {
        String[] tokens = expression.split(" ");
        for (String token : tokens) {
            postfix.add(token);
            if (token.matches("[a-zA-Z]+")) {
                vars.add(token);
            }
        }
    }

    public double evaluate(Map<String, Double> vars) {
        // TODO: реальный парсер
        return 67.0;
    }

    @Override
    public String toString() {
        return "Formula: " + name + " = " + expression;
    }
}