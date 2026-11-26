import java.util.*;

public class Table {
    private String name;
    private int experiments;
    private final List<BaseColumn> columns = new ArrayList<>();

    public Table(String name, int experiments) {
        this.name = name;
        this.experiments = experiments;
        System.out.println("[Table] Создана: " + this.name);
    }

    public List<BaseColumn> getColumns() { return columns; }

    public void createInputColumn(String name, String var, int precision) {
        columns.add(new InputColumn(name, var, precision));
    }

    public void createConstantColumn(String name, String var, int precision, double value) {
        columns.add(new ConstantColumn(name, var, precision, value));
    }

    public void createFormulaColumn(String name, String var, int precision, EvaluationStrategy strategy) {
        columns.add(new FormulaColumn(name, var, precision, strategy));
    }

    public void setColumnData(String var, double[] data) {
        for (BaseColumn col : columns) {
            if (col.getVar().equals(var)) {
                col.setData(data);
                return;
            }
        }
    }
    
    // ПЕРЕГРУЗКА МЕТОДОВ: поиск по var (String) и по id (int)
    public BaseColumn findColumn(String var) {
        for (BaseColumn col : columns) {
            if (col.getVar().equals(var)) return col;
        }
        return null;
    }

    public BaseColumn findColumn(int id) {
        for (BaseColumn col : columns) {
            if (col.getId() == id) return col;
        }
        return null;
    }
}