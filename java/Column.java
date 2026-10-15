public class Column {
    private String name;
    private String var;
    private int precision;
    private double[] data;
    private Formula formula;

    public Column(String name, String var, int precision) {
        this.name = name;
        this.var = var;
        this.precision = checkPrecision(precision);
        System.out.println("[+] Column создана: " + name);
    }

    private int checkPrecision(int precision) {
        if (precision < 0) {
            System.out.println("[!] Точность не может быть ниже нуля (правило №5)");
            return 0;
        }
        return precision;
    }

    public String getName() { return name; }
    public String getVar() { return var; }
    public int getPrecision() { return precision; }
    public double[] getData() { return data; }
    public Formula getFormula() { return formula; }

    public void setFormula(Formula formula) { this.formula = formula; }
    public void setData(double[] data) { this.data = data; }
    public void setPrecision(int precision) { this.precision = checkPrecision(precision); }

    public boolean isReady(int expectedLength) {
        return data != null && data.length == expectedLength;
    }

    @Override
    public String toString() {
        return "Column: " + name + " (" + var + ")";
    }
}