import java.util.*;

public class Table {
    private String name;
    private int experiments;
    private final List<Column> columns = new ArrayList<>();

    public Table(String name, int experiments) {
        this.name = name;
        this.experiments = experiments;
        System.out.println("[+] Table создана: " + name);
    }

    public String getName() { return name; }
    public int getExperiments() { return experiments; }
    public List<Column> getColumns() { return columns; }

    public void setName(String name) { this.name = name; }
    public void setExperiments(int experiments) { this.experiments = experiments; }

    // Композиция: Table сам создаёт колонку (без формулы)
    public void createColumn(String name, String var, int precision) {
        columns.add(new Column(name, var, precision));
    }

    // Агрегация: формула создана СНАРУЖИ и передаётся
    public void createColumn(String name, String var, int precision, Formula formula) {
        Column col = new Column(name, var, precision);
        col.setFormula(formula);
        columns.add(col);
    }

    public void setColumnData(String var, double[] data) {
        for (Column col : columns) {
            if (col.getVar().equals(var)) {
                col.setData(data);
                return;
            }
        }
    }

    public void calculate() {
        try (TableCalculator calc = new TableCalculator(experiments)) {
            for (Column col : columns) {
                calc.addCol(col);
            }
            calc.tryCalculate();
        }
    }

    @Override
    public String toString() {
        return "Table: " + name + " (" + experiments + " опытов)";
    }
}