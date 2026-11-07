import java.util.*;

public class Table {
    private String name;
    private int experiments;
    private final List<BaseColumn> columns = new ArrayList<>();

    public Table(String name, int experiments) {
        this.name = name;
        this.experiments = experiments;
        System.out.println("[+] Table создана: " + this.name);
    }

    public List<BaseColumn> getColumns() { return columns; }

    public void createInputColumn(String name, String var, int precision) {
        columns.add(new InputColumn(name, var, precision));
    }

    public void createConstantColumn(String name, String var, int precision, double value) {
        columns.add(new ConstantColumn(name, var, precision, value));
    }

    public void createFormulaColumn(String name, String var, int precision, Formula formula) {
        columns.add(new FormulaColumn(name, var, precision, formula));
    }

    public void setColumnData(String var, double[] data) {
        for (BaseColumn col : columns) {
            if (col.getVar().equals(var)) {
                col.setData(data);
                return;
            }
        }
    }

    public void calculate() {
        try (TableCalculator calc = new TableCalculator(experiments)) {
            for (BaseColumn col : columns) {
                calc.addCol(col); // Теперь принимает BaseColumn
            }
            calc.tryCalculate();
        }
    }
}