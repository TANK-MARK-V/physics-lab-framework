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
                    double[] result = new double[experiments];
                    Arrays.fill(result, 42.0);
                    col.setData(result);
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
        // Проверяем только для формульных колонок
        if (col instanceof FormulaColumn formulaCol) {
            for (String var : formulaCol.getFormula().getVars()) {
                if (!varsStates.getOrDefault(var, false)) return false;
            }
        }
        return true;
    }

    @Override
    public void close() {
        System.out.println("[-] Калькулятор закрыт");
    }
}