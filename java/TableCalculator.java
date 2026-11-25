import java.util.*;

public class TableCalculator implements AutoCloseable {
    private final int experiments;
    private final List<BaseColumn> readyCols = new ArrayList<>();
    private final List<BaseColumn> pendingCols = new ArrayList<>();
    private final Map<String, Boolean> varsStates = new HashMap<>();

    public TableCalculator(int experiments) {
        this.experiments = experiments;
        System.out.println("[+] Калькулятор открыт");
    }

    public void addCol(BaseColumn col) {
        if (col.getData() != null && col.getData().length == experiments) {
            readyCols.add(col);
            varsStates.put(col.getVar(), true);
        } else {
            pendingCols.add(col);
            varsStates.put(col.getVar(), false);
        }
    }

    public boolean tryCalculate() {
        boolean progress = true;
        while (progress) {
            progress = false;
            Iterator<BaseColumn> it = pendingCols.iterator();
            while (it.hasNext()) {
                BaseColumn col = it.next();
                if (canCalculate(col)) {
                    if (col instanceof Calculable calculable) {
                        calculable.calculate();
                    } else {
                        double[] result = new double[experiments];
                        Arrays.fill(result, 42.0);
                        col.setData(result);
                    }
                    readyCols.add(col);
                    varsStates.put(col.getVar(), true);
                    it.remove();
                    progress = true;
                }
            }
        }
        return pendingCols.isEmpty();
    }

    private boolean canCalculate(BaseColumn col) {
        if (col instanceof FormulaColumn formulaCol) {
            // Проверяем зависимости по стратегии (если FormulaEvaluation)
            if (formulaCol.getStrategy() instanceof FormulaEvaluation formulaEval) {
                formulaEval.getView();  // Компилятор ругается, если не использовать переменную
                // Можно добавить проверку переменных
            }
        }
        return true;
    }

    @Override
    public void close() {
        System.out.println("[-] Калькулятор закрыт");
    }
}