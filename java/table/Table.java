package table;
import java.util.*;

import columns.*;

public class Table {
    private String name;
    private int experiments;
    
    // 1. LinkedList (аналог std::list)
    private final LinkedList<BaseColumn> columns = new LinkedList<>();
    
    // 2. TreeMap (аналог std::map)
    private final TreeMap<String, BaseColumn> lookup = new TreeMap<>();

    public Table(String name, int experiments) {
        this.name = name;
        this.experiments = experiments;
        System.out.println("[Table] Создана: " + this.name);
    }

    public List<BaseColumn> getColumns() { return columns; }

    public void createInputColumn(String name, String var, int precision) {
        BaseColumn col = new InputColumn(name, var, precision);
        columns.add(col);
        lookup.put(var, col);
    }

    public void createConstantColumn(String name, String var, int precision, double value) {
        BaseColumn col = new ConstantColumn(name, var, precision, value);
        columns.add(col);
        lookup.put(var, col);
    }

    public void createFormulaColumn(String name, String var, int precision, java.util.function.Function<Map<String, Double>, Double> calculator) {
        BaseColumn col = new FormulaColumn(name, var, precision, calculator);
        columns.add(col);
        lookup.put(var, col);
    }

    // Вставка в середину (демонстрация LinkedList)
    public void insertColumnAt(int index, BaseColumn col) {
        columns.add(index, col);
        lookup.put(col.getVar(), col);
        System.out.println("[Table] Колонка вставлена на позицию " + index);
    }

    public void setColumnData(String var, double[] data) {
        BaseColumn col = lookup.get(var); // Быстрый поиск через TreeMap
        if (col != null) {
            col.setData(data);
        }
    }

    public BaseColumn findColumn(String var) {
        return lookup.get(var);
    }

    public BaseColumn findColumn(int id) {
        for (BaseColumn col : columns) {
            if (col.getId() == id) return col;
        }
        return null;
    }
}